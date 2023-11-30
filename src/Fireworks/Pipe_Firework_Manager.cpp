#include "Pipe_Firework_Manager.h"

Pipe_Firework_Manager::Pipe_Firework_Manager(
    std::shared_ptr<Emitter_Render> _render
#ifdef SDL2_LIB
    ,std::shared_ptr<Sound_Player> _player
#endif
) {
    if (fireworks.size() != 0) fireworks.clear();
    render = _render;
#ifdef SDL2_LIB
    player = _player;
#endif
}

int32_t Pipe_Firework_Manager::Register_Firework(
    int32_t _type,
    float init_v,
    glm::vec3 init_pos,
    glm::vec3 init_dire,
    glm::vec4 init_color,
    int64_t b_time
) {
    fireworks.push_back(std::make_shared<Pipe_Firework>(
        _type,
        render,
#ifdef SDL2_LIB
        player,
#endif
        init_v,
        init_pos,
        init_dire,
        init_color,
        b_time
    ));
}

void Pipe_Firework_Manager::Update(uint64_t deltatime) {
#pragma omp parallel for
    for (int i = 0;i < fireworks.size();i++) {
        fireworks[i]->Update(deltatime);
        //std::cout << "thread:" << omp_get_thread_num() << std::endl;
    }

    for (auto it = fireworks.begin();it != fireworks.end();) {
        if ((*it)->isValid()) ++it;// 如果烟花中还有节点需要更新 就保留
        else it = fireworks.erase(it); // 否则删除该烟花
    }
}

Pipe_Firework_Manager::~Pipe_Firework_Manager() {}