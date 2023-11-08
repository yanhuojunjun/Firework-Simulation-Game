#version 330 core

// 点光源的数量
#define NR_POINT_LIGHTS 4

// 物体材质
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    // 镜面反光度
    float shininess;
}; 

// 点光源
struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// 平行光
struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// 聚光灯
struct SpotLight{
    vec3  position;
    vec3  direction;
    
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// 输入
// 片段位置
in vec3 FragPos;
// 片段法向量
in vec3 Normal;
// 纹理坐标
in vec2 TexCoords;

// 输出
// 片段颜色
out vec4 FragColor;

// uniform 变量
// 点光源数组
uniform PointLight pointLights[NR_POINT_LIGHTS];
// 平行光光源
uniform DirLight dirLight;
// 聚光灯
uniform SpotLight spotLight;
// 摄像机位置
uniform vec3 viewPos;
// 物体材质
uniform Material material;

// 声明函数
// 计算平行光
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
// 计算点光源
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
// 计算聚光灯
vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
    // 属性
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // 第一阶段：定向光照
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // 第二阶段：点光源
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // 第三阶段：聚光
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    

    FragColor = vec4(result, 1.0);
}

// 函数定义

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 fragPos, vec3 viewDir){

    vec3 lightDir = normalize(spotLight.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并结果
    vec3 ambient  = spotLight.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = spotLight.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = spotLight.specular * spec * vec3(texture(material.specular, TexCoords));
    // 平滑边缘
    float theta = dot(lightDir, normalize(-spotLight.direction)); 
    float epsilon = (spotLight.cutOff - spotLight.outerCutOff);
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    // 随距离衰减
    float distance    = length(spotLight.position - fragPos);
    float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}