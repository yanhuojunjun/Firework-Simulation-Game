#include "Firework_Pipeline.h"

Pipe_Firework::Pipe_Firework(
    int type,
    std::shared_ptr<Emitter_Render> render,
#ifdef SDL2_LIB
    std::shared_ptr<Sound_Player> player,
#endif
    float init_v,
    glm::vec3 init_pos,
    glm::vec3 init_dire,
    glm::vec4 init_color,
    int64_t b_time,
    int32_t _init_node_type
) {
    SetRender(render);
#ifdef SDL2_LIB
    SetPlayer(player);
#endif
    std::shared_ptr<ParticleEmitter> first_emitter = std::make_shared<ParticleEmitter>();
    switch (_init_node_type)
    {
    case 0:
        first_emitter->SetParticleEmitter(
            80,                                         // 最大粒子数
            b_time,                                     // 粒子发射器生命值
            init_pos,                                   // 粒子发射器中心
            4.0f * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),   // 粒子颜色
            100,                                        // 粒子大小
            500,                                        // 粒子生命周期
            0.01f,                                      // 粒子初速度
            glm::vec3(0, -1, 0),                        // 粒子初始方向
            glm::vec3(0, -0.005, 0),                    // 粒子加速度
            10,                                         // 粒子发射间隔
            0,                                          // 纹理
            init_v,                                     // 发射器移动速度
            init_dire,                                  // 发射器运动方向
            glm::vec3(0.0f, -0.1f, 0.0f),               // 发射器加速度
            EmitterType::Sphere,                        // 粒子发射器类型
            0.0f,                                       // 圆形粒子发射器-半径
            DirectionType::Outer                        // 圆形粒子发射器-朝向类型
        );
        first_emitter->EnableVelocityUpdater(1.0f, 0.0f);
        first_emitter->AddMidVelocity(0.0, 0.7);
        first_emitter->EnableColorUpdater(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        first_emitter->AddMidColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.5);
        first_emitter->EnableLifetimeTolerance(0.2);
        break;
    case 1:
        first_emitter->SetParticleEmitter(
            500,                                   // 最大粒子数
            b_time,                                        // 发射器生命
            init_pos,      // 粒子发射器中心
            4.0f * glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),      // 粒子颜色
            150,                                     // 粒子大小
            1500,                                    // 粒子生命周期
            0.1f,                                      // 粒子初速度
            glm::normalize(glm::vec3(0, 1, 0)),        // 粒子初始方向
            glm::vec3(0.0f, -0.001f, 0.0f),                     // 粒子加速度
            10,                                     // 粒子发射间隔
            0,                                      // 纹理
            init_v,                                    // 发射器移动速度
            init_dire,            // 发射器运动方向
            glm::vec3(0.0f, 0.0f, 0.0f),            // 发射器加速度
            EmitterType::Sphere,                    // 粒子发射器类型
            0.03f,                                       // 圆形粒子发射器-半径
            DirectionType::Outer                  // 圆形粒子发射器-朝向类型
        );
        first_emitter->EnableColorUpdater(glm::vec4(1.0f, 0.7f, 0.5f, 1.0f), glm::vec4(0.0f, 0.2f, 0.1f, 0.1f));
        first_emitter->AddMidColor(0.7f * glm::vec4(1.0f, 0.7f, 0.5f, 1.0f), 0.7);
        first_emitter->EnableLifetimeTolerance(0.2);
        first_emitter->EnableLifetimeUpdater(4000, 2500);
        break;
    default:
        break;
    }
    

    Firework_Pipeline_Node first_node(
        false,
        first_emitter,
        pipe_end
    );
    
    switch (type) {
    case 0:
        first_node.Create_Next = pipe0_0;
#ifdef SDL2_LIB
        sound_player->PlayOne(Sound_Type::FLY);
#endif
        break;
    case 1:
        first_node.Create_Next = pipe1_0;
        break;
    case 2:
        first_node.Create_Next = pipe2_0;
        break;
    case 3:
        first_node.Create_Next = pipe1_0;
        break;
    default:
        break;
    }

    nodes.push_front(first_node);
    render->AddEmitter(first_emitter);
    // 光源
    boom_lighting = false;
    light_pos = glm::vec3(0.0f);
    light_col = glm::vec3(0.0f);
}

