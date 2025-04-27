#version 460

in vec2 tCoords;

out vec4 color;

uniform sampler2D diffuse;

void main() {
    vec4 t_color = texture(diffuse, tCoords);
    if(t_color.a < 0.1){
        discard;
    }
    color = t_color;
}