#version 450 core

layout (location = 0) out vec4 color;

in vec4 fColour;

void main()
{
	//color = fColour;
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}