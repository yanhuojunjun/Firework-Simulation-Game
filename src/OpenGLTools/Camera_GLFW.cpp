#include "Camera_GLFW.h"

extern unsigned int WIN_WIDTH;
extern unsigned int WIN_HEIGHT;

Camera_GLFW::Camera_GLFW(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    delta_second = 0.0f;
    last_frame_second = 0.0f;
    current_second = 0.0f;
    firstMouse = true;
    lastX = WIN_WIDTH / 2.0f;
    lastY = WIN_HEIGHT / 2.0f;
    ICamera(position, up, yaw, pitch);
    ICamera::updateCameraVectors();
}

Camera_GLFW::Camera_GLFW(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) {
    delta_second = 0.0f;
    last_frame_second = 0.0f;
    current_second = 0.0f;
    firstMouse = true;
    lastX = WIN_WIDTH / 2.0f;
    lastY = WIN_HEIGHT / 2.0f;
    ICamera(posX, posY, posZ, upX, upY, upZ, yaw, pitch);
    updateCameraVectors();
}

void Camera_GLFW::SetWindow(GLFWwindow* _window) {
    window = _window;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏鼠标
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

void Camera_GLFW::HandleEvent() {
    glfwPollEvents();
    FlushFrameTime();
    ProcessKeyboard();
}

void Camera_GLFW::FlushFrameTime() {
    current_second = static_cast<float>(glfwGetTime());
    delta_second = current_second - last_frame_second;
    last_frame_second = current_second;
}

void Camera_GLFW::ProcessKeyboard() {
    float velocity = MovementSpeed * delta_second;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) Position += Front * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) Position -= Front * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) Position -= Right * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) Position += Right * velocity;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) Position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) Position += glm::vec3(0.0f, -1.0f, 0.0f) * velocity;
}

void Camera_GLFW::ProcessMouseMovement(double _xpos, double _ypos) {
    if (firstMouse) {
        lastX = _xpos;
        lastY = _ypos;
        firstMouse = false;
    }

    float xoffset = (_xpos - lastX) * MouseSensitivity;
    float yoffset = (lastY - _ypos) * MouseSensitivity; // reversed since y-coordinates go from bottom to top

    lastX = _xpos;
    lastY = _ypos;

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

extern Camera_GLFW camera;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    camera.ProcessMouseMovement(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}


