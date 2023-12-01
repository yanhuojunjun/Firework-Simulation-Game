#include "Firework_Viewer.h"

Firework_Viewer::Firework_Viewer(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :ICamera(position, up, yaw, pitch) {
    ICamera::updateCameraVectors();
    Last_Frame_time = SDL_GetTicks64();
    Time_Pass_By = 0;
    is_view_mode = true;
    jumping = false;
    for (int i = 0;i < 6;i++) direct[i] = glm::vec3(0.0f);
}

Firework_Viewer::Firework_Viewer(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :ICamera(posX, posY, posZ, upX, upY, upZ, yaw, pitch) {
    updateCameraVectors();
    Last_Frame_time = SDL_GetTicks64();
    Time_Pass_By = 0;
    is_view_mode = true;
    jumping = false;
    for (int i = 0;i < 6;i++) direct[i] = glm::vec3(0.0f);
}

Firework_Viewer::~Firework_Viewer() {}

void Firework_Viewer::FlushFrameTime() {
    Time_Pass_By = SDL_GetTicks64() - Last_Frame_time;
    Last_Frame_time += Time_Pass_By;

    // 计算这一帧的位移
    float velocity(MovementSpeed * Time_Pass_By / 1000);

    for (int i = 0;i < 4;i++) {
        Position += velocity * direct[i];
    }
    // 跳跃 下落
    if (is_view_mode) {
        if (jumping) {
            direct[4].y -= velocity * 2.0; // 重力加速度为0.01
            Position.y += velocity * direct[4].y;
        }
    }
    else {  // 飞行
        Position += velocity * direct[4];
        Position += velocity * direct[5];
    }
    // 地面检测
    if (Position.y < 0.0f) {
        Position.y = 0.0f;
        jumping = false;
    }

}

void Firework_Viewer::ProcessKeyboardDown(SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_w: {
        direct[0] = glm::normalize(glm::vec3(Front.x, 0, Front.z));
        break;
    }
    case SDLK_s: {
        direct[1] = -glm::normalize(glm::vec3(Front.x, 0, Front.z));
        break;
    }
    case SDLK_d: {
        direct[2] = glm::normalize(glm::vec3(Right.x, 0, Right.z));
        break;
    }
    case SDLK_a: {
        direct[3] = -glm::normalize(glm::vec3(Right.x, 0, Right.z));
        break;
    }
    case SDLK_SPACE: {
        if (is_view_mode) {
            if (!jumping) {
                direct[4] = glm::vec3(0, 2.0, 0); // 跳跃初速度
                jumping = true;
            }
        }
        else {
            direct[4] = glm::vec3(0, 1, 0);
        }
        break;
    }
    case SDLK_LSHIFT: {
        direct[5] = glm::vec3(0, -1, 0);
        break;
    }
    case SDLK_ESCAPE: {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
        break;
    }
    case SDLK_f: {
        is_view_mode = false;
        break;
    }
    default: {
        break;
    }
    }
}

void Firework_Viewer::ProcessKeyboardUp(SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_w: {
        direct[0] = glm::vec3(0.0f);
        //std::cout << "go left" << std::endl;
        break;
    }
    case SDLK_s: {
        direct[1] = glm::vec3(0.0f);
        //std::cout << "go back" << std::endl;
        break;
    }
    case SDLK_d: {
        direct[2] = glm::vec3(0.0f);
        //std::cout << "go right" << std::endl;
        break;
    }
    case SDLK_a: {
        direct[3] = glm::vec3(0.0f);
        //std::cout << "go ahead" << std::endl;
        break;
    }
    case SDLK_SPACE: {
        if (!jumping || !is_view_mode) direct[4] = glm::vec3(0.0f);
        break;
    }
    case SDLK_LSHIFT: {
        direct[5] = glm::vec3(0.0f);
        break;
    }
    default: {
        break;
    }
    }
}

void Firework_Viewer::ProcessMouseMovement(SDL_Event& event) {
    Yaw += event.motion.xrel * MouseSensitivity;
    Pitch -= event.motion.yrel * MouseSensitivity;
    //std::cout << "move " << Yaw << ", " << Pitch << std::endl;
    if (constrainPitch) {
        if (Pitch > 89.0f) Pitch = 89.0f;
        else if (Pitch < -89.0f) Pitch = -89.0f;
    }
    updateCameraVectors();
}

void Firework_Viewer::ProcessMouseScroll(SDL_Event& event) {
    Zoom -= event.wheel.preciseY;
    //std::cout << "wheel " << Zoom << std::endl;
    if (Zoom < 1.0f) Zoom = 1.0f;
    if (Zoom > 45.0f) Zoom = 45.0f;
}

void Firework_Viewer::ProcessEvent(SDL_Event& event) {
    switch (event.type) {
    case SDL_MOUSEMOTION: {
        ProcessMouseMovement(event);
        //std::cout << "mouse move" << std::endl;
        break;
    }
    case SDL_KEYDOWN: {
        if (is_view_mode) ProcessKeyboardDown(event);
        else ProcessCommand(event);
        break;
    }
    case SDL_KEYUP: {
        ProcessKeyboardUp(event);
        break;
    }
    case SDL_MOUSEWHEEL: {
        if (is_view_mode) ProcessMouseScroll(event);
        //std::cout << "mouse wheel" << std::endl;
        break;
    }
    default: {
        break;
    }
    }
}

void Firework_Viewer::ProcessCommand(SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_w: {
        direct[0] = glm::normalize(glm::vec3(Front.x, 0, Front.z));
        break;
    }
    case SDLK_s: {
        direct[1] = -glm::normalize(glm::vec3(Front.x, 0, Front.z));
        break;
    }
    case SDLK_d: {
        direct[2] = glm::normalize(glm::vec3(Right.x, 0, Right.z));
        break;
    }
    case SDLK_a: {
        direct[3] = -glm::normalize(glm::vec3(Right.x, 0, Right.z));
        break;
    }
    case SDLK_SPACE: {
        direct[4] = glm::vec3(0, 1, 0);
        break;
    }
    case SDLK_LSHIFT: {
        direct[5] = glm::vec3(0, -1, 0);
        break;
    }
    case SDLK_ESCAPE: {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
        break;
    }
    case SDLK_f: {
        is_view_mode = true;
        if (Position.y > 0.0f) {
            direct[4].y = 0.0f;
            jumping = true;
        }
        break;
    }
    default: {
        break;
    }
    }
}