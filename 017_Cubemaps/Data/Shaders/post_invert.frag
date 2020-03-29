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
	FragColor = vec4(vec3(1.0 - textureDiffuse * ourColor), 1.0);
}