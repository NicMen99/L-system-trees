#version 460

in vec2 tCoords;

out vec4 color;

uniform sampler2D bark_diffuse;

void main() {
    color = texture(bark_diffuse, tCoords);
}