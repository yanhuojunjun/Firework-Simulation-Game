#include "Sound_Player.h"

Sound_Player::Sound_Player() {
    std::string path = "";
    bk_music = Mix_LoadMUS("sound/ThisIsMe.mp3");

    // 读取飞行音效
    fly = Mix_LoadWAV("sound/firework_fly1.wav");
    if (fly != NULL) {
        Mix_VolumeChunk(fly, 50);
    }
    else {
        std::cout << "failed to read file: sound/firework_fly1.wav" << std::endl;
    }

    // 读取喷发音效
    pour = Mix_LoadWAV("sound/firework_fly0.wav");
    if (pour != NULL) {
        Mix_VolumeChunk(pour, 50);
    }
    else {
        std::cout << "failed to read file: sound/firework_fly0.wav" << std::endl;
    }

    // 持续烟花音效
    if (!flow.empty()) flow.clear();
    for (int i = 0;i < 2;i++) {
        path = std::string("sound/firework_c") + std::to_string(i) + std::string(".mp3");
        Mix_Chunk* temp = Mix_LoadWAV(path.data());
        if (temp != NULL) {
            flow.push_back(temp);
            Mix_VolumeChunk(temp, 50);
        }
        else {
            std::cout << "flow failed path: " << path << std::endl;
        }
    }
    std::cout << "flow num: " << flow.size() << std::endl;

    // 爆炸音效
    if (!boom.empty()) boom.clear();
    for (int i = 0;i < 5;i++) {
        path = std::string("sound/firework_boom") + std::to_string(i) + std::string(".wav");
        Mix_Chunk* temp = Mix_LoadWAV(path.data());
        if (temp != NULL) {
            boom.push_back(temp);
            Mix_VolumeChunk(temp, 50);
        }
    }
    std::cout << "boom num: " << boom.size() << std::endl;

    // 物体放置音效
    if (!put.empty()) put.clear();
    for (int i = 0;i < 4;i++) {
        path = std::string("sound/put") + std::to_string(i) + std::string(".mp3");
        Mix_Chunk* temp = Mix_LoadWAV(path.data());
        if (temp != NULL) {
            put.push_back(temp);
            Mix_VolumeChunk(temp, 50);
        }
    }
    std::cout << "put num: " << put.size() << std::endl;

    enable_sound = false;
}

void Sound_Player::StartBKSound() {
    // 播放背景音频并调整音量至合适大小
    Mix_PlayMusic(bk_music, -1);
    Mix_VolumeMusic(80);
}

void Sound_Player::CloseBKSound() {
    Mix_HaltMusic();
}

void Sound_Player::StartSound() {
    enable_sound = true;
}

void Sound_Player::CloseSound() {
    enable_sound = false;
}

void Sound_Player::PlayOne(Sound_Type _type) {
    if (!enable_sound) return;
    switch (_type)
    {
        
    case Sound_Type::FLY: {
        Mix_PlayChannel(-1, fly, 0);
        break;
    }
    case Sound_Type::POUR: {
        Mix_PlayChannel(-1, pour, 0);
        break;
    }
    case Sound_Type::FLOW: {
        if (flow.size() != 0) {
            int index = rand() % flow.size();
            Mix_PlayChannel(-1, flow[index], 0);
        }
        break;
    }
    case Sound_Type::BOOM: {
        if (boom.size() != 0) {
            int index = rand() % boom.size();
            Mix_PlayChannel(-1, boom[index], 0);
        }
        break;
    }
    case Sound_Type::PUT: {
        if (put.size() != 0) {
            int index = rand() % put.size();
            Mix_PlayChannel(-1, put[index], 0);
        }
        break;
    }
    default:
        break;
    }
}

Sound_Player::~Sound_Player() {
    Mix_FreeChunk(fly);
    for (int i = 0;i < boom.size();i++) {
        Mix_FreeChunk(boom[i]);
    }
    for (int i = 0;i < flow.size();i++) {
        Mix_FreeChunk(flow[i]);
    }
    for (int i = 0;i < put.size();i++) {
        Mix_FreeChunk(put[i]);
    }
    Mix_FreeMusic(bk_music);
}