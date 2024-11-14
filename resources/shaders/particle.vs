#version 330 core
layout(location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    TexCoords = vertex.zw;
    gl_Position = projection * view * model * vec4(vertex.xy * 0.05, 0.0, 1.0);//projection * view * vec4(vertex.x, vertex.y, 0.0, 1.0);
}