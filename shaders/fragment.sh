#version 330 core

in vec3 colorOut;

out vec4 fragmentColor;

void main()
{
    fragmentColor = vec4(colorOut,1.0f);
}