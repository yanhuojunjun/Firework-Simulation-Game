#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in float aPointSize;
out vec4 ourColor;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 camera_pos;
void main()
{   
    gl_PointSize = aPointSize  / length(camera_pos - aPos);
    gl_Position = projection * view * vec4(aPos, 1.0);
    ourColor = aColor;
}