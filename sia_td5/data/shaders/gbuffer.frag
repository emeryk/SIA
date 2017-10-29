#version 410 core

uniform float specular_coef;
uniform float depth;

in vec3 vert_normal_view;
in vec3 vert_color;

out vec4 out_color;
out vec4 out_normal;

void main()
{
  out_color = vec4(vert_color, specular_coef);

  out_normal = vec4(vert_normal_view, depth);

  out_normal = normalize(out_color);
}
