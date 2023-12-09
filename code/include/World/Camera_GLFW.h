#ifndef CAMERA_H
#define CAMERA_H

#include "glad.h"
#include "glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "ICamera.h"

#include <vector>
#include <iostream>


class Camera_GLFW : public ICamera {
public:

    /*
        窗口指针 摄像机位置 世界上坐标 偏航角 俯仰角(不能超过90度)
        默认初始: 摄像机朝向(0, 0, -1)点,
    */
    Camera_GLFW(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    /*
        窗口指针 摄像机位置值 世界上坐标值 偏航角 俯仰角(不能超过90度)
    */
    Camera_GLFW(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    void SetWindow(GLFWwindow* _window);
    void HandleEvent();
    
    void FlushFrameTime();

    /*
        处理来自键盘的输入消息
        输入 摄像机移动的方向 经过的时间(使用这个时间乘以速度得到移动的距离)
    */
    void ProcessKeyboard();

    /*
        处理来自鼠标的消息
        输入 鼠标相对于上一次的偏移量 是否将俯仰角限制在[-90, 90]度范围内
    */
    void ProcessMouseMovement(double _xpos, double _ypos);

    /*
        处理鼠标滚轮消息
        只输入垂直滚动的距离 (保证视角限制在[1, 45]度)
    */
    void ProcessMouseScroll(float yoffset);
protected:
    GLFWwindow* window;
    float delta_second;
    float last_frame_second;
    float current_second;

    bool firstMouse;
    float lastX;
    float lastY;

    float jump_init_velocity; // 跳跃初速度
    
    bool is_view_mode; // 走路浏览模式 否则飞行模式
    
    bool jumping; // 跳跃
    
    float velocity; // 帧位移

    double last_handle_second, current_handle_second;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif