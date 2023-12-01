#ifndef ANIMATION_0_H
#define ANIMATION_0_H

#include "Animation.h"

class Animation_0 :public Animation {
public:
    Animation_0(std::shared_ptr<Pipe_Firework_Manager> _manager);
    void Build();
    ~Animation_0();
};

#endif