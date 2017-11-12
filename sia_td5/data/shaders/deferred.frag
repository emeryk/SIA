#version 410 core

uniform float specular_coef;
uniform mat4 inv_projection_matrix;

in vec3 vert_normal_view;
in vec3 vert_color;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;

vec3 VSPositionFromDepth(vec2 texcoord, float z)
{
	// Get x/w and y/w from the viewport position
	vec4 positionNDC = vec4(2 * vec3(texcoord, z) - 1, 1.f);
	// Transform by the inverse projection matrix
	vec4 positionVS = inv_projection_matrix * positionNDC;
	// Divide by w to get the view-space position
	return positionVS.xyz / positionVS.w;
}

void main()
{
  out_color = vec4(vert_color, specular_coef);

  out_normal = vec4((vert_normal_view + 1.0) / 2.0, gl_FragCoord.z);
}
