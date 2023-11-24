#ifndef FIREWORK_MANAGER_H
#define FIREWORK_MANAGER_H

#include <map>
#include <stack>
#include <vector>
#include <memory>

#include "Emitter_Render.h"

#include "Firework.h"

class Firework_Manager {
protected:
    // 目前有效的烟花个数
    int32_t firework_count;
    // 使用过但被弃用的序号
    std::stack<int32_t> firework_number_unused;
    // 序号 -> 烟花 的一一映射
    std::map<int32_t, std::shared_ptr<Firework> > fireworks;
    // 粒子渲染器
    std::shared_ptr<Emitter_Render> render;
public:
    Firework_Manager(std::shared_ptr<Emitter_Render> _render);
    // 根据烟花的类名后缀创建一个烟花
    int32_t Register_Firework(
        int32_t _type,
        float init_v,
        glm::vec3 init_pos,
        glm::vec3 init_dire,
        glm::vec4 init_color,
        int64_t b_time
    );
    // 进行烟花的爆炸倒计时
    void Update(uint64_t deltatime);
protected:
    // 取得一个没有被使用的序号
    int32_t Firework_Number();
};

#endif