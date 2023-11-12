#include "Path_Generator.h"

int PathGenerator::gravity(glm::vec3& pos, glm::vec3& v, uint64_t ms_passby, float g) {
    float t = (float)ms_passby / 1000;
    pos += v * t;
    pos.y += g * t * t / 2;
    v.y += g * t;
    return 0;
}