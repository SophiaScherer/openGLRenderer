#version 330 core

uniform mat4 projection;
uniform vec3 color;

layout (location = 0) in vec2 aPos;

out vec3 ourColor;
out vec2 fragPos;

void main()
{
    vec2 position = (projection * vec4(aPos, 0.0, 1.0)).xy;
    //gl_Position = position;
    fragPos = position;

    ourColor = color;
}