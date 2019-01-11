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

vec3 mainSpecular( out vec3 fragColor, in vec2 fragCoord );
vec3 mainImage( out vec3 fragColor, in vec2 fragCoord );

void main()
{
	vec3 colorMain;
	vec2 uv = -1. + 2 * TexCoord;

	//ambiant
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	//diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	colorMain = mainImage(colorMain, TexCoord);
	vec3 diffuse = (diff * colorMain) * light.diffuse;

	//specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//vec3 specular = (spec * vec3(texture(material.specular, TexCoord))) * light.specular;
	vec3 colorSpec; colorSpec = mainSpecular(colorSpec, TexCoord);
	vec3 specular = (spec * colorSpec) * light.specular;

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
	vec3 result = ((diffuse) * attenuation + emissive);
	fragColor = vec4(result, 1.0);
}

vec3 mainSpecular( out vec3 color, in vec2 fragCoord )
{   
    float speed = .041;
    float scale = 0.002;
    vec2 p = fragCoord * scale;   
    for(int i=1; i<10; i++){
        p.x+=0.9/float(i)*sin(float(i)*3.*p.y+time*speed);
        p.y+=0.2/float(i)*cos(float(i)*3.*p.x+time*speed);
    }
    float r=sin(p.x+p.y+1.)*.5+.5;
    float g=sin(p.x+p.y+1.)*.5+.5;
    float b=sin(p.x+p.y+1.) *.5+.5;
    return color = vec3(r,g,b);
}

vec3 mainImage( out vec3 color, in vec2 fragCoord )
{   
    float speed = .041;
    float scale = 0.002;
    vec2 p = fragCoord * scale;   
    for(int i=1; i<10; i++){
        p.x+=0.9/float(i)*sin(float(i)*3.*p.y+time*speed);
        p.y+=0.2/float(i)*cos(float(i)*3.*p.x+time*speed);
    }
    float r=cos(p.x+p.y+1.)*.5+.5;
    float g=sin(p.x+p.y+1.)*.5+.5;
    float b=(sin(p.x+p.y)+cos(p.x+p.y))*.3+.5;
    return color = vec3(r,g,b);
}