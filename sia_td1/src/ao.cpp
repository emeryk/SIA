#include "integrator.h"
#include "scene.h"
#include "material.h"
#include "warp.h"

class AO : public Integrator
{
public:
    AO(const PropertyList &props) {
        m_sampleCount = props.getInteger("samples", 10);
        m_cosineWeighted = props.getBoolean("cosine", true);
    }

    Color3f Li(const Scene *scene, const Ray &ray) const {
      //throw RTException("AO::Li() is not yet implemented!");
      Hit hit;
      scene->intersect(ray, hit);
      Color3f sum = Color3f(0.f);
      if (hit.foundIntersection())
      {
        Normal3f n = hit.normal();
        Point3f pos = ray.at(hit.t());

        for (int i = 0; i < m_sampleCount; i++)
        {
          //Vector3f n = hit.normal();

          float rand1 = Eigen::internal::random<float>(0,1);
          float rand2 = Eigen::internal::random<float>(0,1);

          Vector3f d;
          if (m_cosineWeighted)
            d = Warp::squareToCosineHemisphere(Point2f(rand1, rand2));
          else
            d = Warp::squareToUniformHemisphere(Point2f(rand1, rand2));

          Vector3f u;
          if(n.y() == 0 && n.z() == 0)
            u = n.cross(Vector3f(0,0,1));
          else
            u = n.cross(Vector3f(1,0,0));
          u.normalize();

          Vector3f v;
          v = u.cross(n);
          v.normalize();

          Vector3f p = d.x() * u + d.y() * v + d.z() * n;

          Ray shadow_ray(pos + n*Epsilon, p, true);
          Hit shadow_hit;
          scene->intersect(shadow_ray, shadow_hit);

          double pdf;

          if (m_cosineWeighted)
            pdf = Warp::squareToCosineHemispherePdf(d);
          else
            pdf = Warp::squareToUniformHemispherePdf(d);

          if(!shadow_hit.foundIntersection())
            sum += Color3f(1.0f)*((p.dot(n) / (p.norm() * n.norm())) / M_PI) / pdf;
        }
        sum /= m_sampleCount;

      }
      return sum;
    }

    std::string toString() const {
      return tfm::format("AO[\n"
                         "  samples = %f\n"
                         "  cosine-weighted = %s]\n",
                         m_sampleCount,
                         m_cosineWeighted ? "true" : "false");
  }

private:
    int m_sampleCount;
    bool m_cosineWeighted;
};

REGISTER_CLASS(AO, "ao")
