#include "Particle_Emitter.h"

ParticleEmitter::ParticleEmitter() {
    emit_time_passby = 0;
    last_generate_index = 0;
    max_particle_num = 0;
    lifetime = 0;
    total_lifetime = 0;
    valid = true;
    // 更新选项默认为 false
    one_shoot = false;
    enable_color_interpolation = false;
    enable_velocity_interpolation = false;
    enable_emitter_radial_acc = false;
}

ParticleEmitter::ParticleEmitter(
    uint64_t _e_max_px_num,
    int64_t _e_total_lifetime,
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
    EmitterType _e_type,
    ...
) {
    max_particle_num = _e_max_px_num;
    lifetime = _e_total_lifetime;
    total_lifetime = _e_total_lifetime;
    valid = true;
    particles.resize(_e_max_px_num);
    va_list args;
    va_start(args, _e_type);
    switch (_e_type) {
    case EmitterType::Line: {
        double div = va_arg(args, double);
        emitter = std::make_shared<LineEmitter>(static_cast<float>(div));
        break;
    }
    case EmitterType::Circle: {
        double radius = va_arg(args, double);
        int type = va_arg(args, int);
        emitter = std::make_shared<CircleEmitter>(static_cast<float>(radius), static_cast<DirectionType>(type));
        break;
    }
    case EmitterType::Sphere: {
        double radius = va_arg(args, double);
        int type = va_arg(args, int);
        emitter = std::make_shared<SphereEmitter>(static_cast<float>(radius), static_cast<DirectionType>(type));
        break;
    }
    default:
        emitter = std::make_shared<LineEmitter>(0.0f);
        break;
    }
    va_end(args);
    emitter->SetEmitter(
        _p_center,
        _p_color,
        _p_size,
        _p_lifetime,
        _p_init_velocity,
        _p_init_direction,
        _p_acceleration,
        _p_delta_time,
        _p_texture,
        _e_velocity,
        _e_direction,
        _e_acceleration,
        _e_type
        );
    one_shoot = false;
    enable_color_interpolation = false;
    enable_velocity_interpolation = false;
    enable_emitter_radial_acc = false;
}

void ParticleEmitter::SetParticleEmitter(
    uint64_t _e_max_px_num,
    int64_t _e_total_lifetime,
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
    EmitterType _e_type,
    ...
) {
    valid = true;
    max_particle_num = _e_max_px_num;
    lifetime = _e_total_lifetime;
    total_lifetime = _e_total_lifetime;
    particles.resize(_e_max_px_num);
    va_list args;
    va_start(args, _e_type);
    switch (_e_type) {
    case EmitterType::Line: {
        double div = va_arg(args, double);
        emitter = std::make_shared<LineEmitter>(static_cast<float>(div));
        break;
    }
    case EmitterType::Circle: {
        double radius = va_arg(args, double);
        int type = va_arg(args, int);
        emitter = std::make_shared<CircleEmitter>(static_cast<float>(radius), static_cast<DirectionType>(type));
        break;
    }
    case EmitterType::Sphere: {
        double radius = va_arg(args, double);
        int type = va_arg(args, int);
        emitter = std::make_shared<SphereEmitter>(static_cast<float>(radius), static_cast<DirectionType>(type));
        break;
    }
    default:
        emitter = std::make_shared<LineEmitter>(0.0f);
        break;
    }
    va_end(args);
    emitter->SetEmitter(
        _p_center,
        _p_color,
        _p_size,
        _p_lifetime,
        _p_init_velocity,
        _p_init_direction,
        _p_acceleration,
        _p_delta_time,
        _p_texture,
        _e_velocity,
        _e_direction,
        _e_acceleration,
        _e_type
    );
    one_shoot = false;
    enable_color_interpolation = false;
    enable_velocity_interpolation = false;
    enable_emitter_radial_acc = false;
}

void ParticleEmitter::EnableOneShoot() {
    one_shoot = true;
    // 发射间隔设置为无穷
    emitter->emission_delta_time = 0xffffffff;
    // 删除原有的所有粒子
    for (int i = 0;i < max_particle_num;i++) {
        particles[i].lifetime = 0;
    }
    // 一次性产生所有粒子
    for (int i = 0;i < max_particle_num;i++) {
        Emit();
    }
}

void ParticleEmitter::DisableOneShoot() {
    one_shoot = false;
}

void ParticleEmitter::EnableColorUpdater(glm::vec4 start, glm::vec4 end) {
    enable_color_interpolation = true;
    color_interpolation.Init(start, end);
}

void ParticleEmitter::AddMidColor(glm::vec4 color, float t) {
    if (enable_color_interpolation == false) return;
    color_interpolation.AddTag(color, t);
}

void ParticleEmitter::DisableColorUpdater() {
    enable_color_interpolation = false;
}

void ParticleEmitter::EnableVelocityUpdater(float start, float end) {
    enable_velocity_interpolation = true;
    velocity_interpolation.Init(start, end);
}
void ParticleEmitter::AddMidVelocity(float v, float t) {
    if (!enable_velocity_interpolation) return;
    velocity_interpolation.AddTag(v, t);
}
void ParticleEmitter::DisableVelocityUpdater() {
    enable_velocity_interpolation = false;
}

