#version 330 core

uniform vec2 center;
uniform vec2 rad;

in vec3 ourColor;
in vec2 fragPos;

out vec4 FragColor;

void main()
{
    float dx = (fragPos.x - center.x) / rad.x;
    float dy = (fragPos.y - center.y) / rad.y;
    float dist = dx * dx + dy * dy;

    if (dist > 1.0) {
        discard;
    }

    FragColor = vec4(ourColor, 1.0);
}