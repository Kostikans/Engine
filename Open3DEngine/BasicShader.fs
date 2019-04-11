
#version 410 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
	FragColor = texture2D(texture1, TexCoord);
}