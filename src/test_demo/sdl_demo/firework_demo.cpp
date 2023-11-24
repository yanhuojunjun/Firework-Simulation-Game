#include "glad.h"
#include "SDL.h"
#include "stb_image.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Shader.h"
#include "Firework_Viewer.h"
#include "World.h"
// 烟花
#include "Firework_Manager.h"

#include <iostream>
#include <cmath>
#include <string>

#define WIN_WIDTH 1200
#define WIN_HEIGHT 750
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
    
    // 创建渲染器
    //Emitter_Render emitter_render(&camera);
    std::shared_ptr<Emitter_Render> emitter_render = std::make_shared<Emitter_Render>(&camera);
    //emitter_render.AddEmitter(&emitter);
    // 创建烟花
    Firework_Manager fw_manager(emitter_render);
 
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
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_4:
                    fw_manager.Register_Firework(
                        0,
                        8,
                        camera.Position + 15.0f * glm::vec3(camera.Front.x, 0, camera.Front.z),
                        glm::vec3(0, 1, 0),
                        glm::vec4(glm::linearRand(0.001f, 1.0f), glm::linearRand(0.001f, 1.0f), glm::linearRand(0.001f, 1.0f), 1.0f),
                        3000 + glm::linearRand(0, 1) * 500
                    );
                    break;
                case SDLK_1:
                    fw_manager.Register_Firework(
                        1,
                        8,
                        camera.Position + 15.0f * glm::vec3(camera.Front.x, 0, camera.Front.z),
                        glm::vec3(0, 1, 0),
                        glm::vec4(glm::linearRand(0.001f, 1.0f), glm::linearRand(0.001f, 1.0f), glm::linearRand(0.001f, 1.0f), 1.0f),
                        3000 + glm::linearRand(0, 1) * 500
                    );
                    break;
                case SDLK_2:
                    fw_manager.Register_Firework(
                        2,
                        8,
                        camera.Position + 15.0f * glm::vec3(camera.Front.x, 0, camera.Front.z),
                        glm::vec3(1, 2, 0),
                        glm::vec4(glm::linearRand(0.001f, 1.0f), glm::linearRand(0.001f, 1.0f), glm::linearRand(0.001f, 1.0f), 1.0f),
                        3000 + glm::linearRand(0, 1) * 500
                    );
                    break;
                case SDLK_3:
                    fw_manager.Register_Firework(
                        3,
                        8,
                        camera.Position + 15.0f * glm::vec3(camera.Front.x, 0, camera.Front.z),
                        glm::vec3(0, 1, 0),
                        glm::vec4(glm::linearRand(0.001f, 1.0f), glm::linearRand(0.001f, 1.0f), glm::linearRand(0.001f, 1.0f), 1.0f),
                        3000 + glm::linearRand(0, 1) * 500
                    );
                    break;
                }
            }
        }
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // 设置屏幕颜色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除屏幕
        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(WIN_WIDTH) / static_cast<float>(WIN_HEIGHT), 0.1f, 100.0f);

        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setMat4("model", model);

        world.Display();

        // 更新帧时间
        now_frame_time = SDL_GetTicks64();
        delta_frame_time = now_frame_time - last_frame_time;

        // 更新烟花
        fw_manager.Update(delta_frame_time);

        // 更新粒子发射器并渲染
        emitter_render->Update_and_Collect(delta_frame_time);
        emitter_render->Render();

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