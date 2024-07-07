#version 410 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

#define MAX_LIGHTS 5
#define GAMMA 2.2
uniform vec3 lightColors[MAX_LIGHTS];
uniform vec3 lightPositions[MAX_LIGHTS];

uniform vec3 objectColor;
uniform vec3 bgc;

void main() {
	vec3 ambient = 0.1 * bgc;
    vec3 diffuse = vec3(0.0);

	vec3 norm = normalize(Normal);
	
	for (int i = 0; i < MAX_LIGHTS; i++) {
		vec3 lightDir = normalize(lightPositions[i] - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		float distance = length(lightPositions[i] - FragPos);
		float attenuation = 1.0 + 0.05 * distance + 0.1 * distance * distance;
		
		diffuse += diff * lightColors[i] / attenuation;
	}

	vec3 result = (ambient + diffuse) * objectColor;
	vec3 gammaCorrect = pow(result, vec3(1.0 / GAMMA));
	FragColor = vec4(gammaCorrect, 1.0);
}