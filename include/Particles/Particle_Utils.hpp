#ifndef PARTICLE_UTILS_HPP
#define PARTICLE_UTILS_HPP

#include <vector>
#include <algorithm>


template<typename T>
struct Interpolation_Tag {
    T value;
    float t;
};

template<typename T>
class Interpolation {
private:
    std::vector< Interpolation_Tag<T> > tags;
public:
    Interpolation() = default;
    Interpolation(T start, T end) {
        tags.push_back(Interpolation_Tag<T>{start, 0.0f});
        tags.push_back(Interpolation_Tag<T>{end, 1.0f});
    }
    void Init(T start, T end) {
        ClearTags();
        tags.push_back(Interpolation_Tag<T>{start, 0.0f});
        tags.push_back(Interpolation_Tag<T>{end, 1.0f});
    }
    void AddTag(T value, float t) {
        if (t <= 0.0f || t >= 1.0f) return;
        tags.push_back(Interpolation_Tag<T>{value, t});
        std::sort(tags.begin(), tags.end(), [](Interpolation_Tag<T> a, Interpolation_Tag<T> b) {return a.t < b.t;});
    }
    bool Remove(float t) {
        for (auto it = tags.begin();it != tags.end();it++) {
            if (it->t == t) {
                tags.erase(it);
                return true;
            }
        }
        return false;
    }
    void ClearTags() {
        tags.clear();
    }
    void GetInterpolation(T& value, float t) {
        for (int i = 1;i < tags.size();i++) {
            if (tags[i].t >= t) {
                value = ((t - tags[i - 1].t) * tags[i].value + (tags[i].t - t) * tags[i - 1].value) / (tags[i].t - tags[i - 1].t);
                return;
            }
        }
    }
};

#endif