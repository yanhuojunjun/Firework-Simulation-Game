/*
    显示一个光照箱子

*/

#include "glad/glad.h"
#include "glfw3.h"

#include "stb_image.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <iostream>
#include <cmath>


#include "Shader.h"
#include "Camera_GLFW.h"

#include "Cube.h"

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

Camera_GLFW camera;
float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;
bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void CreatTexture() {
    // 载入图像
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("img/container.jpg", &width, &height, &nrChannels, 0);
    // 创建纹理
    unsigned int texture;
    glGenTextures(1, &texture);
    // 激活纹理单元
    glActiveTexture(GL_TEXTURE0);
    // 绑定纹理
    glBindTexture(GL_TEXTURE_2D, texture);
    // 根据图像数据生成纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    // 生成多级渐远纹理
    glGenerateMipmap(GL_TEXTURE_2D);
    // 生成纹理后释放图片数据
    stbi_image_free(data);

    data = stbi_load("img/awesomeface.png", &width, &height, &nrChannels, 0);
    // 创建纹理
    unsigned int texture2;
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

int main() {
    // 初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // 定义一个窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "21307124", NULL, NULL);
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

    glViewport(0, 0, 800, 600);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏鼠标
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    /*
        创建一个立方体
    */
    Cube cube(36, 6, "Object/light_cube.v");
    unsigned int temp[2] = { 3,3 };
    // 物体
    cube.CreateCube(2, temp, false);
    // 光源
    cube.CreateCube(1, temp, false);

    /*
        自定义着色器
        判断是否成功创建 编译
    */
    Shader object_shader("Shaders/object_shader.vs", "Shaders/object_shader.fs");
    Shader light_shader("Shaders/light_shader.vs", "Shaders/light_shader.fs");

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

    model = glm::translate(model, glm::vec3(0.0f, -0.7f, -1.0f));

    glm::vec3 lightpos = glm::vec3(1.0f, 1.5f, -1.5f);
    glm::mat4 light(1.0f);
    light = glm::translate(light, lightpos);
    light = glm::scale(light, glm::vec3(0.2f));

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // 输入 处理函数
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置屏幕颜色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕 Z缓冲

        // 设置物体变换
        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
        rotate_mat = glm::rotate(model, (float)(glfwGetTime()), glm::vec3(1.0f, 0.3f, 0.5f));

        // 绘制物体
        object_shader.use();
        // 设置采样器 为其赋值着色器位置
        // object_shader.setInt("Texture0", 0);
        // object_shader.setInt("Texture1", 1);
        object_shader.setMat4("view", view);
        object_shader.setMat4("projection", projection);
        object_shader.setMat4("model", model);
        object_shader.setVec3("lightPos", lightpos);
        object_shader.setVec3("viewPos", camera.Position);
        object_shader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        object_shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        cube.DrawCube(0);

        // 绘制光源
        light_shader.use();

        light_shader.setMat4("view", view);
        light_shader.setMat4("projection", projection);
        light_shader.setMat4("model", light);

        cube.DrawCube(1);

        // 检查并调用事件 交换缓冲
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    object_shader.deleteShader();
    light_shader.deleteShader();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;
    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}