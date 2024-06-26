#KAREN_SHADER_TYPE KAREN_VERTEX
#version 330 core

layout (location = 0) in vec4 i_color;
layout (location = 1) in vec3 i_pos;
layout (location = 2) in vec2 i_tux_coord;
layout (location = 3) in float i_tux_idx;

uniform mat4 u_proj_view;
uniform mat4 u_trans;

out vec4 v_color;
out vec2 v_tux_coord;
out float v_tux_idx;

void main()
{
  gl_Position = u_proj_view * vec4(i_pos, 1.0);
  v_color = i_color;
  v_tux_coord = i_tux_coord;
  v_tux_idx = i_tux_idx;
}

#KAREN_SHADER_TYPE KAREN_FRAGMENT
#KAREN_SAMPLE_TEMPLATE frag_color = texture(u_textures[${KAREN_CURRENT_SWITCH_CASE}], v_tux_coord) * v_color;
#version 330 core


in vec2 v_tux_coord;
in vec4 v_color;
in float v_tux_idx;

uniform sampler2D u_textures[${KAREN_MAX_TEXTUERS}];

out vec4 frag_color;

void main()
{
  int idx = int(v_tux_idx);
  #KAREN_MAX_TEXTUER_SWITCH(idx)
}
