#version 330 core

uniform mat4 projection;
uniform vec3 color;
layout (location = 0) in vec2 aPos;

out vec3 ourColor;

void main()
{
    gl_Position = projection * vec4(aPos, 0.0, 1.0);
    ourColor = color;
}