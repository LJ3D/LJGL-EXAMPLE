#version 330 core

layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aNorm; // the normal variable has attribute position 1
layout (location = 2) in vec2 aTexCoords; // the texture coordinates variable has attribute position 2
layout (location = 3) in vec3 aOffset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoords;

void main(){
    gl_Position = projection * view * model * vec4(aPos + aOffset, 1.0);
    normal = mat3(transpose(inverse(model))) * aNorm;
    fragPos = vec3(model * vec4(aPos, 1.0));
    texCoords = aTexCoords * 10.0;
}
