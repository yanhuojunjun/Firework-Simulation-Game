#include "Particle_Emitter.h"

ParticleEmitter::ParticleEmitter() {
    emit_time_passby = 0;
    last_generate_index = 0;
    max_particle_num = 0;
}

ParticleEmitter::ParticleEmitter(
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
) {
    max_particle_num = max_px_num;
    particles.resize(max_px_num);
    va_list args;
    va_start(args, _type);
    switch (_type) {
    case EmitterType::Line:
        emitter = std::make_unique<LineEmitter>();
        break;
    case EmitterType::Circle: {
        double radius = va_arg(args, double);
        int type = va_arg(args, int);
        emitter = std::make_unique<CircleEmitter>(static_cast<float>(radius), static_cast<DirectionType>(type));
        break;
    }
    case EmitterType::Sphere: {
        double radius = va_arg(args, double);
        int type = va_arg(args, int);
        emitter = std::make_unique<SphereEmitter>(static_cast<float>(radius), static_cast<DirectionType>(type));
        break;
    }
    default:
        emitter = std::make_unique<LineEmitter>();
        break;
    }
    va_end(args);
    emitter->SetEmitter(_center, _color, _size, lifetime, _v0, dire, a, delta_time, _texture, _type);
}

void ParticleEmitter::SetParticleEmitter(
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
) {
    max_particle_num = max_px_num;
    particles.resize(max_px_num);
    va_list args;
    va_start(args, _type);
    switch (_type) {
    case EmitterType::Line:
        emitter = std::make_unique<LineEmitter>();
        break;
    case EmitterType::Circle: {
        double radius = va_arg(args, double);
        int type = va_arg(args, int);
        emitter = std::make_unique<CircleEmitter>(static_cast<float>(radius), static_cast<DirectionType>(type));
        break;
    }
    case EmitterType::Sphere: {
        double radius = va_arg(args, double);
        int type = va_arg(args, int);
        emitter = std::make_unique<SphereEmitter>(static_cast<float>(radius), static_cast<DirectionType>(type));
        break;
    }
    default:
        emitter = std::make_unique<LineEmitter>();
        break;
    }
    va_end(args);
    emitter->SetEmitter(_center, _color, _size, lifetime, _v0, dire, a, delta_time, _texture, _type);
}

void ParticleEmitter::EnableColorUpdater(glm::vec4 start, glm::vec4 end) {
    if (!color_points.empty()) color_points.clear();
    enable_color_interpolation = true;
    color_points.push_back(color_t_map{ start, 0.0f });
    color_points.push_back(color_t_map{ end , 1.0f });
}

void ParticleEmitter::AddMidColor(glm::vec4 color, float t) {
    if (t <= 0.0f || t >= 1.0f || enable_color_interpolation == false) return;
    color_points.push_back(color_t_map{ color, t });
    std::sort(color_points.begin(), color_points.end(), [](color_t_map a, color_t_map b) {return a.t < b.t;});
}

void ParticleEmitter::DisableColorUpdater() {
    enable_color_interpolation = false;
}

void ParticleEmitter::EnableRandom(float _lifetime) {
    emitter->EnableRandom(_lifetime);
}

void ParticleEmitter::DisableRandom() {
    emitter->DisableRandom();
}

void ParticleEmitter::Emit() {
    Particle new_particle;
    emitter->EmitParticle(new_particle);
    Generate(new_particle);
}

void ParticleEmitter::Update(uint64_t deltatime) {
    // 更新上一次距离发射经过的时间
    emit_time_passby += deltatime;
    if (emit_time_passby > emitter->emission_delta_time) {
        // 回退发射间隔
        emit_time_passby -= emitter->emission_delta_time;
        // 发射粒子
        Emit();
    }
    // 更新所有粒子
    for (auto& particle : particles) {
        if (particle.alive()) {
            particle.position += static_cast<float>(deltatime) / 1000.0f * particle.velocity;
            if (enable_color_interpolation) ColorInterpolation(particle.color, static_cast<float>(particle.totallifetime - particle.lifetime) / static_cast<float>(particle.totallifetime));
            particle.velocity += emitter->acceleration;
            particle.lifetime -= deltatime;
        }
    }
}

uint64_t ParticleEmitter::Upload(std::vector<float>& vbo_buffer) {
    uint64_t count = 0;
    for (auto& particle : particles) {
        if (particle.alive()) {
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

ParticleEmitter::~ParticleEmitter() {
    particles.clear();
}

void ParticleEmitter::Generate(const Particle& new_particle) {
    // 检查最早使用过的粒子
    for (uint32_t i = last_generate_index;i < max_particle_num;i++) {
        if (!particles[i].alive()) {
            particles[i] = new_particle;
            last_generate_index = i;
            return;
        }
    }
    // 从头开始检查
    for (uint32_t i = 0;i < last_generate_index;i++) {
        if (!particles[i].alive()) {
            particles[i] = new_particle;
            last_generate_index = i;
            return;
        }
    }
    // 全部占满后 抢占最早创建的粒子
    ++last_generate_index;
    if (last_generate_index >= max_particle_num) last_generate_index = 0;
    particles[last_generate_index] = new_particle;
    return;
}

void ParticleEmitter::ColorInterpolation(glm::vec4& color, float t) {
    for (int i = 1;i < color_points.size();i++) {
        if (color_points[i].t >= t) {
            color = ((t - color_points[i - 1].t) * color_points[i].color + (color_points[i].t - t) * color_points[i - 1].color) / (color_points[i].t - color_points[i - 1].t);
            return;
        }
    }
}