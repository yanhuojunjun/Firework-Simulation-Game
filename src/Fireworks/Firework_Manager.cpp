#include "Firework_Manager.h"

Firework_Manager::Firework_Manager(std::shared_ptr<Emitter_Render> _render) {
    firework_count = 0;
    while (!firework_number_unused.empty()) firework_number_unused.pop();
    fireworks.clear();
    render = _render;
    
}

int32_t Firework_Manager::Register_Firework(
    int32_t _type,
    float init_v,
    glm::vec3 init_pos,
    glm::vec3 init_dire,
    glm::vec4 init_color,
    int64_t b_time
) {
    switch (_type) {
    case 0: {
        int32_t number = Firework_Number();
        fireworks[number] = std::make_shared<Firework_0>(
            render,      // 渲染器
            init_v,           // 初始速度
            init_pos,      // 初始位置
            init_dire,     // 初始方向
            init_color,     // 初始颜色
            b_time
        );
        firework_count++;
        return number;
    }
    case 1: {
        int32_t number = Firework_Number();
        fireworks[number] = std::make_shared<Firework_1>(
            render,
            init_v,          // 初始速度
            init_pos,     // 初始位置
            init_dire,     // 初始方向
            init_color,     // 初始颜色
            b_time
        );
        firework_count++;
        return number;
    }
    case 2: {
        int32_t number = Firework_Number();
        fireworks[number] = std::make_shared<Firework_2>(
            render,
            init_v,          // 初始速度
            init_pos,     // 初始位置
            init_dire,     // 初始方向
            init_color,     // 初始颜色
            b_time
        );
        firework_count++;
        return number;
    }
    case 3: {
        int32_t number = Firework_Number();
        fireworks[number] = std::make_shared<Firework_3>(
            render,
            init_v,          // 初始速度
            init_pos,     // 初始位置
            init_dire,     // 初始方向
            init_color,     // 初始颜色
            b_time
        );
        firework_count++;
        return number;
    }
    default:
        return -1;
    }
}

void Firework_Manager::Update(uint64_t deltatime) {
    // 为每一个烟花进行爆炸倒计时
    for (auto it = fireworks.begin();it != fireworks.end();) {
        if (!it->second->Update(deltatime)) {
            it = fireworks.erase(it);
            --firework_count;
        }
        else ++it;
    }
}

int32_t Firework_Manager::Firework_Number() {
    if (!firework_number_unused.empty()) {
        int32_t num = firework_number_unused.top();
        firework_number_unused.pop();
        return num;
    }
    else {
        return firework_count;
    }
}