#ifndef PARTICLE_RENDER_H
#define PARTICLE_RENDER_H

#include "glad.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Shader.h"

#include <vector>

#include "particle.h"

class particle_render
{
public:
    particle_render();

    void AddGroup(particle_group* new_group);
    void DeleteGroup(/*args*/);

    void collect();

    void render();

    ~particle_render();
protected:
    // CPU缓冲 收集所有粒子的信息
    // 输入到VBO_position的顶点数据 位置信息对齐vec4
    std::vector<glm::vec4> position;
    // 输入到VBO_color的顶点数据
    std::vector<glm::vec4> color;

    // 渲染对应的VAO, 需要把所有的VBO绑定到该VAO的不同绑定点
    unsigned int VAO;
    // 分别存放位置与颜色的GPU缓冲
    unsigned int VBO_position, VBO_color;

    // 渲染使用同一个shader
    Shader shader;

    // 需要渲染的所有的粒子群
    std::vector<particle_group*> particle_groups;
};



#endif