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
	float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    FragColor = vec4(average, average, average, 1.0);
}