void ParticleEmitter::EnableRadialAcc(float _radial_acc, glm::vec3 _radial_axle) {
    enable_emitter_radial_acc = true;
    radial_axle = _radial_axle;
    emitter->emitter_radial_acceleration = _radial_acc;
}
void ParticleEmitter::DisableRadialAcc() {
    enable_emitter_radial_acc = false;
}

void ParticleEmitter::EnableLifetimeTolerance(float _p_lifetime) {
    emitter->EnableLifetimeTolerance(_p_lifetime);
}

void ParticleEmitter::DisableLifetimeTolerance() {
    emitter->DisableLifetimeTolerance();
}

void ParticleEmitter::Validate() {
    valid = true;
}

void ParticleEmitter::Invalidate() {
    valid = false;
}

bool ParticleEmitter::isValid() {
    return valid;
}
bool ParticleEmitter::isAlive() {
    return lifetime > 0;
}

void ParticleEmitter::Emit() {
    // 检查最早使用过的粒子
    for (uint32_t i = last_generate_index;i < max_particle_num;i++) {
        if (!particles[i].alive()) {
            emitter->EmitParticle(particles[i]);
            last_generate_index = i;
            return;
        }
    }
    // 从头开始检查
    for (uint32_t i = 0;i < last_generate_index;i++) {
        if (!particles[i].alive()) {
            emitter->EmitParticle(particles[i]);
            last_generate_index = i;
            return;
        }
    }
    // 全部占满后 抢占最早创建的粒子
    ++last_generate_index;
    if (last_generate_index >= max_particle_num) last_generate_index = 0;
    emitter->EmitParticle(particles[last_generate_index]);
}

bool ParticleEmitter::Update(uint64_t deltatime) {
    // 失效粒子不进行更新
    if (!valid) return valid;
    // count 用于统计存活的粒子
    int count = 0;
    // 更新距离上一次发射经过的时间
    emit_time_passby += deltatime;
    // 更新粒子发射器生命值
    if (lifetime > 0) lifetime -= deltatime;
    // 判断发射条件, 如果满足就发射粒子
    // 非one_shoot模式, 因为one_shoot在启用时就创建好了所有粒子, 所以不能再次添加
    // 距离上一次发射经过的时间超过了发射间隔
    // 粒子发射器生命值大于0, 否则不再产生新粒子, 当所有粒子消散后才会失效(valid == false)
    if (!one_shoot && emit_time_passby > emitter->emission_delta_time && lifetime > 0) {
        emit_time_passby -= emitter->emission_delta_time;   // 回退发射间隔
        Emit(); // 发射粒子
    }
    float delta_time_second = static_cast<float>(deltatime) / 1000.0f;  // 计算经过的时间(秒)
    // 更新所有粒子
    for (auto& particle : particles) {
        if (particle.alive()) { // 只有存活的粒子需要更新
            // 粒子颜色更新 如果启用了插值就进行插值否则使用初始设置的颜色(不进行更改)
            if (enable_color_interpolation) color_interpolation.GetInterpolation(particle.color, static_cast<float>(particle.totallifetime - particle.lifetime) / static_cast<float>(particle.totallifetime));
            // 粒子速度更新
            particle.velocity += delta_time_second * emitter->particle_initial_acceleration;
            // 粒子生命值更新
            particle.lifetime -= deltatime;
            // 速度线性插值
            // 不修改速度为了避免固定的加速度 对不同的速度产生不同的效果
            if (enable_velocity_interpolation) {
                float alpha = 0.0f;
                velocity_interpolation.GetInterpolation(alpha, static_cast<float>(particle.totallifetime - particle.lifetime) / static_cast<float>(particle.totallifetime));
                particle.position += delta_time_second * alpha * glm::normalize(particle.velocity);
            }
            else {
                // 粒子位置默认更新
                particle.position += delta_time_second * particle.velocity;
            }
            count++; // 记录存活粒子数
        }
    }
    // 更新粒子发射器速度
    // 线性加速度
    emitter->emitter_velocity += delta_time_second * emitter->emitter_acceleration;
    // 径向加速度
    if (enable_emitter_radial_acc) emitter->emitter_velocity += delta_time_second * emitter->emitter_radial_acceleration * glm::normalize(glm::cross(radial_axle, emitter->emitter_velocity));
    emitter->emitter_center += delta_time_second * emitter->emitter_velocity;

    // 一次性的粒子发射器在所有粒子消散后需要被删除(即失效)
    // 非一次性粒子发射器在超时未发射后需要被删除(即失效)
    if (count == 0 && (one_shoot || emit_time_passby > emitter->emission_delta_time)) {
        valid = false;
    }
    return valid;
}

uint64_t ParticleEmitter::Upload(std::vector<float>& vbo_buffer) {
    if (!valid) return 0;
    uint64_t count = 0;
    for (auto& particle : particles) {
        if (particle.alive()) { // 只有存活的粒子需要上传渲染
            vbo_buffer.push_back(particle.position.x);
            vbo_buffer.push_back(particle.position.y);
            vbo_buffer.push_back(particle.position.z);
            vbo_buffer.push_back(particle.color.r);
            vbo_buffer.push_back(particle.color.g);
            vbo_buffer.push_back(particle.color.b);
            vbo_buffer.push_back(particle.color.a);
            vbo_buffer.push_back(particle.size);
            ++count;
        }
    }
    return count;
}

glm::vec3 ParticleEmitter::GetEmitterCenter() {
    return emitter->emitter_center;
}

ParticleEmitter::~ParticleEmitter() {
    particles.clear();
}