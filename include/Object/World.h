#ifndef WORLD_H
#define WORLD_H
#include "glad.h"
#include "Vertex_Manager.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
class World
{
public:
    // 世界范围 x轴宽度 y轴长度 z轴位置
    glm::vec3 position;
    // 地表颜色
    glm::vec3 color;

    // 重力加速度
    //float g;

    // 顶点数据
    Vertex_Manager v;
    unsigned int VBO, VAO;

public:
    World();

    void Create();

    bool OnGround(glm::vec3 pos);

    void Display();

    ~World();
};

#endif