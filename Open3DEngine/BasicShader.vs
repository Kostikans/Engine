
#version 410 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;


uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;

out vec2 v_texcoord;

void main()
{
    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4( a_position, 1.0f);
	v_texcoord = a_texcoord;
}