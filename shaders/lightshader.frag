#version 460 core
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main() 
{
	FragColor = vec4(mix(objectColor, lightColor, 0.7), 1.0);
}