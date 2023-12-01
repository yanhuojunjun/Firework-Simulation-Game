#include "Animation_0.h"

Animation_0::Animation_0(std::shared_ptr<Pipe_Firework_Manager> _manager) :Animation(_manager) {}
void Animation_0::Build() {
    sleep_time space_time;
    // 设置时间
#ifdef SDL2_LIB
    space_time.sdl_sleep_time = 5000;
#else
    space_time.glfw_sleep_time = 5000.0;
#endif
    Add_Frame(Animation_Frame(
        1,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(0.0f, 0.0f, 0.0f),        // 初始位置
        glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  // 初始颜色
        2000,                                // 爆炸倒计时
        space_time                          // 该帧结束后休眠的时间
    ));
    Add_Frame(Animation_Frame(
        1,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(1.0f, 0.0f, 0.0f),        // 初始位置
        glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  // 初始颜色
        2000,                                // 爆炸倒计时
        space_time                     // 该帧结束后休眠的时间
    ));
    Add_Frame(Animation_Frame(
        0,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(1.0f, 0.0f, 1.0f),        // 初始位置
        glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  // 初始颜色
        2000,                                // 爆炸倒计时
        space_time                     // 该帧结束后休眠的时间
    ));
    Add_Frame(Animation_Frame(
        0,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(0.0f, 0.0f, 1.0f),        // 初始位置
        glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  // 初始颜色
        2000,                                // 爆炸倒计时
        space_time                     // 该帧结束后休眠的时间
    ));
    Add_Frame(Animation_Frame(
        0,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(1.0f, 0.0f, 0.0f),        // 初始位置
        glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  // 初始颜色
        2000,                                // 爆炸倒计时
        space_time                     // 该帧结束后休眠的时间
    ));
    Add_Frame(Animation_Frame(
        0,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(0.0f, 0.0f, 1.0f),        // 初始位置
        glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  // 初始颜色
        2000,                                // 爆炸倒计时
        space_time                     // 该帧结束后休眠的时间
    ));
    Add_Frame(Animation_Frame(
        0,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(1.0f, 0.0f, 1.0f),        // 初始位置
        glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  // 初始颜色
        2000,                                // 爆炸倒计时
        space_time                     // 该帧结束后休眠的时间
    ));
}
Animation_0::~Animation_0(){}