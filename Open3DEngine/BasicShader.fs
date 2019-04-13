
#version 410 core

out vec4 FragColor;
in vec2 v_texcoord;

uniform sampler2D u_texture;

void main()
{
	FragColor = texture2D(u_texture, v_texcoord);
}