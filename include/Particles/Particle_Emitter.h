#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include "Emitter.h"
#include <algorithm>
struct color_t_map {
    glm::vec4 color;
    float t;
};

class ParticleEmitter {
protected:
    uint64_t emit_time_passby;
    uint64_t last_generate_index;
    uint64_t max_particle_num;
    std::vector<Particle> particles;
    std::unique_ptr<Emitter> emitter;

    /**********************
    *    粒子更新选项      *
    **********************/
    // 一次性发射所有粒子
    bool one_shoot;
    // 对颜色进行插值更新
    bool enable_color_interpolation;
    std::vector<color_t_map> color_points;

public:
    ParticleEmitter();
    ParticleEmitter(
        uint64_t max_px_num,
        glm::vec3 _center,
        glm::vec4 _color,
        float _size,
        int64_t lifetime,
        float _v0,
        glm::vec3 dire,
        glm::vec3 a,
        uint64_t delta_time,
        unsigned int _texture,
        EmitterType _type,
        ...
    );

    void SetParticleEmitter(
        uint64_t max_px_num,
        glm::vec3 _center,
        glm::vec4 _color,
        float _size,
        int64_t lifetime,
        float _v0,
        glm::vec3 dire,
        glm::vec3 a,
        uint64_t delta_time,
        unsigned int _texture,
        EmitterType _type,
        ...
    );

    void EnableOneShoot();
    void DisableOneShoot();

    void EnableColorUpdater(glm::vec4 start, glm::vec4 end);
    void AddMidColor(glm::vec4 color, float t);
    void DisableColorUpdater();

    void EnableRandom(float _lifetime);
    void DisableRandom();
    void Emit();
    void Update(uint64_t deltatime);
    uint64_t Upload(std::vector<float>& vbo_buffer);
    ~ParticleEmitter();
protected:
    void Generate(const Particle& new_particle);
    void ColorInterpolation(glm::vec4& color, float t);
};

#endif