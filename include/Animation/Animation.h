#ifndef ANIMATION_H
#define ANIMATION_H

#include "Pipe_Firework_Manager.h"

#ifdef SDL2_LIB
#include "SDL.h"
#else
#include "glfw3.h"
#endif

struct Animation_Frame;

typedef std::function<void(std::shared_ptr<Pipe_Firework_Manager>)> FrameFunction;

// 睡眠时间
union sleep_time {
    int64_t sdl_sleep_time;
    double glfw_sleep_time;
};

struct Animation_Frame {
    // 帧行为
    FrameFunction func;
    // 帧休眠时间
    sleep_time total_sleep_time;
    // 构造
    Animation_Frame() = default;
    Animation_Frame(
        FrameFunction _func,
        sleep_time _total_sleep_time
    ) : func(_func),
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
    virtual void Build() = 0;
    void Play(double delta_time);
    void Play(uint64_t delta_time);
    virtual ~Animation();
};

#endif