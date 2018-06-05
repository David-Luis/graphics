#version 330 core
out vec4 FragColor;
  
in vec3 Normal; 
in vec2 TexCoord; 
in vec3 FragPos;  

uniform sampler2D ourTexture;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

struct Material {
	sampler2D texture_diffuse_1;
	sampler2D texture_specular_1;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

uniform Material material;

uniform vec3 viewPos; 

void main()
{
	 // ambient
     vec3 ambient = light.ambient * material.ambient * vec3(texture(material.texture_diffuse_1, TexCoord));
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * material.diffuse * vec3(texture(material.texture_diffuse_1, TexCoord));  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * light.specular * material.specular * vec3(texture(material.texture_specular_1, TexCoord));  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}