#include "glad.h"
#include "SDL.h"
#include "stb_image.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Shader.h"
#include "Character.h"
#include "World.h"

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

    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    
    World world;
    Character camera(&world);
    world.Create();
    
    /*
        自定义着色器
        判断是否成功创建 编译
    */
    // Shader object_shader("Shaders/material_texture.vs", "Shaders/mult_light.fs");
    // Shader light_shader("Shaders/light_shader.vs", "Shaders/light_shader.fs");
    Shader shader("Shaders/base_world.vs", "Shaders/base_world.fs");
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //图元绘制设置为线框模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //图元绘制设置为默认(填充)模式

    // 开启Z缓冲
    glEnable(GL_DEPTH_TEST);

    // 立方体的位置
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // 光源位置
    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };

    // 变换矩阵
    glm::mat4 projection(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 model(1.0f);
    // 旋转矩阵
    glm::mat4 rotate_mat(1.0f);

    SDL_Event event;
    bool quit_flag = false;
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
        
        SDL_GL_SwapWindow(win);
        camera.Update();
    }

    // object_shader.deleteShader();
    // light_shader.deleteShader();

    SDL_DestroyWindow(win);
    //退出SDL 
    SDL_Quit();

    return 0;
}