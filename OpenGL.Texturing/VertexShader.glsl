#version 400 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTex;

out vec2 fTex;

uniform mat4 view, projection, transform;

void main()
{
    gl_Position = projection * view * transform * vPosition;

    fTex = vTex;
}