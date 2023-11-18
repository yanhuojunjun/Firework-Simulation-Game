#ifndef EMITTER_UPDATER_H
#define EMITTER_UPDATER_H

#include "glm.hpp"
#include "gtc/type_ptr.hpp"

#include <vector>
#include <algorithm>

enum UpdateType {
    Linear
};

class Emitter_Updater {
public:
    
    /**********************
    *       接口          *
    **********************/
    virtual float Update(float t) = 0;

    /**********************
    *       成员方法       *
    **********************/
    void AddPoints(const std::vector<glm::vec2> &new_points);
    virtual ~Emitter_Updater() = default;
protected:
    std::vector<glm::vec2> points; // 待插值的点
};

class Linear_Updater :public Emitter_Updater {
public:
    float Update(float t) override;
};

#endif