#version 450 core

in vec2 fTex;
in vec2 fTex2;

layout (location = 0) out vec4 colour;

layout (binding = 0) uniform sampler2D tex;
layout (binding = 1) uniform sampler2D tex2;

void main()
{
	vec4 diffuse_colour = texture(tex, fTex);
	vec4 second_colour = texture(tex2, fTex2);

	colour = diffuse_colour;
	if (second_colour.a > 0.1f)
	{
		colour.xyz = second_colour.xyz;
	}

	if (colour.a < 0.1f)
	{
		discard;
	}
}