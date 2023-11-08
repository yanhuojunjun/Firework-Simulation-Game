#version 330 core
out vec4 FragColor;

in vec3 ourColor;

void main()
{
    //vec4 temp = texture(Texture0, TexCoord) * vec4 (ourColor, 1.0);
    FragColor =  vec4(ourColor, 1.0);
}