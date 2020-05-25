#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTex;

out vec2 fTex;

uniform mat4 view, projection, transform;
uniform mat4 tex_matrix;

void main()
{
    gl_Position = projection * view * transform * vPosition;

    fTex = (vec4(vTex, 1.0f, 1.0f) * tex_matrix).xy;
}