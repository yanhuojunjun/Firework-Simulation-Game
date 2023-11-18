#include "Emitter.h"

void Emitter::SetEmitter(glm::vec3 _center, glm::vec4 _color, float _size, int64_t lifetime, float _v0, glm::vec3 dire, glm::vec3 a, uint64_t delta_time, unsigned int _texture, EmitterType _type) {
    emitter_center = _center;
    particle_color = _color;
    particle_size = _size;
    particle_lifetime = lifetime;
    initial_velocity = _v0;
    emission_direction = dire;
    acceleration = a;
    emission_delta_time = delta_time;
    texture = _texture;
    emitter_type = _type;
}

void Emitter::EnableRandom(float _lifetime) {
    if(_lifetime < 1.0f) lifetime_random = _lifetime;
}

void Emitter::DisableRandom() {
    lifetime_random = 0.0f;
}

void LineEmitter::EmitParticle(Particle& particle) {
    particle.position = emitter_center;
    particle.color = particle_color;
    particle.size = particle_size;
    // 沿发射器方向运动
    particle.velocity = initial_velocity * emission_direction;
    particle.totallifetime = particle_lifetime + lifetime_random * glm::linearRand(-1.0f, 1.0f) * particle_lifetime;
    particle.lifetime = particle.totallifetime;
}

CircleEmitter::CircleEmitter(float _radius, DirectionType d_type) :radius(_radius), direction_type(d_type) {}

void CircleEmitter::EmitParticle(Particle& particle) {
    // 旋转轴
    glm::vec3 axis = emission_direction;
    // 与 axis 正交的一个速度向量 src
    glm::vec3 src = axis;
    if (src.x != 0) { src.y += 1; src = initial_velocity * glm::normalize(glm::cross(src, emission_direction)); }
    else if (src.y != 0) { src.z += 1; src = initial_velocity * glm::normalize(glm::cross(src, emission_direction)); }
    else if (src.z != 0) { src.x += 1; src = initial_velocity * glm::normalize(glm::cross(src, emission_direction)); }
    else {
        // 如果速度为 0 默认在 x-z 平面生成圆
        src = initial_velocity * glm::vec3(1.0f, 0.0f, 1.0f);
        axis = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    // 第二个正交向量
    glm::vec3 src2 = glm::normalize(glm::cross(axis, src));
    // 根据朝向类型生成速度
    if (direction_type == DirectionType::Outer) {
        // 随机生成朝向圆心外方向的速度
        glm::mat4 rotate_mat = glm::rotate(glm::mat4(1.0f), 2.0f * glm::pi<float>() * glm::linearRand(0.0f, 1.0f), axis);
        particle.velocity = glm::vec3(rotate_mat * glm::vec4(src, 1.0f));
    }
    else {
        particle.velocity = emission_direction;
    }
    // 随机线性组合 src 与 src2 得到一个正交于 axis 的随机方向向量
    // 然后 normalize * radius 限定偏移在半径范围内
    particle.position = emitter_center + radius * glm::normalize(static_cast<float>(glm::linearRand(-1.0, 1.0)) * src2 + static_cast<float>(glm::linearRand(-1.0, 1.0)) * src);
    particle.color = particle_color;
    particle.size = particle_size;
    particle.totallifetime = particle_lifetime + lifetime_random * glm::linearRand(-1.0f, 1.0f) * particle_lifetime;
    particle.lifetime = particle.totallifetime;
}

SphereEmitter::SphereEmitter(float _radius, DirectionType d_type) :radius(_radius), direction_type(d_type) {}

void SphereEmitter::EmitParticle(Particle& particle) {
    // 随机生成朝向球心外方向的速度
    if (direction_type == DirectionType::Outer) particle.velocity = initial_velocity * glm::normalize(glm::vec3(glm::linearRand(-1.0, 1.0), glm::linearRand(-1.0, 1.0), glm::linearRand(-1.0, 1.0)));
    else particle.velocity = initial_velocity * emission_direction;
    // 空间中产生随机方向
    // 然后 normalize * radius 限定偏移在半径范围内
    particle.position = emitter_center + radius * glm::normalize(glm::vec3(glm::linearRand(-1.0, 1.0), glm::linearRand(-1.0, 1.0), glm::linearRand(-1.0, 1.0)));
    particle.color = particle_color;
    particle.size = particle_size;
    particle.totallifetime = particle_lifetime + lifetime_random * glm::linearRand(-1.0f, 1.0f) * particle_lifetime;
    particle.lifetime = particle.totallifetime;
    
}
