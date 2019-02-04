#version 450

out vec4 fragColor;

in vec3 Normal;
in vec2 TexCoord;
in vec3 fragPos;

uniform float time;
uniform vec3 viewPos;
uniform float attenu;

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
	vec3 fullBrigthTex = vec3(texture(material.diffuse, TexCoord));

	vec3 attenuation = vec3(attenu);

	//output
	vec3 result = fullBrigthTex + attenuation;
	fragColor = vec4(result, 1.0);
}