#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;

out vec4 ourColor;

uniform mat4 view;
uniform mat4 projection;

void main()
{   
    //gl_PointSize = 10.0;
    gl_PointSize = 50.0 / distance(aPos.xyz, vec3(0.0f));
    gl_Position = projection * view * aPos;
    ourColor = aColor;
}