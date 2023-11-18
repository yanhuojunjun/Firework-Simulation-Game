#include "Emitter_Updater.h"

void Emitter_Updater::AddPoints(const std::vector<glm::vec2>& new_points) {
    points = new_points;
    // 保证列表中的点是按照第一维(t)升序排序
    std::sort(points.begin(), points.end(), [](glm::vec2 first, glm::vec2 second) {return first.x < second.x;});
}

float Linear_Updater::Update(float t) {
    for (int i = 0;i < points.size();i++) {
        if (points[i].x >= t) {
            // 在最邻近的两点之间进行线性插值
            return ((t - points[i - 1].x) * points[i].y + (points[i].x - t) * points[i - 1].y) / (points[i].x - points[i - 1].x);
        }
    }
}
