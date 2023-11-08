#ifndef CHARACTER_H
#define CHARACTER_H

#include "ICamera.h"
#include "SDL.h"
#include "World.h"

enum Character_State {
    Forward = 1,
    Backword = 2,
    Leftword = 4,
    Rightword = 8,
    Jumping = 16,
    Dropping = 32,
    Walking = 64,
    keepJump = 128 // 解决先长按空格 然后长按另一个键导致无法连续跳跃的问题
};

class Character :public ICamera
{
public:
    // 控制移动距离
    Uint64 Last_Frame_time;
    Uint64 Time_Pass_By;

    // 控制掉落速度
    Uint64 Start_Jump_Time;
    // 初始跳跃速度
    float v0;
    
    World* world;
    // 人物高度
    float height;
    glm::vec3 tofeet;
    // 人物状态
    unsigned int state;


public:
    Character(World* w);
    void Update();

    void ProcessKeyboardDown(SDL_Event& event);
    void ProcessKeyboardUp(SDL_Event& event);

    void ProcessMouseMovement(SDL_Event& event);

    void ProcessMouseScroll(SDL_Event& event);

    void ProcessEvent(SDL_Event& event);
    inline void Start(Character_State s);
    inline void End(Character_State s);
    inline bool Have(Character_State s);
};



#endif