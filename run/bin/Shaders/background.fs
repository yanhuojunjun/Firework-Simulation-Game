// #version 330 core
// out vec4 FragColor;

// in vec2 TexCoord;

// // texture samplers
// uniform sampler2D texture1;
// uniform sampler2D texture2;

// void main()
// {
// 	// linearly interpolate between both textures (80% container, 20% awesomeface)
// 	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.6f);
// } //没有添加多光源渲染的

//begin

#version 330 core
out vec4 FragColor;

struct Material {
    // sampler2D diffuse;
    // sampler2D specular;
	vec3 lightcolor;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	vec3 lightcolor;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	vec3 lightcolor;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;   
	vec3 lightcolor;    
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

#define MAX_LEN 20

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform int max_len;
uniform PointLight pointLights[MAX_LEN];
uniform SpotLight spotLight;
uniform Material material;
uniform sampler2D texture1;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
    vec3 result = 0.7*CalcDirLight(dirLight, norm, viewDir); //需要一直有自然光的照射
    // phase 2: point lights
    // result += CalcPointLight(pointLights[0], norm, FragPos, viewDir);
    // result += CalcPointLight(pointLights[1], norm, FragPos, viewDir);
    // result += CalcPointLight(pointLights[2], norm, FragPos, viewDir);
    for(int i = 0; i < max_len; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir); 

    // phase 3: spot light
    // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);  //不需要聚光灯  
    result = result * vec3(texture(texture1, TexCoords)); // result* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * light.lightcolor; //vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * light.lightcolor; // vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * light.lightcolor; //vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
	
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * light.lightcolor; //vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * light.lightcolor; //vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * light.lightcolor; //vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}