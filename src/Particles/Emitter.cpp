#include "Emitter.h"

void Emitter::SetEmitter(
    glm::vec3 _p_center,
    glm::vec4 _p_color,
    float _p_size,
    int64_t _p_lifetime,
    float _p_init_velocity,
    glm::vec3 _p_init_direction,
    glm::vec3 _p_acceleration,
    uint64_t _p_delta_time,
    unsigned int _p_texture,
    float _e_velocity,
    glm::vec3 _e_direction,
    glm::vec3 _e_acceleration,
    EmitterType _e_type
) {
    // 设置必需参数
    emitter_center = _p_center;
    particle_color = _p_color;
    particle_size = _p_size;
    particle_lifetime = _p_lifetime;
    particle_initial_velocity = _p_init_velocity;
    particle_initial_direction = glm::normalize(_p_init_direction);
    particle_initial_acceleration = _p_acceleration;
    emission_delta_time = _p_delta_time;
    texture = _p_texture;
    emitter_velocity = _e_velocity * glm::normalize(_e_direction);
    emitter_acceleration = _e_acceleration;
    emitter_type = _e_type;
    // 可选选项默认为 0.0f
    emitter_radial_acceleration = 0.0f;
    lifetime_tolerance = 0.0f;
}

void Emitter::EnableLifetimeTolerance(float _lifetime_tolerance) {
    if (_lifetime_tolerance < 1.0f && _lifetime_tolerance > 0.0f) lifetime_tolerance = _lifetime_tolerance;
}

void Emitter::DisableLifetimeTolerance() {
    lifetime_tolerance = 0.0f;
}

/********************************************************
*                      线型发射器                        *
********************************************************/

LineEmitter::LineEmitter(float _divergence) {
    if (_divergence <= 1.0f && _divergence >= 0.0f) divergence = _divergence;
}

void LineEmitter::EmitParticle(Particle& particle) {
    particle.position = emitter_center;
    particle.color = particle_color;
    particle.size = particle_size;
    // 散度为 0.0f 沿发射器方向运动
    // 否则限定在散度范围内随机发散
    if (divergence == 0.0f) particle.velocity = particle_initial_velocity * particle_initial_direction;
    else particle.velocity = particle_initial_velocity * glm::normalize(particle_initial_direction - 2.0f * divergence * glm::normalize(glm::sphericalRand(divergence)));
    // 生命值误差为 0.0f 则是固定值
    // 否则添加在误差容许范围内的随机误差
    if (lifetime_tolerance == 0.0f) particle.totallifetime = particle_lifetime;
    else particle.totallifetime = particle_lifetime + lifetime_tolerance * glm::linearRand(-1.0f, 1.0f) * particle_lifetime;
    // 初始生命值
    particle.lifetime = particle.totallifetime;
}

/********************************************************
*                      圆型发射器                        *
********************************************************/

CircleEmitter::CircleEmitter(float _radius, DirectionType d_type) :radius(_radius), direction_type(d_type) {}

void CircleEmitter::EmitParticle(Particle& particle) {
    // 旋转轴
    glm::vec3 axis = particle_initial_direction;
    // 与 axis 正交的一个速度向量 src
    glm::vec3 src = axis;
    if (src.x != 0) { src.y += 1; src = particle_initial_velocity * glm::normalize(glm::cross(src, particle_initial_direction)); }
    else if (src.y != 0) { src.z += 1; src = particle_initial_velocity * glm::normalize(glm::cross(src, particle_initial_direction)); }
    else if (src.z != 0) { src.x += 1; src = particle_initial_velocity * glm::normalize(glm::cross(src, particle_initial_direction)); }
    else {
        // 如果速度为 0 默认在 x-z 平面生成圆
        src = particle_initial_velocity * glm::vec3(1.0f, 0.0f, 1.0f);
        axis = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    // 第二个正交向量
    glm::vec3 src2 = glm::normalize(glm::cross(axis, src));
    /*
        以上建立了一个以发射器为原点的单位正交坐标系(axis - src- src2)
    */
    // 根据方向类型生成速度
    // 随机线性组合 src 与 src2 得到一个正交于 axis 的随机方向向量
    // velocity 为指向圆心外的单位速度 或者 为0
    glm::vec3 velocity = glm::normalize(static_cast<float>(glm::linearRand(-1.0, 1.0)) * src2 + static_cast<float>(glm::linearRand(-1.0, 1.0)) * src);
    if (direction_type == DirectionType::Outer) {
        particle.velocity = particle_initial_velocity*velocity;
    }
    else {
        particle.velocity = particle_initial_velocity * particle_initial_direction;
    }
    // radius * velocity 限定偏移在圆周上或圆心
    particle.position = emitter_center + radius * velocity;
    particle.color = particle_color;
    particle.size = particle_size;
    // 生命值误差为 0.0f 则是固定值
    // 否则添加在误差容许范围内的随机误差
    if (lifetime_tolerance == 0.0f) particle.totallifetime = particle_lifetime;
    else particle.totallifetime = particle_lifetime + lifetime_tolerance * glm::linearRand(-1.0f, 1.0f) * particle_lifetime;
    particle.lifetime = particle.totallifetime;
}

/********************************************************
*                      球型发射器                        *
********************************************************/

SphereEmitter::SphereEmitter(float _radius, DirectionType d_type) :radius(_radius), direction_type(d_type) {}

void SphereEmitter::EmitParticle(Particle& particle) {
    // 随机生成朝向球心外方向的速度
    if (direction_type == DirectionType::Outer) particle.velocity = particle_initial_velocity * glm::normalize(glm::sphericalRand(1.0f));
    else particle.velocity = particle_initial_velocity * particle_initial_direction;
    // 空间中产生随机方向
    // 然后限定偏移在半径上
    particle.position = emitter_center + radius * glm::normalize(glm::sphericalRand(1.0f));
    particle.color = particle_color;
    particle.size = particle_size;
    // 生命值误差为 0.0f 则是固定值
    // 否则添加在误差容许范围内的随机误差
    if (lifetime_tolerance == 0.0f) particle.totallifetime = particle_lifetime;
    else particle.totallifetime = particle_lifetime + lifetime_tolerance * glm::linearRand(-1.0f, 1.0f) * particle_lifetime;
    particle.lifetime = particle.totallifetime;

}
