#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
//out vec3 ViewDir;

uniform mat4 model;

layout(std140) uniform Matrices {
    mat4 view;
    mat4 proj;
    //vec3 camPos;
};

void main() {
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = normalize(mat3(transpose(inverse(model))) * aNormal);
    gl_Position = proj * view * vec4(FragPos, 1.0);

    //vec3 ViewDir = normalize(camPos - FragPos);
}