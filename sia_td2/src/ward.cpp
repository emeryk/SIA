#include "material.h"

Ward::Ward(const PropertyList &propList)
    : Diffuse(propList.getColor("diffuse",Color3f(0.2)))
{
    m_reflectivity = propList.getColor("reflectivity",Color3f(0.0));
    m_transmissivness = propList.getColor("transmissivness",Color3f(0.0));
    m_etaA = propList.getFloat("etaA",1);
    m_etaB = propList.getFloat("etaB",1);
    m_specularColor = propList.getColor("specular",Color3f(0.9));
    m_alphaX = propList.getFloat("alphaX",0.2);
    m_alphaY = propList.getFloat("alphaY",0.2);

    std::string texturePath = propList.getString("texture","");
    if(texturePath.size()>0){
        filesystem::path filepath = getFileResolver()->resolve(texturePath);
        loadTextureFromFile(filepath.str());
        setTextureScale(propList.getFloat("scale",1));
        setTextureMode(TextureMode(propList.getInteger("mode",0)));
    }
}

Color3f Ward::brdf(const Vector3f& viewDir, const Vector3f& lightDir, const Normal3f& normal, const Vector2f& uv) const
{

    float sq = lightDir.dot(normal) * viewDir.dot(normal);

    if (sq <= 0)
      return Color3f(0,0,0);

    Vector3f d(0,1,0);

    Vector3f x = (d - (d.dot(normal) * normal)).normalized();
    Vector3f y = x.cross(normal);

    Vector3f h = (viewDir + lightDir) / (viewDir + lightDir).norm();

    float squareHX = (h.dot(x) / m_alphaX) * (h.dot(x) / m_alphaX);
    float squareHY = (h.dot(y) / m_alphaY) * (h.dot(y) / m_alphaY);
    float squareHN = h.dot(normal) * h.dot(normal);

    float ex = - ((squareHX + squareHY) / squareHN);
    float de = 4 * M_PI * m_alphaX * m_alphaY * sqrt(sq);
    Color3f Fr = (m_specularColor / de) * exp(ex);

    return diffuseColor(uv) / M_PI + Fr;
}

Vector3f Ward::is(const Normal3f &n, const Vector3f &ray_dir) const
{

  float rand = Eigen::internal::random<float>(0, 1);

	if (rand < (m_specularColor.mean() / (m_specularColor.mean() + m_diffuseColor.mean()))) {

    Point2f p1(Eigen::internal::random<float>(0,1),Eigen::internal::random<float>(0,1));

		float angle = 2 * M_PI * p1.y();

	  float phi = atan(m_alphaY / m_alphaX * tan(angle));
		float c = cos(phi);
    float s = sin(phi),

		theta = atan(sqrt( - log(p1.x()) / ((c * c) / ((m_alphaX * m_alphaX)) + (s * s) / ((m_alphaY * m_alphaY)))));

		Vector3f d(0, 1, 0);

		Vector3f u = (d - ((d.dot(n)) * n)).normalized();
		Vector3f v = u.cross(n);
		Vector3f h = Vector3f(sinf(theta) * cos(phi), sin(theta) * sin(phi), cos(theta)).normalized();

		h = (h.x() * u + h.y() * v + h.z() * n).normalized();

		return (2 * (ray_dir.dot(h)) * h - ray_dir).normalized();
	}

	float pdf;
	return (us (n, pdf));
}

Color3f Ward::premultBrdf(const Vector3f& viewDir, const Vector3f& lightDir, const Normal3f& normal, const Vector2f& uv) const {

  if (lightDir.dot(normal) * viewDir.dot(normal) <= 0)
    return Color3f(0, 0, 0);

  Vector3f h = (viewDir + lightDir).normalized();
  return m_specularColor * h.dot(lightDir) * h.dot(normal) * h.dot(normal) * sqrt(viewDir.dot(normal) / lightDir.dot(normal));
}

std::string Ward::toString() const {
    return tfm::format(
        "Ward [\n"
        "  diffuse color = %s\n"
        "  specular color = %s\n"
        "  alphaX = %f  alphaY = %f\n"
        "]", m_diffuseColor.toString(),
             m_specularColor.toString(),
             m_alphaX, m_alphaY);
}

REGISTER_CLASS(Ward, "ward")
