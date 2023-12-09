#version 330 core
out vec4 FragColor;

in vec4 ourColor;

uniform sampler2D texture1;

void main()
{
    if(ourColor.a > 0.05){
        FragColor = texture(texture1, gl_PointCoord) * ourColor;
    }
    else{
        discard;
    }
    
}