#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;

void main()
{
	FragColor = vec4(0.6 * texture(texture1, TexCoord).xyz, 1.0f);
}