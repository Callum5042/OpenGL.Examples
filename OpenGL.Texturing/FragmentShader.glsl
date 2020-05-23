#version 450 core

in vec2 fTex;

layout (location = 0) out vec4 color;

uniform sampler2D tex;

void main()
{
	color = texture(tex, fTex);
}