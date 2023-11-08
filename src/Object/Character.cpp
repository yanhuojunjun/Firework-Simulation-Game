#include "Character.h"
Character::Character(World* w) {
    Last_Frame_time = SDL_GetTicks64();
    world = w;
    height = 0.1;
    tofeet = glm::vec3(0, height, 0);
    MovementSpeed = 1;
    state = Character_State::Jumping;
    v0 = 0.1;
}

void Character::Update() {
    Time_Pass_By = SDL_GetTicks64() - Last_Frame_time;
    Last_Frame_time += Time_Pass_By;
    //std::cout << 1000 / Time_Pass_By << std::endl;
    // 计算这一帧的水平位移
    glm::vec3 velocity(MovementSpeed * Time_Pass_By / 1000);
    // 掉落/上升距离
    float y = 0;

    // 计算移动的方向 前后左右
    glm::vec3 direction(0);
    if (Have(Character_State::Forward)) direction += glm::normalize(glm::vec3(Front.x, 0, Front.z));
    if (Have(Character_State::Backword)) direction += glm::normalize(glm::vec3(-Front.x, 0, -Front.z));
    if (Have(Character_State::Leftword)) direction += glm::normalize(glm::vec3(Right.x, 0, Right.z));
    if (Have(Character_State::Rightword)) direction += glm::normalize(glm::vec3(-Right.x, 0, -Right.z));
    //std::cout << direction.x << " " << direction.z << std::endl;
    Position += velocity * direction;

    // 跳跃与坠落
    if (Have(Character_State::Jumping)) {
        float time_since_jump = (SDL_GetTicks64() - Start_Jump_Time)/10;
        y = v0 * time_since_jump - 0.002 * time_since_jump * time_since_jump;
        //std::cout << y << std::endl;
        Position.y = world->position.y + tofeet.y + y;
        // 掉落到地上后开始行走
        if (!world->OnGround(Position - tofeet)) {
            Position.y = world->position.y + tofeet.y; // 避免掉落到地面之下
            End(Character_State::Jumping);
            if (Have(Character_State::keepJump)) {
                Start(Character_State::Jumping);
                Start_Jump_Time = SDL_GetTicks64();
            }
            else {
                Start(Character_State::Walking);
                //std::cout << "walking" << std::endl;
            }
                
        }
    }
}

void Character::ProcessKeyboardDown(SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_w: {
        Start(Character_State::Forward);
        break;
    }
    case SDLK_s: {
        Start(Character_State::Backword);
        break;
    }
    case SDLK_d: {
        Start(Character_State::Leftword);
        break;
    }
    case SDLK_a: {
        Start(Character_State::Rightword);
        break;
    }
    case SDLK_SPACE: {
        // 落地时才可以再次跳跃
        //std::cout << "space down" << std::endl;
        if (Have(Character_State::Walking)) {
            End(Character_State::Walking);
            Start(Character_State::Jumping);
            Start(Character_State::keepJump);
            Start_Jump_Time = SDL_GetTicks64();
        }
        break;
    }
    case SDLK_LSHIFT: {
        tofeet = glm::vec3(0, height / 2, 0);
        break;
    }
    case SDLK_ESCAPE: {
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
void Character::ProcessKeyboardUp(SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_w: {
        End(Character_State::Forward);
        break;
    }
    case SDLK_s: {
        End(Character_State::Backword);
        break;
    }
    case SDLK_d: {
        End(Character_State::Leftword);
        break;
    }
    case SDLK_a: {
        End(Character_State::Rightword);
        break;
    }
    case SDLK_SPACE: {
        End(Character_State::keepJump);
        break;
    }
    case SDLK_LSHIFT: {
        tofeet = glm::vec3(0, height, 0);
        break;
    }
    default: {
        break;
    }
    }
}

void Character::ProcessMouseMovement(SDL_Event& event) {
    Yaw += event.motion.xrel * MouseSensitivity;
    Pitch -= event.motion.yrel * MouseSensitivity;
    //std::cout << "move " << Yaw << ", " << Pitch << std::endl;
    if (constrainPitch) {
        if (Pitch > 89.0f) Pitch = 89.0f;
        else if (Pitch < -89.0f) Pitch = -89.0f;
    }
    updateCameraVectors();
}

void Character::ProcessMouseScroll(SDL_Event& event) {
    Zoom -= event.wheel.preciseY;
    //std::cout << "wheel " << Zoom << std::endl;
    if (Zoom < 1.0f) Zoom = 1.0f;
    if (Zoom > 45.0f) Zoom = 45.0f;
}
void Character::ProcessEvent(SDL_Event& event) {
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

inline void Character::Start(Character_State s) {
    state |= s;
}
inline void Character::End(Character_State s) {
    state &= ~s;
}
inline bool Character::Have(Character_State s) {
    return (state & s) != 0;
}