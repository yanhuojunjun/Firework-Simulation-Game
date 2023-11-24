#ifndef FIREWORK_H
#define FIREWORK_H

#include "Particle_Emitter.h"
#include "Emitter_Render.h"

#include <vector>

class Firework {
public:
    Firework();
    
    virtual void Init(
        std::shared_ptr<Emitter_Render> render,
        float init_v,
        glm::vec3 init_pos,
        glm::vec3 init_dire,
        glm::vec4 init_color,
        int64_t b_time
        ) = 0;

    // 返回烟花是否还应该存在 即其中的粒子发射器还有粒子未消散
    virtual bool Update(uint64_t delta_time) = 0;
    void SetRender(std::shared_ptr<Emitter_Render> render);
    virtual ~Firework() = default;
protected:
    std::shared_ptr<ParticleEmitter> core_emitter;
    std::vector < std::shared_ptr<ParticleEmitter> > particle_emitters;
    uint32_t generate_index;

    std::shared_ptr<Emitter_Render> emitter_render;
    /**********************
    *       选项          *
    **********************/
    uint32_t max_emitter_number;
    float initial_velocity;         // 初速度
    glm::vec3 emission_direction;   // 初始方向
    glm::vec3 emission_position;    // 初始位置
    glm::vec4 emission_color;       // 粒子初始颜色
    int64_t boom_time;              // 爆炸倒计时
    
    // uint64_t emission_delta_time;   // 

    // 默认一次性
    // bool one_shot;


};

class Firework_0 :public Firework {
public:
    Firework_0() = default;
    Firework_0(
        std::shared_ptr<Emitter_Render> render,
        float init_v,
        glm::vec3 init_pos,
        glm::vec3 init_dire,
        glm::vec4 init_color,
        int64_t b_time
    );
    void Init(
        std::shared_ptr<Emitter_Render> render,
        float init_v,
        glm::vec3 init_pos,
        glm::vec3 init_dire,
        glm::vec4 init_color,
        int64_t b_time
    ) override;
    bool Update(uint64_t delta_time) override;
};


// 随机球形烟花 使用一个粒子发射器
class Firework_1 :public Firework {
public:
    Firework_1() = default;
    Firework_1(
        std::shared_ptr<Emitter_Render> render,
        float init_v,
        glm::vec3 init_pos,
        glm::vec3 init_dire,
        glm::vec4 init_color,
        int64_t b_time
    );
    void Init(
        std::shared_ptr<Emitter_Render> render,
        float init_v,
        glm::vec3 init_pos,
        glm::vec3 init_dire,
        glm::vec4 init_color,
        int64_t b_time
    ) override;
    bool Update(uint64_t delta_time) override;
};

// 螺旋上升烟花
class Firework_2 :public Firework {
public:
    Firework_2() = default;
    Firework_2(
        std::shared_ptr<Emitter_Render> render,
        float init_v,
        glm::vec3 init_pos,
        glm::vec3 init_dire,
        glm::vec4 init_color,
        int64_t b_time
    );
    void Init(
        std::shared_ptr<Emitter_Render> render,
        float init_v,
        glm::vec3 init_pos,
        glm::vec3 init_dire,
        glm::vec4 init_color,
        int64_t b_time
    ) override;
    bool Update(uint64_t delta_time) override;
};

// 喷泉烟花
class Firework_3 :public Firework {
public:
    Firework_3() = default;
    Firework_3(
        std::shared_ptr<Emitter_Render> render,
        float init_v,
        glm::vec3 init_pos,
        glm::vec3 init_dire,
        glm::vec4 init_color,
        int64_t b_time
    );
    void Init(
        std::shared_ptr<Emitter_Render> render,
        float init_v,
        glm::vec3 init_pos,
        glm::vec3 init_dire,
        glm::vec4 init_color,
        int64_t b_time
    ) override;
    bool Update(uint64_t delta_time) override;
};
#endif