bool Pipe_Firework::Update(uint64_t delta_ms) {
    for (auto it = nodes.begin();it != nodes.end();) {
        if (it->particle_emitter->Update(delta_ms)) {
            if (!it->particle_emitter->isAlive() && !it->created_next) {
                it->created_next = true;
                if (it->Create_Next(nodes, emitter_render, (*it))) { // 需要产生光源
                    boom_lighting = true;
#ifdef SDL2_LIB
                    sound_player->PlayOne(Sound_Type::BOOM);
#endif
                    light_pos = it->particle_emitter->GetEmitterCenter();
                    light_col = it->particle_emitter->GetEmitterColor();
                }
            }
            ++it;
        }
        else {
            it = nodes.erase(it);
            boom_lighting = false;
        }
    }
    if (boom_lighting) {    // 将光源信息传递给 render
        emitter_render->AddPointLight(light_pos, light_col);
    }
    return !nodes.empty();
}

bool Pipe_Firework::isValid() {
    return !nodes.empty();
}

void Pipe_Firework::SetRender(std::shared_ptr<Emitter_Render> render) {
    emitter_render = render;
}
#ifdef SDL2_LIB
void Pipe_Firework::SetPlayer(std::shared_ptr<Sound_Player> player) {
    sound_player = player;
}

#endif

bool pipe_end(std::list<Firework_Pipeline_Node>& nodes, std::shared_ptr<Emitter_Render> render, Firework_Pipeline_Node& father) {
    return false;
}

/***********************************************************************
 *                      烟花 0                                         *
***********************************************************************/

