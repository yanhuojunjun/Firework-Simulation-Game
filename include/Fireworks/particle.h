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
enum particle_status {
    P_DEAD, // 死亡粒子不进行任何更新
    P_DYING, // 正在死亡的粒子 执行其亡语
    P_ALIVE, // 存活的粒子 进行位置, 速度等更新

    // 预留的
    // 粒子运动的阶段 可进行更加复杂的粒子运动
    P_STAGE0 = 256,
    P_STAGE1,
    P_STAGE2,
    P_STAGE3,
    P_STAGE4,
    P_STAGE5,
    P_STAGE6,
    P_STAGE7,
    P_STAGE8,
    P_STAGE9,
    P_STAGE10,
    P_STAGE11,
    P_STAGE12,
    P_STAGE13,
    P_STAGE14,
    P_STAGE15
};

class particle {
public:
    glm::vec3 position; // 粒子位置
    glm::vec3 velocity; // 粒子速度
    glm::vec4 color; // 粒子颜色
    int64_t HP; // 粒子剩余存活时间(毫秒)
    particle_status state; // 粒子状态
public:
    particle() = default;
    particle(const glm::vec3& pos, const glm::vec3& v, const glm::vec4& col, int64_t hp);
    // 返回是否存活 粒子更新操作
    virtual int update(int64_t millisecond_passby);
    // 返回是否存活
    bool alive();
};

/* *****************************************
*                 粒子群                   *
*******************************************/

class particle_group {
public:
    particle_group() = default;
    // 初始化第一个粒子 万粒之初
    void init(uint32_t max_px, const particle& origin_px);
    // 增加一个新的粒子
    void generate(const particle& new_px);
    // 更新粒子位置与颜色
    virtual void update(int64_t millisecond_passby);
    virtual ~particle_group();
protected:
    uint64_t birth_millisecond; // 粒子群产生的时间(暂时忘记有啥用了)
    uint32_t max_alive_particle_number; // 粒子群容纳的最大粒子数量
    uint32_t last_generate_index; // 上一次生成的粒子在列表中的下标
    std::vector<particle> particles; // 粒子列表
};

/* *****************************************
*               粒子生成器                  *
*******************************************/

namespace particle_generator {
    // px 粒子群 dire 父粒子前进的方向 num 产生的粒子数量 sp 子粒子的初速度 col 子粒子的颜色 hp 子粒子存活时间
    void circle_surround(particle_group* px, const particle& root, int num, float sp = 1.0f, const glm::vec4& col = glm::vec4(1.0f), int64_t hp = 10000);

};


#endif