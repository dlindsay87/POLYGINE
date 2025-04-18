#version 460 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 ViewDir;

#define GAMMA {{GAMMA}}
#define SPEC_STRENGTH {{SPEC_STRENGTH}}
#define SHINE_FACTOR {{SHINE_FACTOR}}

#define AMBIENT_STRENGTH {{AMBIENT_STRENGTH}}
#define AMBIENT_BLEND {{AMBIENT_BLEND}}

//uniform vec3 attenuationFactors;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 camPos;

uniform vec3 bgc;

void main() {
    vec3 ViewDir = normalize(FragPos - camPos);
    vec3 ambient = AMBIENT_STRENGTH * mix(lightColor, bgc, AMBIENT_BLEND);

    vec3 lightDir = normalize(lightPos - FragPos);
    float lightDistance = length(lightPos - FragPos);

    vec3 attenuationFactors = {1.0, 0.2, 0.01};
    float attenuation = dot(attenuationFactors, vec3(1.0, lightDistance, lightDistance * lightDistance));

    float diffusion = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diffusion * lightColor / attenuation;

    vec3 reflectDir = normalize(reflect(lightDir, Normal));
    float spec = pow(max(dot(ViewDir, reflectDir), 0.0), SHINE_FACTOR);
    vec3 specular = SPEC_STRENGTH * spec * lightColor / attenuation;

    vec3 result = (ambient + diffuse + specular) * objectColor;

    vec3 gammaCorrect = pow(result, vec3(1.0 / GAMMA));
    FragColor = vec4(gammaCorrect, 1.0);
}