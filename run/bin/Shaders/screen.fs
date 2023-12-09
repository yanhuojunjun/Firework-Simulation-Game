#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform bool bloom;
uniform float exposure;

void main()
{   
    vec3 result;          
    const float gamma = 2.2;
    vec3 hdrColor = texture(scene, TexCoords).rgb;      
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
    if(bloom)
        result= hdrColor+bloomColor;
    else result= hdrColor;
    // tone mapping
    //result = vec3(1.0) - exp(-result * exposure);
    // also gamma correct while we're at it       
    //result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
}