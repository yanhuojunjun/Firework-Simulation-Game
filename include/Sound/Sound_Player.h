#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include "SDL_mixer.h"

#include <vector>
#include <string>
#include <queue>
#include <iostream>
enum Sound_Type {
    BK,     // 背景音
    ENV,    // 环境音
    FLY,    // 烟花飞行音
    POUR,   // 烟花喷发音
    FLOW,   // 烟花持续音
    BOOM,   // 烟花爆炸音
    PUT,    // 物体放置音
    CHARA   // 人物音
};

class Sound_Player {
protected:
    // 背景音乐
    Mix_Music* bk_music;
    // 环境音
    //Mix_Chunk* env_chunk;
    // 发射音
    Mix_Chunk* fly;
    // 烟花喷发音
    Mix_Chunk* pour;
    // 烟花持续音
    std::vector<Mix_Chunk*> flow;
    // 爆炸音
    std::vector<Mix_Chunk*> boom;
    // 人物音
    std::vector<Mix_Chunk*> put;

public:
    Sound_Player();
    void StartBKSound();
    void PlayOne(Sound_Type _type);
    ~Sound_Player();
};


#endif