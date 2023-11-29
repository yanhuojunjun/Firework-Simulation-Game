#ifndef PIPE_FIREWORK_MANAGER_H
#define PIPE_FIREWORK_MANAGER_H

#include "Firework_Pipeline.h"
#include <omp.h>

class Pipe_Firework_Manager {
protected:
    // 烟花链表
    std::vector<std::shared_ptr<Pipe_Firework>> fireworks;
    // 粒子渲染器
    std::shared_ptr<Emitter_Render> render;
#ifdef SDL2_LIB
    // 音频播放器
    std::shared_ptr<Sound_Player> player;
#endif

public:
    Pipe_Firework_Manager(
        std::shared_ptr<Emitter_Render> _render
#ifdef SDL2_LIB
        , std::shared_ptr<Sound_Player> _player
#endif
    );
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
    ~Pipe_Firework_Manager();
};




#endif