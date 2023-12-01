#ifndef ANIMATION_H
#define ANIMATION_H

#include "Pipe_Firework_Manager.h"

#ifdef SDL2_LIB
#include "SDL.h"
#else
#include "glfw3.h"
#endif

// 睡眠时间
union sleep_time {
    int64_t sdl_sleep_time;
    double glfw_sleep_time;
};

struct Animation_Frame {
    // 参数列表
    int32_t firework_type;
    float firework_init_v;
    glm::vec3 firework_init_pos;
    glm::vec3 firework_init_dire;
    glm::vec4 firework_init_color;
    int64_t firework_b_time;
    // 帧休眠时间
    sleep_time total_sleep_time;
    // 构造
    Animation_Frame(
        int32_t _firework_type,
        float _firework_init_v,
        glm::vec3 _firework_init_pos,
        glm::vec3 _firework_init_dire,
        glm::vec4 _firework_init_color,
        int64_t _firework_b_time,
        sleep_time _total_sleep_time
    ) :firework_type(_firework_type),
        firework_init_v(_firework_init_v),
        firework_init_pos(_firework_init_pos),
        firework_init_dire(_firework_init_dire),
        firework_init_color(_firework_init_color),
        firework_b_time(_firework_b_time),
        total_sleep_time(_total_sleep_time) {}
};

class Animation {
protected:
    // 动画状态
    bool playing;
    bool end;
    // 动画事件帧
    std::vector<Animation_Frame> frames;
    int32_t frame_now_index; // 当前所在的帧下标
    // 剩余睡眠时间
    sleep_time h_sleep_time;
    //
    std::shared_ptr<Pipe_Firework_Manager> manager;
public:
    Animation(std::shared_ptr<Pipe_Firework_Manager> _manager, int n = 0);
    void Add_Frame(const Animation_Frame& new_frame);
    void Play(double delta_time);
    void Play(uint64_t delta_time);
    virtual ~Animation();
protected:

    void Use_Param();


};

#endif