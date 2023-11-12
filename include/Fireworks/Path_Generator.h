#ifndef PATH_GENERATOR_H
#define PATH_GENERATOR_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

/**
 *@brief 轨迹生成器用于生成指定的轨迹
 * 
 */
namespace PathGenerator {
    // 贝塞尔曲线轨迹
    glm::vec3 bezier();

    // 模拟重力 在 y 方向
    int gravity(glm::vec3& pos, glm::vec3& v, uint64_t ms_passby, float g);
};

#endif