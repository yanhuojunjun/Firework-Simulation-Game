#include "glad.h"
#include "SDL.h"
#include "stb_image.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Shader.h"
#include "Camera_SDL.h"

#include "Cube.h"

#include <iostream>
#include <cmath>
#include <string>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

Camera_SDL camera;

unsigned int texture;
unsigned int texture2;

void CreatTexture() {
    // 载入图像
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("img/container2.png", &width, &height, &nrChannels, 0);
    if (data == NULL) {
        std::cout << "fail to load image" << std::endl;
    }
    // 创建纹理
    //unsigned int texture;
    glGenTextures(1, &texture);
    // 激活纹理单元
    glActiveTexture(GL_TEXTURE0);
    // 绑定纹理
    glBindTexture(GL_TEXTURE_2D, texture);
    // 根据图像数据生成纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    // 生成多级渐远纹理
    glGenerateMipmap(GL_TEXTURE_2D);
    // 生成纹理后释放图片数据
    stbi_image_free(data);

    data = stbi_load("img/container2_specular.png", &width, &height, &nrChannels, 0);
    if (data == NULL) {
        std::cout << "fail to load image" << std::endl;
    }
    // 创建纹理
    //unsigned int texture2;
    glGenTextures(1, &texture2);
    // 激活纹理单元
    glActiveTexture(GL_TEXTURE1);
    // 绑定纹理
    glBindTexture(GL_TEXTURE_2D, texture2);
    // 根据图像数据生成纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    // 生成多级渐远纹理
    glGenerateMipmap(GL_TEXTURE_2D);
    // 生成纹理后释放图片数据
    stbi_image_free(data);
}

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


    Cube cube(36, 8, "Object/material_cube.v");
    unsigned int temp[] = { 3,3,2 };

    // 物体
    cube.CreateCube(3, temp, false);
    CreatTexture();

    // 光源
    cube.CreateCube(1, temp, false);


    /*
        自定义着色器
        判断是否成功创建 编译
    */
    Shader object_shader("Shaders/material_texture.vs", "Shaders/mult_light.fs");
    Shader light_shader("Shaders/light_shader.vs", "Shaders/light_shader.fs");

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
        rotate_mat = glm::rotate(model, (float)(SDL_GetTicks()), glm::vec3(1.0f, 0.3f, 0.5f));

        // 绘制箱子
        object_shader.use();
        // 变换矩阵
        object_shader.setMat4("view", view);
        object_shader.setMat4("projection", projection);
        // 摄像机位置
        object_shader.setVec3("viewPos", camera.Position);
        // 箱子的材质
        object_shader.setInt("material.diffuse", 0); // 纹理0
        object_shader.setInt("material.specular", 1); // 纹理1
        object_shader.setFloat("material.shininess", 32.0f); // 反光度->高光大小
        // 点光源
        for (int i = 0;i < 4;i++) {
            std::string base_var_name = "pointLights[" + std::to_string(i) + "].";
            std::string var_name = base_var_name + "position";
            object_shader.setVec3(var_name.data(), pointLightPositions[i]);
            var_name = base_var_name + "constant";
            object_shader.setFloat(var_name.data(), 1.0f);
            var_name = base_var_name + "linear";
            object_shader.setFloat(var_name.data(), 0.09f);
            var_name = base_var_name + "quadratic";
            object_shader.setFloat(var_name.data(), 0.032f);
            var_name = base_var_name + "ambient";
            object_shader.setVec3(var_name.data(), glm::vec3(0.05f, 0.05f, 0.05f));
            var_name = base_var_name + "diffuse";
            object_shader.setVec3(var_name.data(), glm::vec3(0.8f, 0.8f, 0.8f)); // 将光照调暗了一些以搭配场景
            var_name = base_var_name + "specular";
            object_shader.setVec3(var_name.data(), glm::vec3(1.0f, 1.0f, 1.0f));

        }
        // 平行光
        object_shader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        object_shader.setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        object_shader.setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
        object_shader.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
        // 聚光灯
        object_shader.setVec3("spotLight.position", camera.Position);
        object_shader.setVec3("spotLight.direction", camera.Front);
        object_shader.setVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
        object_shader.setVec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        object_shader.setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        object_shader.setFloat("spotLight.constant", 1.0f);
        object_shader.setFloat("spotLight.linear", 0.09f);
        object_shader.setFloat("spotLight.quadratic", 0.032f);
        object_shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        object_shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
        // 绘制
        for (int i = 0;i < 10;i++) {
            model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            object_shader.setMat4("model", model);
            cube.DrawCube(0);
        }
        // 绘制光源
        light_shader.use();

        light_shader.setMat4("view", view);
        light_shader.setMat4("projection", projection);
        
        for (int i = 0;i < 4;i++) {
            glm::mat4 light(1.0f);
            light = glm::translate(light, pointLightPositions[i]);
            light = glm::scale(light, glm::vec3(0.2f));
            light_shader.setMat4("model", light);
            cube.DrawCube(1);
        }
        

        SDL_GL_SwapWindow(win);
        camera.FlushFrameTime();
    }

    object_shader.deleteShader();
    light_shader.deleteShader();

    SDL_DestroyWindow(win);
    //退出SDL 
    SDL_Quit();

    return 0;
}