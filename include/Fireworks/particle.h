#ifndef PARTICLE_H
#define PARTICLE_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Path_Generator.h"

#include <vector>
#include <iostream>
/* *****************************************
*                 粒子                     *
*******************************************/
class particle {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec4 color;
    int64_t HP; // 粒子剩余存活时间(毫秒)
public:
    particle() = default;
    particle(const glm::vec3& pos, const glm::vec3& v, const glm::vec4& col, int64_t hp);
    // 更新存活时间 返回是否存活
    bool update(int64_t millisecond_passby);
    // 返回是否存活
    bool alive();
};

/* *****************************************
*                 粒子群                   *
*******************************************/

class particle_group {
public:
    particle_group() = default;
    void init(uint32_t max_px, const particle& origin_px);
    void generate(const particle& new_px);
    // 更新粒子位置与颜色
    virtual void update(int64_t millisecond_passby);
    virtual ~particle_group();
protected:
    uint64_t birth_millisecond;
    uint32_t max_alive_particle_number;
    uint32_t last_generate_index;
    std::vector<particle> particles;
};

/* *****************************************
*               粒子生成器                  *
*******************************************/
namespace particle_generator {
    // px 粒子群 dire 父粒子前进的方向 num 产生的粒子数量 sp 子粒子的初速度 col 子粒子的颜色 hp 子粒子存活时间
    void circle_surround(particle_group* px, const particle& root, int num, float sp = 1.0f, const glm::vec4& col = glm::vec4(1.0f), int64_t hp = 10000);

};


#endif