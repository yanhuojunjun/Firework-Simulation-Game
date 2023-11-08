#include "Camera_GLFW.h"


Camera_GLFW::Camera_GLFW(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    ICamera(position, up, yaw, pitch);
    ICamera::updateCameraVectors();
}

Camera_GLFW::Camera_GLFW(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) {
    ICamera(posX, posY, posZ, upX, upY, upZ, yaw, pitch);
    updateCameraVectors();
}

void Camera_GLFW::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    // 使用 switch 比 if 稍微快一些
    switch (direction) {
    case Camera_Movement::FORWARD:
        Position += Front * velocity;
        break;
    case Camera_Movement::BACKWARD:
        Position -= Front * velocity;
        break;
    case Camera_Movement::LEFT:
        Position -= Right * velocity;
        break;
    case Camera_Movement::RIGHT:
        Position += Right * velocity;
        break;
    default:
        break;
    }
}

void Camera_GLFW::ProcessMouseMovement(float xoffset, float yoffset, GLboolean consPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // 确保当俯仰角超过90度时 屏幕不会翻转
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // 根据欧拉角更新 front up right 向量
    updateCameraVectors();
}


void Camera_GLFW::ProcessMouseScroll(float yoffset) {
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}




