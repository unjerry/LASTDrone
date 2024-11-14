#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform vec4 clrr;

uniform sampler2D sprite;

void main() {
    if((texture(sprite, TexCoords)).a < 0.1) {
        discard;
    }
    color = (texture(sprite, TexCoords) * clrr);
}