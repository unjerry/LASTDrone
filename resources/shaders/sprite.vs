#version 330 core
layout(location = 0) in vec3 vertex; // <vec2 position, vec2 texCoords>
layout(location = 1) in vec2 texx; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
    TexCoords = texx;
    gl_Position = projection * view * model * vec4(vertex.xyz, 1.0);
}