#include <iostream>
#include <cmath>
#include <string>

#include "glad.h"
#include "stb_image.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "SkyBox.hpp"
#include "Background.hpp"
#include "Shader.h"
#include "bloom.h"
// 烟花
#include "Pipe_Firework_Manager.h"
#include "Animation_0.h"

unsigned int WIN_WIDTH = 1200;
unsigned int WIN_HEIGHT = 750;
const float FPS = 62.0f;

#ifdef SDL2_LIB
#include "SDL.h"
#include "Firework_Viewer.h"
#else
#include <chrono>
#include <thread>
#include "glfw3.h"
#include "Camera_GLFW.h"
Camera_GLFW camera;
#endif

// 窗口标题
std::string win_title = "video_demo FPS:" + std::to_string(0);

int main(int argc, char* args[]) {

#ifdef SDL2_LIB
    //启动SDL
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        return 1;
    }
    // 初始化 Mixer 可以读取 MP3 格式文件
    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error: %s\n", Mix_GetError());
        SDL_Quit();
        return -1;
    }
    // 打开 Audio
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_CHANNELS, 4096) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "error: %s\n", Mix_GetError());
        Mix_Quit();
        SDL_Quit();
        return -1;
    }
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //设置窗口
    SDL_Window* win = SDL_CreateWindow(win_title.data(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIN_WIDTH, WIN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (win == NULL) {
        std::cout << "Failed to create SDL2 window" << std::endl;
        SDL_Quit();
        return 2;
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_GLContext gl_context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, gl_context);
    SDL_GL_SetSwapInterval(0);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Firework_Viewer camera;
#else
    // 初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // 定义一个窗口
    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, win_title.data(), NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    camera.SetWindow(window);
#endif

    glEnable(GL_BLEND); // 启用混合 可显示透明背景纹理
    glEnable(GL_PROGRAM_POINT_SIZE); // 着色器中可设置点的大小
    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    // 天空盒
    skybox sky(&camera);
    // 地面
    Background background(50, 50, -1.0f, &camera);
    //bloom
    bloom bloom_worker(true, 0.3f, WIN_WIDTH, WIN_HEIGHT);//创建-------------------------
    // 创建渲染器
    std::shared_ptr<Emitter_Render> emitter_render = std::make_shared<Emitter_Render>(&camera);
#ifdef SDL2_LIB
    // 音频播放器
    std::shared_ptr<Sound_Player> sound_player = std::make_shared<Sound_Player>();
    // 创建烟花
    std::shared_ptr<Pipe_Firework_Manager> fw_manager = std::make_shared<Pipe_Firework_Manager>(emitter_render, sound_player);
#else
    // 创建烟花
    std::shared_ptr<Pipe_Firework_Manager> fw_manager = std::make_shared<Pipe_Firework_Manager>(emitter_render);
#endif
    // 构建动画序列帧
    Animation_0 animation_0(fw_manager);
    animation_0.Build();
    sound_player->StartBKSound();
    // 开启Z缓冲
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //图元绘制设置为默认(填充)模式

#ifdef SDL2_LIB
    SDL_Event event;
    bool quit_flag = false;
    uint64_t last_frame_time = SDL_GetTicks64();
    uint64_t now_frame_time = last_frame_time;
    uint64_t delta_frame_time = now_frame_time - last_frame_time;
    float frame_rate = 0.0f;
    uint64_t last_flush_time = 0;

    while (!quit_flag) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit_flag = true;
            camera.ProcessEvent(event);
        }
#else
    double delta_ms = 0;
    double last_frame_ms = glfwGetTime() * 1000.0;
    double current_ms = 0;
    double frame_rate, last_flush_time; // 以 ms 为单位

    while (!glfwWindowShouldClose(window)) {
        camera.HandleEvent();
#endif

        glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // 设置屏幕颜色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除屏幕
        /***************************************************
         *                    更新                         *
        ***************************************************/
#ifdef SDL2_LIB

        // 更新帧时间
        now_frame_time = SDL_GetTicks64();
        delta_frame_time = now_frame_time - last_frame_time;
        // 更新烟花
        animation_0.Play(delta_frame_time);
        fw_manager->Update(delta_frame_time);
        // 更新粒子发射器并渲染
        emitter_render->Update_and_Collect(delta_frame_time);
#else
        current_ms = glfwGetTime() * 1000.0; // 将 glfwGetTime 的秒转换为毫秒
        delta_ms = current_ms - last_frame_ms;
        last_frame_ms = current_ms;
        animation_0.Play(delta_ms);
        fw_manager->Update(static_cast<uint64_t>(delta_ms));
        emitter_render->Update_and_Collect(static_cast<uint64_t>(delta_ms));
#endif
        /***************************************************
         *                    渲染                         *
        ***************************************************/
        bloom_worker.draw_world();//画世界------------------------------
        sky.draw();
        background.draw();
        emitter_render->Render();

        bloom_worker.draw_firework();//画烟花-------------------------------
        emitter_render->Render();

        bloom_worker.draw_gauss(); //gauss 模糊--------------------------------------

        bloom_worker.draw_screen();//画屏幕-------------------------------

        /***************************************************
         *                    帧率控制                     *
        ***************************************************/
#ifdef SDL2_LIB
        // 控制帧率
        frame_rate = 1000.0f / static_cast<float>(delta_frame_time);
        if (frame_rate > FPS) {
            SDL_Delay(static_cast<uint32_t>(1000.0 / FPS - static_cast<float>(delta_frame_time)));
        }
        // 标题栏显示帧率
        if (last_flush_time + 1000 < now_frame_time) {
            win_title = "video_demo FPS:" + std::to_string(static_cast<int>(frame_rate));
            SDL_SetWindowTitle(win, win_title.data());
            last_flush_time = now_frame_time;
        }
        // 交换缓冲
        SDL_GL_SwapWindow(win);
        camera.FlushFrameTime();

        // 更新帧时间
        last_frame_time = now_frame_time;
#else
        // 控制帧率
        frame_rate = 1000.0 / delta_ms;
        if (frame_rate > FPS) {
            std::this_thread::sleep_for(std::chrono::seconds(static_cast<int64_t>(1.0 / FPS - 1000.0 * delta_ms)));
        }
        // 标题栏显示帧率
        if (last_flush_time + 1000.0 < current_ms) {
            win_title = "video_demo FPS:" + std::to_string(static_cast<int>(frame_rate));
            glfwSetWindowTitle(window, win_title.data());
            last_flush_time = current_ms;
        }
        // 交换缓冲
        glfwSwapBuffers(window);
#endif

    }

    /***************************************************
     *              窗口-程序退出                           *
    ***************************************************/
#ifdef SDL2_LIB
    SDL_DestroyWindow(win);
    // 关闭音频相关库
    Mix_CloseAudio();
    Mix_Quit();
    //退出SDL 
    SDL_Quit();
#else
    glfwTerminate();
#endif
    return 0;
    }