bool pipe0_0(std::list<Firework_Pipeline_Node>& nodes, std::shared_ptr<Emitter_Render> render, Firework_Pipeline_Node& father) {
    Firework_Pipeline_Node new_node;
    for (int i = 0;i < 10;i++) {
        new_node.created_next = false;
        // 设置粒子发射器
        new_node.particle_emitter = std::make_shared<ParticleEmitter>(
            50,                                   // 最大粒子数
            2000,                                  // 发射器生命
            father.particle_emitter->GetEmitterCenter(),      // 粒子发射器中心
            4.0f*glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),      // 粒子颜色
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
        new_node.particle_emitter->EnableColorUpdater(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
        new_node.particle_emitter->EnableLifetimeTolerance(0.2);
        // 设置下一节点
        new_node.Create_Next = pipe0_1;
        // 添加到节点列表
        nodes.push_front(new_node);
        // 添加到渲染器
        render->AddEmitter(new_node.particle_emitter);
    }
    return true;
}

bool pipe0_1(std::list<Firework_Pipeline_Node>& nodes, std::shared_ptr<Emitter_Render> render, Firework_Pipeline_Node& father) {
    Firework_Pipeline_Node new_node;
    new_node.created_next = false;
    // 设置粒子发射器
    new_node.particle_emitter = std::make_shared<ParticleEmitter>(
        50,                                   // 最大粒子数
        100,                                    // 发射器生命值
        father.particle_emitter->GetEmitterCenter(),      // 粒子发射器中心
        4.0f * glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),      // 粒子颜色
        150,                                     // 粒子大小
        3000,                                    // 粒子生命周期
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
    new_node.particle_emitter->EnableColorUpdater(glm::vec4(1.0f, 0.7f, 0.5f, 1.0f), glm::vec4(0.0f, 0.2f, 0.1f, 0.1f));
    new_node.particle_emitter->AddMidColor(0.7f * glm::vec4(1.0f, 0.7f, 0.5f, 1.0f), 0.7);
    new_node.particle_emitter->EnableLifetimeTolerance(0.2);
    new_node.particle_emitter->EnableOneShoot();
    new_node.particle_emitter->EnableVelocityUpdater(5.0f, 0.0f);
    new_node.particle_emitter->AddMidVelocity(1.0f, 0.4f);
    // 设置下一节点
    new_node.Create_Next = pipe0_2;
    // 添加到节点列表
    nodes.push_front(new_node);
    // 添加到渲染器
    render->AddEmitter(new_node.particle_emitter);
    return false;
}

bool pipe0_2(std::list<Firework_Pipeline_Node>& nodes, std::shared_ptr<Emitter_Render> render, Firework_Pipeline_Node& father) {
    Firework_Pipeline_Node new_node;
    for (int i = 0;i < 3;i++) {
        new_node.created_next = false;
        // 设置粒子发射器
        new_node.particle_emitter = std::make_shared<ParticleEmitter>(
            50,                                   // 最大粒子数
            2000,                                  // 发射器生命
            father.particle_emitter->GetEmitterCenter(),      // 粒子发射器中心
            4.0f * glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),      // 粒子颜色
            100,                                     // 粒子大小
            1500,                                    // 粒子生命周期
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
        new_node.particle_emitter->EnableColorUpdater(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
        new_node.particle_emitter->EnableLifetimeTolerance(0.2);
        // 设置下一节点
        new_node.Create_Next = pipe_end;
        // 添加到节点列表
        nodes.push_front(new_node);
        // 添加到渲染器
        render->AddEmitter(new_node.particle_emitter);
    }
    return false;
}


/***********************************************************************
 *                      烟花 1                                         *
***********************************************************************/

bool pipe1_0(std::list<Firework_Pipeline_Node>& nodes, std::shared_ptr<Emitter_Render> render, Firework_Pipeline_Node& father) {
    Firework_Pipeline_Node new_node;
    for (int i = 0;i < 10;i++) {
        new_node.created_next = false;
        // 设置粒子发射器
        new_node.particle_emitter = std::make_shared<ParticleEmitter>(
            50,                                   // 最大粒子数
            100,                                    // 发射器生命
            father.particle_emitter->GetEmitterCenter(),      // 粒子发射器中心
            4.0f * glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),      // 粒子颜色
            150,                                     // 粒子大小
            3000,                                    // 粒子生命周期
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
        new_node.particle_emitter->EnableColorUpdater(glm::vec4(1.0f, 0.7f, 0.5f, 1.0f), glm::vec4(0.0f, 0.2f, 0.1f, 0.1f));
        new_node.particle_emitter->AddMidColor(0.7f * glm::vec4(1.0f, 0.7f, 0.5f, 1.0f), 0.7);
        new_node.particle_emitter->EnableLifetimeTolerance(0.2);
        new_node.particle_emitter->EnableOneShoot();
        new_node.particle_emitter->EnableVelocityUpdater(5.0f, 0.0f);
        new_node.particle_emitter->AddMidVelocity(1.0f, 0.4f);
        // 设置下一节点
        new_node.Create_Next = pipe_end;
        // 添加到节点列表
        nodes.push_front(new_node);
        // 添加到渲染器
        render->AddEmitter(new_node.particle_emitter);
    }
    return true;
}


/***********************************************************************
 *                      烟花 2                                         *
***********************************************************************/

bool pipe2_0(std::list<Firework_Pipeline_Node>& nodes, std::shared_ptr<Emitter_Render> render, Firework_Pipeline_Node& father) {
    Firework_Pipeline_Node new_node;
    // 球形粒子发射器1
    new_node.created_next = false;
    // 设置粒子发射器
    new_node.particle_emitter = std::make_shared<ParticleEmitter>(
        300,                                   // 最大粒子数
        100,                                    // 发射器生命
        father.particle_emitter->GetEmitterCenter(),      // 粒子发射器中心
        4.0f * glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),      // 粒子颜色
        150,                                     // 粒子大小
        3000,                                    // 粒子生命周期
        3.0f,                                      // 粒子初速度
        glm::normalize(glm::vec3(0, 1, 0)),        // 粒子初始方向
        glm::vec3(0.0f, 0.0f, 0.0f),                     // 粒子加速度
        10,                                     // 粒子发射间隔
        0,                                      // 纹理
        0.0f,                                    // 发射器移动速度
        glm::vec3(0, 1, 0),            // 发射器运动方向
        glm::vec3(0.0f, 0.0f, 0.0f),            // 发射器加速度
        EmitterType::Sphere,                    // 粒子发射器类型
        0.0f,                                       // 圆形粒子发射器-半径
        DirectionType::Outer                  // 圆形粒子发射器-朝向类型
    );
    new_node.particle_emitter->EnableColorUpdater(glm::vec4(1.0f, 0.7f, 0.5f, 1.0f), glm::vec4(0.0f, 0.2f, 0.1f, 0.1f));
    new_node.particle_emitter->AddMidColor(0.7f * glm::vec4(1.0f, 0.7f, 0.5f, 1.0f), 0.7);
    new_node.particle_emitter->EnableLifetimeTolerance(0.2);
    new_node.particle_emitter->EnableOneShoot();
    new_node.particle_emitter->EnableVelocityUpdater(5.0f, 0.0f);
    new_node.particle_emitter->AddMidVelocity(1.0f, 0.4f);
    // 设置下一节点
    new_node.Create_Next = pipe_end;
    // 添加到节点列表
    nodes.push_front(new_node);
    // 添加到渲染器
    render->AddEmitter(new_node.particle_emitter);

    // 球形粒子发射器2
    new_node.created_next = false;
    // 设置粒子发射器
    new_node.particle_emitter = std::make_shared<ParticleEmitter>(
        100,                                   // 最大粒子数
        100,                                    // 发射器生命
        father.particle_emitter->GetEmitterCenter(),      // 粒子发射器中心
        4.0f * glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),      // 粒子颜色
        150,                                     // 粒子大小
        3000,                                    // 粒子生命周期
        0.1f,                                      // 粒子初速度
        glm::normalize(glm::vec3(0, 1, 0)),        // 粒子初始方向
        glm::vec3(0.0f, 0.0f, 0.0f),                     // 粒子加速度
        10,                                     // 粒子发射间隔
        0,                                      // 纹理
        0.0f,                                    // 发射器移动速度
        glm::vec3(0, 1, 0),            // 发射器运动方向
        glm::vec3(0.0f, 0.0f, 0.0f),            // 发射器加速度
        EmitterType::Sphere,                    // 粒子发射器类型
        0.0f,                                       // 圆形粒子发射器-半径
        DirectionType::Outer                  // 圆形粒子发射器-朝向类型
    );
    new_node.particle_emitter->EnableColorUpdater(glm::vec4(0.5f, 0.7f, 1.0f, 1.0f), glm::vec4(0.0f, 0.1f, 0.2f, 0.1f));
    new_node.particle_emitter->AddMidColor(0.7f * glm::vec4(0.5f, 0.7f, 1.0f, 1.0f), 0.7);
    new_node.particle_emitter->EnableLifetimeTolerance(0.2);
    new_node.particle_emitter->EnableOneShoot();
    new_node.particle_emitter->EnableVelocityUpdater(3.0f, 0.0f);
    new_node.particle_emitter->AddMidVelocity(1.0f, 0.4f);
    // 设置下一节点
    new_node.Create_Next = pipe_end;
    // 添加到节点列表
    nodes.push_front(new_node);
    // 添加到渲染器
    render->AddEmitter(new_node.particle_emitter);

    // 条形粒子发射器
    for (int i = 0;i < 20;i++) {
        new_node.created_next = false;
        // 设置粒子发射器
        new_node.particle_emitter = std::make_shared<ParticleEmitter>(
            500,                                   // 最大粒子数
            2000,                                        // 发射器生命
            father.particle_emitter->GetEmitterCenter(),      // 粒子发射器中心
            4.0f * glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),      // 粒子颜色
            150,                                     // 粒子大小
            1500,                                    // 粒子生命周期
            0.0f,                                      // 粒子初速度
            glm::normalize(glm::vec3(0, 1, 0)),        // 粒子初始方向
            glm::vec3(0.0f, 0.0f, 0.0f),                     // 粒子加速度
            30,                                     // 粒子发射间隔
            0,                                      // 纹理
            2.0f,                                    // 发射器移动速度
            glm::sphericalRand(1.0f),            // 发射器运动方向
            glm::vec3(0.0f, 0.0f, 0.0f),            // 发射器加速度
            EmitterType::Sphere,                    // 粒子发射器类型
            0.005f,                                       // 圆形粒子发射器-半径
            DirectionType::Outer                  // 圆形粒子发射器-朝向类型
        );
        new_node.particle_emitter->EnableColorUpdater(glm::vec4(1.0f, 0.7f, 0.5f, 1.0f), glm::vec4(0.0f, 0.2f, 0.1f, 0.1f));
        new_node.particle_emitter->AddMidColor(0.7f * glm::vec4(1.0f, 0.7f, 0.5f, 1.0f), 0.7);
        new_node.particle_emitter->EnableLifetimeTolerance(0.2);
        new_node.particle_emitter->EnableLifetimeUpdater(2000, 500);
        // 设置下一节点
        new_node.Create_Next = pipe_end;
        // 添加到节点列表
        nodes.push_front(new_node);
        // 添加到渲染器
        render->AddEmitter(new_node.particle_emitter);
    }
    return true;
}

