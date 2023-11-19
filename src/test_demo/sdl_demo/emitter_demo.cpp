#include "glad.h"
#include "SDL.h"
#include "stb_image.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Shader.h"
#include "Firework_Viewer.h"
#include "World.h"
// 粒子
#include "Emitter.h"
#include "Particle_Emitter.h"
#include "Emitter_Render.h"
#include <iostream>
#include <cmath>
#include <string>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define FPS 62

int main(int argc, char* args[]) {
    //启动SDL
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        return 1;
    }
    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    // SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //设置窗口
    std::string win_title = "emitter_demo FPS:" + std::to_string(0);
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
    // SDL_GL_MakeCurrent(win, gl_context);
    // SDL_GL_SetSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_BLEND); // 启用混合 可显示透明背景纹理
    glEnable(GL_PROGRAM_POINT_SIZE);
    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

    World world;
    Firework_Viewer camera;
    world.Create();
    /*
        自定义着色器
        判断是否成功创建 编译
    */
    Shader shader("Shaders/base_world.vs", "Shaders/base_world.fs");
    // 创建烟花
    ParticleEmitter emitter;
    emitter.SetParticleEmitter(
        30,                                   // 最大粒子数
        glm::vec3(0, 0, -1),                     // 粒子发射器中心
        glm::vec4(0.5f, 1.0f, 0.5f, 1.0f),      // 粒子颜色
        100,                                     // 粒子大小
        2000,                                    // 粒子生命周期
        0.5f,                                      // 粒子初速度
        glm::normalize(glm::vec3(0, 1, 0)),        // 粒子初始方向
        glm::vec3(0, 0.005, 0),                     // 粒子加速度
        50,                                     // 粒子发射间隔
        0,                                      // 纹理
        EmitterType::Sphere,                    // 粒子发射器类型
        0.0f,                                       // 圆形粒子发射器-半径
        DirectionType::Outer                  // 圆形粒子发射器-朝向类型
    );
    emitter.EnableColorUpdater(glm::vec4(0.5f, 0.0f, 0.5f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
    emitter.AddMidColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.7f), 0.7);
    emitter.EnableRandom(0.2);
    emitter.EnableOneShoot();
    // 创建渲染器
    Emitter_Render emitter_render(&camera);
    emitter_render.AddEmitter(&emitter);

    // 开启Z缓冲
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //图元绘制设置为默认(填充)模式
    // 变换矩阵
    glm::mat4 projection(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 model(1.0f);

    SDL_Event event;
    bool quit_flag = false;
    Uint64 last_frame_time = SDL_GetTicks64();
    Uint64 now_frame_time = last_frame_time;
    Uint64 delta_frame_time = now_frame_time - last_frame_time;
    float frame_rate = 0.0f;
    Uint64 last_flush_time = 0;
    while (!quit_flag) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit_flag = true;
            camera.ProcessEvent(event);
        }
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置屏幕颜色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除屏幕
        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);

        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setMat4("model", model);

        world.Display();

        // 更新帧时间
        now_frame_time = SDL_GetTicks64();
        delta_frame_time = now_frame_time - last_frame_time;
        // 更新粒子发射器并渲染
        emitter_render.Update_and_Collect(delta_frame_time);
        emitter_render.Render();

        // 控制帧率
        frame_rate = 1000.0f / static_cast<float>(delta_frame_time);
        if (frame_rate > FPS) {
            SDL_Delay(1000.0 / FPS - delta_frame_time);
        }
        // 标题栏显示帧率
        if (last_flush_time + 1000 < now_frame_time) {
            win_title = "emitter_demo FPS:" + std::to_string(static_cast<int>(frame_rate));
            SDL_SetWindowTitle(win, win_title.data());
            last_flush_time = now_frame_time;
        }

        // 交换缓冲
        SDL_GL_SwapWindow(win);
        camera.FlushFrameTime();

        // 更新帧时间
        last_frame_time = now_frame_time;
    }

    // object_shader.deleteShader();
    // light_shader.deleteShader();
    shader.deleteShader();
    SDL_DestroyWindow(win);
    //退出SDL 
    SDL_Quit();

    return 0;
}