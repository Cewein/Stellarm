#version 450

out vec4 fragColor;

in vec3 Normal;
in vec2 TexCoord;
in vec3 fragPos;

uniform float time;
uniform vec3 viewPos;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emissive;
	float	  shininess;
};

struct Light {
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform Material material;
uniform Light light;

void main()
{
	vec2 uv = -1. + 2 * TexCoord;

	//ambiant
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	//diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * vec3(texture(material.diffuse, TexCoord))) * light.diffuse;

	//specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * vec3(texture(material.specular, TexCoord))) * light.specular;

	vec3 emissive = vec3(0.0f);
	/*emission
	if(texture(material.specular, TexCoord).r == 0.0f)
	{
		emissive = texture(material.emissive, TexCoord).rgb;
	}
	*/

	//attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	//output
	vec3 result = ((ambient + diffuse + specular) * attenuation + emissive);
	fragColor = vec4(result, 1.0);
}