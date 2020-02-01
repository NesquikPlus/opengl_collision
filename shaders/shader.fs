#version 450 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_diffuse1;


void main()
{    
	//color = vec4(0.8f, 0.3f, 0.2f, 1.0f);
    color = vec4(texture(texture_diffuse1, TexCoords));
}