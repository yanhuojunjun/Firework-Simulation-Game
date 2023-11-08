#ifndef ICAMERA_H
#define ICAMERA_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

// 默认的一些取值
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class ICamera
{
public:
    // camera Attributes
    // 摄像机位置
    glm::vec3 Position;
    // 相对于摄像机位置而言, 物体的位置
    // 或者说是一个原点在摄像机处, 指向物体的向量
    glm::vec3 Front;
    // 摄像机的上轴
    glm::vec3 Up;
    // 摄像机的右轴
    glm::vec3 Right;
    // 世界坐标系的上方向(一般就是(0, 1, 0))
    glm::vec3 WorldUp;
    // 欧拉角
    float Yaw;
    float Pitch;
    // 摄像机选项
    // 摄像机移动速度
    float MovementSpeed;
    // 鼠标灵敏度(转角速度)
    float MouseSensitivity;
    // 视角大小(放大缩小物体的效果)
    float Zoom;
    // 摄像机限制在俯仰90度
    bool constrainPitch;
public:
    /*
        摄像机位置 世界上坐标 偏航角 俯仰角(不能超过90度)
        默认初始: 摄像机朝向(0, 0, -1)点,
    */
    ICamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    /*
            摄像机位置值 世界上坐标值 偏航角 俯仰角(不能超过90度)
        */
    ICamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    /*
        获得观察矩阵
    */
    glm::mat4 GetViewMatrix();

    virtual ~ICamera();

    /*
        根据欧拉角计算 front up right 向量
    */
    void updateCameraVectors();
};

#endif