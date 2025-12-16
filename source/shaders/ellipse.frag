#version 330 core

uniform vec2 center;
uniform vec2 rad;

out vec4 FragColor;

in vec3 color;
in vec2 fragPos;

void main()
{

    for (float i = fragPos.x - w; i < fragPos.x + w; i++) {
        for (float j = fragPos.y - h; j < fragPos.y + h; j++) {

            float pointCheck = (pow((i - fragPos.x), 2) / pow(w / 2, 2)) + (pow((j - fragPos.y), 2) / pow(h / 2, 2));

            if (pointCheck > 1.0) {
                continue;
            }

            //point(i, j);
        }
    }

    FragColor = vec4(color, 1.0);
}