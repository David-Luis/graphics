#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 viewPos;

uniform samplerCube cubemap;

uniform int refraction;

void main()
{             
	if (refraction==1)
	{
		float ratio = 1.00 / 1.52;
		vec3 I = normalize(Position - viewPos);
		vec3 R = refract(I, normalize(Normal), ratio);
		FragColor = vec4(texture(cubemap, R).rgb, 1.0);
	}
	else
	{
		vec3 I = normalize(Position - viewPos);
		vec3 R = reflect(I, normalize(Normal));
		FragColor = vec4(texture(cubemap, R).rgb, 1.0);
	}
}