/***********************************************************************
 *                      烟花 3                                         *
***********************************************************************/

bool pipe3_0(std::list<Firework_Pipeline_Node>& nodes, std::shared_ptr<Emitter_Render> render, Firework_Pipeline_Node& father) {
    Firework_Pipeline_Node new_node;

    // 条形粒子发射器
    new_node.created_next = false;
    // 设置粒子发射器
    new_node.particle_emitter = std::make_shared<ParticleEmitter>(
        500,                                   // 最大粒子数
        1500,                                        // 发射器生命
        father.particle_emitter->GetEmitterCenter(),      // 粒子发射器中心
        4.0f * glm::vec4(1.0f, 1.0f, 0.5f, 1.0f),      // 粒子颜色
        150,                                     // 粒子大小
        1500,                                    // 粒子生命周期
        0.0f,                                      // 粒子初速度
        glm::normalize(glm::vec3(0, 1, 0)),        // 粒子初始方向
        glm::vec3(0.0f, 0.0f, 0.0f),                     // 粒子加速度
        10,                                     // 粒子发射间隔
        0,                                      // 纹理
        8.0f,                                    // 发射器移动速度
        glm::vec3(0.0f, 2.0f, 1.0f),            // 发射器运动方向
        glm::vec3(0.0f, 0.0f, 0.0f),            // 发射器加速度
        EmitterType::Sphere,                    // 粒子发射器类型
        0.01f,                                       // 圆形粒子发射器-半径
        DirectionType::Outer                  // 圆形粒子发射器-朝向类型
    );
    new_node.particle_emitter->EnableColorUpdater(glm::vec4(1.0f, 0.7f, 0.5f, 1.0f), glm::vec4(0.0f, 0.2f, 0.1f, 0.1f));
    new_node.particle_emitter->AddMidColor(0.7f * glm::vec4(1.0f, 0.7f, 0.5f, 1.0f), 0.7);
    new_node.particle_emitter->EnableLifetimeTolerance(0.2);
    new_node.particle_emitter->EnableLifetimeUpdater(4000, 2500);
    // new_node.particle_emitter->EnableRadialAcc(10.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    // 设置下一节点
    new_node.Create_Next = pipe_end;
    // 添加到节点列表
    nodes.push_front(new_node);
    // 添加到渲染器
    render->AddEmitter(new_node.particle_emitter);
    
    return true;
}
