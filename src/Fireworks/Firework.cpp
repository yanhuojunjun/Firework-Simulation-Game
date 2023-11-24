#include "Firework.h"

Firework::Firework() {

}
void Firework::SetRender(std::shared_ptr<Emitter_Render> render) {
    emitter_render = render;
}

Firework_0::Firework_0(
    std::shared_ptr<Emitter_Render> render,
    float init_v,
    glm::vec3 init_pos,
    glm::vec3 init_dire,
    glm::vec4 init_color,
    int64_t b_time
) {
    Init(render, init_v, init_pos, init_dire, init_color, b_time);
}

void Firework_0::Init(
    std::shared_ptr<Emitter_Render> render,
    float init_v,
    glm::vec3 init_pos,
    glm::vec3 init_dire,
    glm::vec4 init_color,
    int64_t b_time
) {
    SetRender(render);
    generate_index = 0;
    max_emitter_number = 10;
    initial_velocity = init_v;
    emission_direction = init_dire;
    emission_color = init_color;
    boom_time = b_time;
    core_emitter = std::make_shared<ParticleEmitter>(
        80,                                   // 最大粒子数
        b_time,
        init_pos,                     // 粒子发射器中心
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),      // 粒子颜色
        100,                                     // 粒子大小
        500,                                    // 粒子生命周期
        0.01f,                                      // 粒子初速度
        glm::normalize(glm::vec3(0, -1, 0)),        // 粒子初始方向
        glm::vec3(0, -0.005, 0),                     // 粒子加速度
        10,                                     // 粒子发射间隔
        0,                                      // 纹理
        init_v,                                    // 发射器移动速度
        init_dire,            // 发射器运动方向
        glm::vec3(0.0f, -0.1f, 0.0f),            // 发射器加速度
        EmitterType::Sphere,                    // 粒子发射器类型
        0.0f,                                       // 圆形粒子发射器-半径
        DirectionType::Outer                  // 圆形粒子发射器-朝向类型
    );
    core_emitter->EnableVelocityUpdater(1.0f, 0.0f);
    core_emitter->AddMidVelocity(0.0, 0.7);
    render->AddEmitter(core_emitter);
    particle_emitters.resize(max_emitter_number);
}

bool Firework_0::Update(uint64_t delta_time) {
    // 爆炸前进行倒计时
    if (boom_time > 0) {
        boom_time -= delta_time;
        if (boom_time <= 0) {
            for (int i = 0;i < max_emitter_number;i++) {
                particle_emitters[i] = std::make_shared<ParticleEmitter>(
                    50,                                   // 最大粒子数
                    2000,                                  // 发射器生命
                    core_emitter->GetEmitterCenter(),      // 粒子发射器中心
                    glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),      // 粒子颜色
                    200,                                     // 粒子大小
                    2000,                                    // 粒子生命周期
                    1.0f,                                      // 粒子初速度
                    glm::normalize(glm::vec3(0, 1, 0)),        // 粒子初始方向
                    glm::vec3(0, -0.005, 0),                     // 粒子加速度
                    30,                                     // 粒子发射间隔
                    0,                                      // 纹理
                    5.0f,                                    // 发射器移动速度
                    glm::sphericalRand(1.0f),// 发射器运动方向
                    glm::vec3(0.0f, -0.01f, 0.0f),            // 发射器加速度
                    EmitterType::Sphere,                    // 粒子发射器类型
                    0.0f,                                       // 圆形粒子发射器-半径
                    DirectionType::Outer                  // 圆形粒子发射器-朝向类型
                );
                particle_emitters[i]->EnableColorUpdater(emission_color, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
                //particle_emitters[i]->AddMidColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.7f), 0.7);
                particle_emitters[i]->EnableLifetimeTolerance(0.2);
                //emitter->EnableOneShoot();
                emitter_render->AddEmitter(particle_emitters[i]);
            }
            // 爆炸后 使 core 粒子发射器失效
            //core_emitter->Invalidate();
        }
        return true;
    }
    else {
        // 计算失效的粒子发射器数量
        uint32_t count = 0;
        for (auto it : particle_emitters) {
            if (!it->isValid()) count++;
        }
        if (count == max_emitter_number) return false;
        else return true;
    }
    return true;
}

Firework_1::Firework_1(
    std::shared_ptr<Emitter_Render> render,
    float init_v,
    glm::vec3 init_pos,
    glm::vec3 init_dire,
    glm::vec4 init_color,
    int64_t b_time
) {
    Init(render, init_v,init_pos, init_dire,init_color, b_time);
}

