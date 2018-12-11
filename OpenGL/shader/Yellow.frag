#version 450

out vec4 fragColor;

in vec3 vertColor;
in vec2 textCoord;

uniform float time;
uniform sampler2D wallTexture;
uniform sampler2D happyFace;

void main()
{
	fragColor = mix(texture(wallTexture, textCoord), texture(happyFace, vec2(-1.0 + textCoord.x + cos(time/10), sin(time) + textCoord.y)), 0.2) * vec4(vertColor,1.);
}