#version 330 core
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = vec4(1.0, 0.28, 0.26, 1.0); 
}