#include "Animation.h"

Animation::Animation(std::shared_ptr<Pipe_Firework_Manager> _manager, int n) {
    playing = false;
    end = false;
    frame_now_index = 0;
    if (!frames.empty()) frames.clear();
#ifdef SDL2_LIB
    h_sleep_time.sdl_sleep_time = 0;
#else
    h_sleep_time.glfw_sleep_time = 0.0;
#endif
    manager = _manager;
}

void Animation::Play(double delta_time) {
    if (frame_now_index == frames.size()) return; // 避免数组越界
    h_sleep_time.glfw_sleep_time -= delta_time;
    while (h_sleep_time.glfw_sleep_time <= 0 && frame_now_index < frames.size()) {
        h_sleep_time.glfw_sleep_time += frames[frame_now_index].total_sleep_time.glfw_sleep_time;
        frames[frame_now_index].func(manager);
        ++frame_now_index;
    }
}

void Animation::Play(uint64_t delta_time) {
    if (frame_now_index == frames.size()) return; // 避免数组越界
    h_sleep_time.sdl_sleep_time -= delta_time;
    while (h_sleep_time.sdl_sleep_time <= 0 && frame_now_index < frames.size()) {
        h_sleep_time.sdl_sleep_time += frames[frame_now_index].total_sleep_time.sdl_sleep_time;
        frames[frame_now_index].func(manager);
        ++frame_now_index;
    }
}

Animation::~Animation() {}