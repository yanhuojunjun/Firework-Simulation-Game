#include "glad.h"
#include "SDL.h"
#include "stb_image.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Shader.h"
#include "Character.h"
#include "World.h"
// 粒子
#include "circle_firework.h"

#include <iostream>
#include <cmath>
#include <string>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

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
    SDL_Window* win = SDL_CreateWindow("hello",
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

    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

    World world;
    Character camera(&world);
    world.Create();
    //ball_firework firework_0(&camera, glm::vec3(0.0f, 1.0f, -1.0f), glm::vec4(0.5f, 1.0f, 0.5f, 1.0f));
    
    /*
        自定义着色器
        判断是否成功创建 编译
    */
    Shader shader("Shaders/base_world.vs", "Shaders/base_world.fs");
    Shader firework_shader("Shaders/particle.vs", "Shaders/particle.fs");
    // 创建烟花
    circle_firework firework1(&firework_shader, &camera, glm::vec3(0.0f, 0.0f, -15.0f), glm::vec4(0.5f, 1.0f, 0.5f, 1.0f), 50);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //图元绘制设置为线框模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //图元绘制设置为默认(填充)模式

    // 开启Z缓冲
    glEnable(GL_DEPTH_TEST);

    // 变换矩阵
    glm::mat4 projection(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 model(1.0f);
    // 旋转矩阵
    glm::mat4 rotate_mat(1.0f);

    SDL_Event event;
    bool quit_flag = false;
    Uint64 last_frame_time = SDL_GetTicks64();
    Uint64 now_frame_time = last_frame_time;
    while (!quit_flag) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit_flag = true;
            camera.ProcessEvent(event);
        }
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置屏幕颜色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除屏幕
        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
        //rotate_mat = glm::rotate(model, (float)(SDL_GetTicks()), glm::vec3(1.0f, 0.3f, 0.5f));

        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setMat4("model", model);
        world.Display();
        // 更新帧时间
        now_frame_time = SDL_GetTicks64();

        firework1.update(now_frame_time-last_frame_time);

        SDL_GL_SwapWindow(win);
        camera.Update();
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