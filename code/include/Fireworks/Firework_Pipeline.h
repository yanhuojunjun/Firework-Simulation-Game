#ifndef FIREWORK_PIPELINE_H
#define FIREWORK_PIPELINE_H

#include "Particle_Emitter.h"
#include "Emitter_Render.h"
#ifdef SDL2_LIB
#include "Sound_Player.h"
#endif
#include <list>
#include <memory>
#include <functional>
#include <iostream>

// 提前声明
struct Firework_Pipeline_Node;
// 定义节点后继函数
// 创建粒子发射器并添加到渲染器
typedef std::function<bool(std::list<Firework_Pipeline_Node>&, std::shared_ptr<Emitter_Render>, Firework_Pipeline_Node&)> PipelineFunction;

// 烟花流水线节点
struct Firework_Pipeline_Node {
    bool created_next;  // 已经执行过 Create_Next 可以作为流水线的终点 或者设置最后一个节点的 Create_Next 函数为 pipe_end
    std::shared_ptr<ParticleEmitter> particle_emitter;  // 当前节点的粒子发射器
    PipelineFunction Create_Next;    // 粒子发射器 HP < 0 后, 创建后继粒子发射器
    Firework_Pipeline_Node() {
        created_next = false;
        particle_emitter = nullptr;
    }
    Firework_Pipeline_Node(bool _cn, std::shared_ptr<ParticleEmitter> _em, PipelineFunction _fun) {
        created_next = _cn;
        particle_emitter = _em;
        Create_Next = _fun;
    }
};

class Pipe_Firework {
public:
    Pipe_Firework(
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
    );

    bool Update(uint64_t delta_ms);
    bool isValid();
    void SetRender(std::shared_ptr<Emitter_Render> render);
#ifdef SDL2_LIB
    void SetPlayer(std::shared_ptr<Sound_Player> player);
#endif

protected:
    // 烟花节点
    std::list<Firework_Pipeline_Node> nodes;
    // 图像渲染器
    std::shared_ptr<Emitter_Render> emitter_render;
#ifdef SDL2_LIB
    // 音效播放器
    std::shared_ptr<Sound_Player> sound_player;
#endif
    // 爆炸光源
    bool boom_lighting;
    glm::vec3 light_pos, light_col;
};

bool pipe_end(std::list<Firework_Pipeline_Node>&, std::shared_ptr<Emitter_Render>, Firework_Pipeline_Node&);

bool pipe0_0(std::list<Firework_Pipeline_Node>&, std::shared_ptr<Emitter_Render>, Firework_Pipeline_Node&);
bool pipe0_1(std::list<Firework_Pipeline_Node>&, std::shared_ptr<Emitter_Render>, Firework_Pipeline_Node&);
bool pipe0_2(std::list<Firework_Pipeline_Node>&, std::shared_ptr<Emitter_Render>, Firework_Pipeline_Node&);

bool pipe1_0(std::list<Firework_Pipeline_Node>&, std::shared_ptr<Emitter_Render>, Firework_Pipeline_Node&);

bool pipe2_0(std::list<Firework_Pipeline_Node>&, std::shared_ptr<Emitter_Render>, Firework_Pipeline_Node&);

bool pipe3_0(std::list<Firework_Pipeline_Node>&, std::shared_ptr<Emitter_Render>, Firework_Pipeline_Node&);

bool pipe4_0(std::list<Firework_Pipeline_Node>&, std::shared_ptr<Emitter_Render>, Firework_Pipeline_Node&);
#endif