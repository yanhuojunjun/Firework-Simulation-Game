#ifndef PARTICLE_RENDER_H
#define PARTICLE_RENDER_H

#include "glad.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Shader.h"
#include "Camera_SDL.h"

#include <vector>

#include "particle.h"
#include "circle_firework.h"

class firework_render
{
public:
    firework_render(ICamera* cam); //创建shader，连接camera，创建VAO VBO，生成纹理
    void add_group(particle_group* new_group); //增加粒子群
    void update_and_collect(int64_t millisecond_passby); //更新所有粒子的信息，自动删除死亡的粒子群，收集所有粒子的信息
    void render(); //渲染粒子
    ~firework_render(); //删除shader，vao，vbo
protected:
    std::vector<float> vbo_buffer; // 缓存所有粒子的数据
    unsigned int VAO;
    unsigned int VBO;
    Shader shader;
    ICamera* camera;
    unsigned int texture;
    std::vector<particle_group*> particle_groups; // 需要渲染的所有的粒子群
};


#endif