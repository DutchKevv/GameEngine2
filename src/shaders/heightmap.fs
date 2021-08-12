#version 330

in vec2 TexCoords;

uniform sampler2D ourTexture;

out vec4 color;

void main()
{
    color = texture(ourTexture, TexCoords);

    // color = vec4(1.2, 1.0, 0.2, 1.0); 
};