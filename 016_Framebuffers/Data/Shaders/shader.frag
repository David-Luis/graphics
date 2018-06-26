#version 330 core
out vec4 FragColor;
  
in vec3 Normal; 
in vec2 TexCoord; 
in vec3 FragPos;  

#define MAX_DIRECTIONAL_LIGHTS 4
struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform int numDirectionalLights;
uniform DirLight directionalLights[MAX_DIRECTIONAL_LIGHTS];

#define MAX_POINT_LIGHTS 16
struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};
uniform int numPointLights;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

#define MAX_SPOT_LIGHTS 8
struct SpotLight {
    vec3 position;
	vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	
	float cutOff;
    float outerCutOff;
};
uniform int numSpotLights;
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

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

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 textureDiffuse, vec4 textureSpecular)
{
    vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	// ambient
	vec3 ambient = light.ambient * material.ambient * vec3(textureDiffuse);
	
    // diffuse 
	vec3 diffuse = light.diffuse * diff * material.diffuse * vec3(textureDiffuse);
	
    // specular shading
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * light.specular * material.specular * vec3(textureSpecular);
	
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 textureDiffuse, vec4 textureSpecular)
{
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);  
	
	// ambient
    vec3 ambient = light.ambient * material.ambient * vec3(textureDiffuse);
  	
    // diffuse 
	vec3 diffuse = light.diffuse * diff * material.diffuse * vec3(textureDiffuse);  
    
    // specular
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * light.specular * material.specular * vec3(textureSpecular);  
	
	float distance    = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * distance + light.quadraticAttenuation * (distance * distance));    
	
	ambient  *= attenuation; 
	diffuse  *= attenuation;
	specular *= attenuation;   
        
    return(ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 textureDiffuse, vec4 textureSpecular)
{
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);  
	
	// ambient
    vec3 ambient = light.ambient * material.ambient * vec3(textureDiffuse);
  	
    // diffuse 
	vec3 diffuse = light.diffuse * diff * material.diffuse * vec3(textureDiffuse);  
    
    // specular
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * light.specular * material.specular * vec3(textureSpecular);  
	
	float distance    = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * distance + light.quadraticAttenuation * (distance * distance));    
	
	float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);	
	
	ambient  *= attenuation; 
	diffuse  *= attenuation * intensity;
	specular *= attenuation * intensity;  
        
    return(ambient + diffuse + specular);
}

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec4 textureDiffuse = texture(material.texture_diffuse_1, TexCoord);
	vec4 textureSpecular = texture(material.texture_specular_1, TexCoord);
	
	vec3 result;
	
	for(int i = 0; i < numDirectionalLights; i++)
	{
		result += CalcDirLight(directionalLights[i], norm, viewDir, textureDiffuse, textureSpecular);
	}
	
	for(int i = 0; i < numPointLights; i++)
	{
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir, textureDiffuse, textureSpecular);
	}
	
	for(int i = 0; i < numSpotLights; i++)
	{
		result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir, textureDiffuse, textureSpecular);
	}
	
	FragColor = vec4(result, textureDiffuse.a);
}