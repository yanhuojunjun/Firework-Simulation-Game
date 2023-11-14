#version 330 core
out vec4 FragColor;

in vec4 ourColor;
// 纹理坐标
//in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, gl_PointCoord) * ourColor;
}