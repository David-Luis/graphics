#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord; 

struct Material {
	sampler2D texture_diffuse;
};
uniform Material material;

void main()
{
	vec4 textureDiffuse = texture(material.texture_diffuse, TexCoord);
    FragColor = textureDiffuse * ourColor;
}