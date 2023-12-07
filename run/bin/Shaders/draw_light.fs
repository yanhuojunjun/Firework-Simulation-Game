#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;

void main()
{   
    vec3 result;          
    vec3 Color = texture(scene, TexCoords).rgb;      
    if(Color.r+Color.g+Color.b<=1.0f)
        Color=vec3(0,0,0);
    FragColor = vec4(Color, 1.0);
}