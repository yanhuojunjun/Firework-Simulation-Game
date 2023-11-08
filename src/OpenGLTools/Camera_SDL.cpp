#include "Camera_SDL.h"

Camera_SDL::Camera_SDL(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    ICamera(position, up, yaw, pitch);
    ICamera::updateCameraVectors();
    Last_Frame_time = SDL_GetTicks64();
    Time_Pass_By = 0;
    
}

Camera_SDL::Camera_SDL(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) {
    ICamera(posX, posY, posZ, upX, upY, upZ, yaw, pitch);
    updateCameraVectors();
    Last_Frame_time = SDL_GetTicks64();
    Time_Pass_By = 0;
}

Camera_SDL::~Camera_SDL() {}

void Camera_SDL::FlushFrameTime() {
    Time_Pass_By = SDL_GetTicks64() - Last_Frame_time;
    Last_Frame_time += Time_Pass_By;
    
    // 计算这一帧的位移
    glm::vec3 velocity(MovementSpeed * Time_Pass_By / 1000);

    for (int i = 0;i < 6;i++) {
        Position += velocity * direct[i];
    }
}

void Camera_SDL::ProcessKeyboardDown(SDL_Event& event) {
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_W: {
        direct[0] = Front;
        break;
    }
    case SDL_SCANCODE_S: {
        direct[1] = -Front;
        break;
    }
    case SDL_SCANCODE_D: {
        direct[2] = Right;
        break;
    }
    case SDL_SCANCODE_A: {
        direct[3] = -Right;
        break;
    }
    case SDL_SCANCODE_SPACE: {
        direct[4] = Up;
        break;
    }
    case SDL_SCANCODE_LSHIFT: {
        direct[5] = -Up;
        break;
    }
    case SDL_SCANCODE_ESCAPE: {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
        break;
    }
    default: {
        break;
    }
    }
}

void Camera_SDL::ProcessKeyboardUp(SDL_Event& event) {
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_W: {
        direct[0] = glm::vec3(0.0f);
        //std::cout << "go left" << std::endl;
        break;
    }
    case SDL_SCANCODE_S: {
        direct[1] = glm::vec3(0.0f);
        //std::cout << "go back" << std::endl;
        break;
    }
    case SDL_SCANCODE_D: {
        direct[2] = glm::vec3(0.0f);
        //std::cout << "go right" << std::endl;
        break;
    }
    case SDL_SCANCODE_A: {
        direct[3] = glm::vec3(0.0f);
        //std::cout << "go ahead" << std::endl;
        break;
    }
    case SDL_SCANCODE_SPACE: {
        direct[4] = glm::vec3(0.0f);
        break;
    }
    case SDL_SCANCODE_LSHIFT: {
        direct[5] = glm::vec3(0.0f);
        break;
    }
    default: {
        break;
    }
    }
}

void Camera_SDL::ProcessMouseMovement(SDL_Event& event) {
    Yaw += event.motion.xrel * MouseSensitivity;
    Pitch -= event.motion.yrel * MouseSensitivity;
    //std::cout << "move " << Yaw << ", " << Pitch << std::endl;
    if (constrainPitch) {
        if (Pitch > 89.0f) Pitch = 89.0f;
        else if (Pitch < -89.0f) Pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera_SDL::ProcessMouseScroll(SDL_Event& event) {
    Zoom -= event.wheel.preciseY;
    //std::cout << "wheel " << Zoom << std::endl;
    if (Zoom < 1.0f) Zoom = 1.0f;
    if (Zoom > 45.0f) Zoom = 45.0f;
}

void Camera_SDL::ProcessEvent(SDL_Event& event) {
    switch (event.type) {
    case SDL_MOUSEMOTION: {
        ProcessMouseMovement(event);
        //std::cout << "mouse move" << std::endl;
        break;
    }
    case SDL_KEYDOWN: {
        ProcessKeyboardDown(event);
        break;
    }
    case SDL_KEYUP: {
        ProcessKeyboardUp(event);
        break;
    }
    case SDL_MOUSEWHEEL: {
        ProcessMouseScroll(event);
        //std::cout << "mouse wheel" << std::endl;
        break;
    }
    default: {
        break;
    }
    }
}