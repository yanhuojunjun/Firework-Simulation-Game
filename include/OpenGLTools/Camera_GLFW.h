#ifndef CAMERA_H
#define CAMERA_H

#include "glad.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "ICamera.h"

#include <vector>
#include <iostream>

//摄像机移动方式
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

/*
    一个抽象的摄像机类
    处理鼠标,键盘的输入
    计算相关的欧拉角, 向量, 观察矩阵
*/
class Camera_GLFW : public ICamera {
public:

    /*
        摄像机位置 世界上坐标 偏航角 俯仰角(不能超过90度)
        默认初始: 摄像机朝向(0, 0, -1)点,
    */
    Camera_GLFW(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    /*
        摄像机位置值 世界上坐标值 偏航角 俯仰角(不能超过90度)
    */
    Camera_GLFW(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);


    /*
        处理来自键盘的输入消息
        输入 摄像机移动的方向 经过的时间(使用这个时间乘以速度得到移动的距离)
    */
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    /*
        处理来自鼠标的消息
        输入 鼠标相对于上一次的偏移量 是否将俯仰角限制在[-90, 90]度范围内
    */
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    /*
        处理鼠标滚轮消息
        只输入垂直滚动的距离 (保证视角限制在[1, 45]度)
    */
    void ProcessMouseScroll(float yoffset);

};

#endif