void Firework_1::Init(
    std::shared_ptr<Emitter_Render> render,
    float init_v,
    glm::vec3 init_pos,
    glm::vec3 init_dire,
    glm::vec4 init_color,
    int64_t b_time
) {
    SetRender(render);
    generate_index = 0;
    max_emitter_number = 1;
    initial_velocity = init_v;
    emission_direction = init_dire;
    emission_color = init_color;
    boom_time = b_time;

    core_emitter = std::make_shared<ParticleEmitter>(
        80,                  // 最大粒子数
        b_time,             // 发射器生命周期
        init_pos,            // 粒子发射器中心
        glm::vec4(1.0f),      // 粒子颜色
        100,                                     // 粒子大小
        500,                                    // 粒子生命周期
        0.01f,                                      // 粒子初速度
        glm::normalize(glm::vec3(0, -1, 0)),        // 粒子初始方向
        glm::vec3(0, -0.005, 0),                     // 粒子加速度
        10,                                     // 粒子发射间隔
        0,                                      // 纹理
        init_v,               // 发射器移动速度
        init_dire,            // 发射器运动方向
        glm::vec3(0.0f, -0.2f, 0.0f),   // 发射器加速度
        EmitterType::Sphere,                    // 粒子发射器类型
        0.0f,                                       // 圆形粒子发射器-半径
        DirectionType::Outer                  // 圆形粒子发射器-朝向类型
    );
    core_emitter->EnableVelocityUpdater(1.0f, 0.0f);
    core_emitter->AddMidVelocity(0.0, 0.7);
    render->AddEmitter(core_emitter);
    particle_emitters.resize(max_emitter_number);
}

bool Firework_1::Update(uint64_t delta_time) {
    // 爆炸前进行倒计时
    if (boom_time > 0) {
        boom_time -= delta_time;
        if (boom_time <= 0) {
            for (int i = 0;i < max_emitter_number;i++) {
                particle_emitters[i] = std::make_shared<ParticleEmitter>(
                    1000,                                   // 最大粒子数
                    3000,
                    core_emitter->GetEmitterCenter(),      // 粒子发射器中心
                    glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),      // 粒子颜色
                    150,                                     // 粒子大小
                    6000,                                    // 粒子生命周期
                    5.0f,                                      // 粒子初速度
                    glm::normalize(glm::vec3(0, 1, 0)),        // 粒子初始方向
                    glm::vec3(0, -2.0, 0),                     // 粒子加速度
                    10,                                     // 粒子发射间隔
                    0,                                      // 纹理
                    0.0f,                                    // 发射器移动速度
                    glm::vec3(0, 1, 0),            // 发射器运动方向
                    glm::vec3(0.0f, 0.0f, 0.0f),            // 发射器加速度
                    
                    EmitterType::Sphere,                    // 粒子发射器类型
                    0.0f,                                       // 圆形粒子发射器-半径
                    DirectionType::Outer                  // 圆形粒子发射器-朝向类型
                );
                particle_emitters[i]->EnableColorUpdater(emission_color, glm::vec4(0.0f, 0.2f, 0.1f, 0.1f));
                particle_emitters[i]->AddMidColor(0.7f*emission_color, 0.5);
                particle_emitters[i]->EnableLifetimeTolerance(0.2);
                particle_emitters[i]->EnableOneShoot();
                particle_emitters[i]->EnableVelocityUpdater(5.0f, 0.0f);
                particle_emitters[i]->AddMidVelocity(1.0f, 0.4f);
                emitter_render->AddEmitter(particle_emitters[i]);
            }
            // 爆炸后 使 core 粒子发射器失效
            //core_emitter->Invalidate();
        }
        return true;
    }
    else {
        // 计算失效的粒子发射器数量
        uint32_t count = 0;
        for (auto it : particle_emitters) {
            if (!it->isValid()) count++;
        }
        if (count == max_emitter_number) return false;
        else return true;
    }
    return true;
}

Firework_2::Firework_2(
    std::shared_ptr<Emitter_Render> render,
    float init_v,
    glm::vec3 init_pos,
    glm::vec3 init_dire,
    glm::vec4 init_color,
    int64_t b_time
) {
    Init(render, init_v, init_pos, init_dire, init_color, b_time);
}

void Firework_2::Init(
    std::shared_ptr<Emitter_Render> render,
    float init_v,
    glm::vec3 init_pos,
    glm::vec3 init_dire,
    glm::vec4 init_color,
    int64_t b_time
) {
    SetRender(render);
    generate_index = 0;
    max_emitter_number = 10;
    initial_velocity = init_v;
    emission_direction = init_dire;
    emission_color = init_color;
    boom_time = b_time;

    core_emitter = std::make_shared<ParticleEmitter>(
        80,                                   // 最大粒子数
        b_time,
        init_pos,                     // 粒子发射器中心
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),      // 粒子颜色
        100,                                     // 粒子大小
        500,                                    // 粒子生命周期
        0.01f,                                      // 粒子初速度
        glm::normalize(glm::vec3(0, -1, 0)),        // 粒子初始方向
        glm::vec3(0, -0.005, 0),                     // 粒子加速度
        10,                                     // 粒子发射间隔
        0,                                      // 纹理
        init_v,                                    // 发射器移动速度
        init_dire,            // 发射器运动方向
        glm::vec3(0.0f, -0.1f, 0.0f),            // 发射器加速度
        EmitterType::Sphere,                    // 粒子发射器类型
        0.0f,                                       // 圆形粒子发射器-半径
        DirectionType::Outer                  // 圆形粒子发射器-朝向类型
    );
    core_emitter->EnableVelocityUpdater(1.0f, 0.0f);
    core_emitter->AddMidVelocity(0.0, 0.7);
    core_emitter->EnableRadialAcc(100.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    render->AddEmitter(core_emitter);
    particle_emitters.resize(max_emitter_number);
}

bool Firework_2::Update(uint64_t delta_time) {
    // 爆炸前进行倒计时
    if (boom_time > 0) {
        boom_time -= delta_time;
        if (boom_time <= 0) {
            for (int i = 0;i < max_emitter_number;i++) {
                particle_emitters[i] = std::make_shared<ParticleEmitter>(
                    50,                                   // 最大粒子数
                    3000,                                  // 发射器生命
                    core_emitter->GetEmitterCenter(),      // 粒子发射器中心
                    glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),      // 粒子颜色
                    200,                                     // 粒子大小
                    1000,                                    // 粒子生命周期
                    1.0f,                                      // 粒子初速度
                    glm::normalize(glm::vec3(0, 1, 0)),        // 粒子初始方向
                    glm::vec3(0, -0.005, 0),                     // 粒子加速度
                    30,                                     // 粒子发射间隔
                    0,                                      // 纹理
                    10.0f,                                    // 发射器移动速度
                    glm::sphericalRand(1.0f),// 发射器运动方向
                    glm::vec3(0.0f, -0.01f, 0.0f),            // 发射器加速度
                    EmitterType::Sphere,                    // 粒子发射器类型
                    0.0f,                                       // 圆形粒子发射器-半径
                    DirectionType::Outer                  // 圆形粒子发射器-朝向类型
                );
                particle_emitters[i]->EnableColorUpdater(emission_color, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
                //particle_emitters[i]->AddMidColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.7f), 0.7);
                particle_emitters[i]->EnableLifetimeTolerance(0.2);
                //emitter->EnableOneShoot();
                emitter_render->AddEmitter(particle_emitters[i]);
            }
            // 爆炸后 使 core 粒子发射器失效
            //core_emitter->Invalidate();
        }
        return true;
    }
    else {
        // 计算失效的粒子发射器数量
        uint32_t count = 0;
        for (auto it : particle_emitters) {
            if (!it->isValid()) count++;
        }
        if (count == max_emitter_number) return false;
        else return true;
    }
    return true;
}

Firework_3::Firework_3(
    std::shared_ptr<Emitter_Render> render,
    float init_v,
    glm::vec3 init_pos,
    glm::vec3 init_dire,
    glm::vec4 init_color,
    int64_t b_time
) {
    Init(render, init_v, init_pos, init_dire, init_color, b_time);
}

void Firework_3::Init(
    std::shared_ptr<Emitter_Render> render,
    float init_v,
    glm::vec3 init_pos,
    glm::vec3 init_dire,
    glm::vec4 init_color,
    int64_t b_time
) {
    SetRender(render);
    generate_index = 0;
    max_emitter_number = 10;
    initial_velocity = init_v;
    emission_direction = init_dire;
    emission_color = init_color;
    boom_time = b_time;

    core_emitter = std::make_shared<ParticleEmitter>(
        320,                                   // 最大粒子数
        b_time,
        init_pos,                     // 粒子发射器中心
        emission_color,      // 粒子颜色
        100,                                     // 粒子大小
        3000,                                    // 粒子生命周期
        initial_velocity,                          // 粒子初速度
        emission_direction,        // 粒子初始方向
        glm::vec3(0.0f, -4.0f, 0.0f),                     // 粒子加速度
        10,                                     // 粒子发射间隔
        0,                                      // 纹理
        0.0f,                                    // 发射器移动速度
        init_dire,            // 发射器运动方向
        glm::vec3(0.0f, 0.0f, 0.0f),            // 发射器加速度
        EmitterType::Line,                    // 粒子发射器类型
        0.1f                                       // 线性粒子发射器 散度
    );
    // core_emitter->EnableVelocityUpdater(1.0f, 0.0f);
    // core_emitter->AddMidVelocity(0.0, 0.7);
    render->AddEmitter(core_emitter);
    particle_emitters.resize(max_emitter_number);
}

bool Firework_3::Update(uint64_t delta_time) {
    // 爆炸前进行倒计时
    if (boom_time > 0) {
        boom_time -= delta_time;
        return true;
    }
    else {
        return false;
    }
    return true;
}