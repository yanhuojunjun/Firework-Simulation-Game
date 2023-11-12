#include "particle.h"

particle::particle(const glm::vec3& pos, const glm::vec3& v, const glm::vec4& col, int64_t hp) {
    position = pos;
    velocity = v;
    color = col;
    HP = hp;
}

bool particle::update(int64_t millisecond_passby) {
    HP -= millisecond_passby;
    return HP > 0;
}

bool particle::alive() {
    return HP > 0;
}

/*********************************************************************************************
*********************************************************************************************/

void particle_group::init(uint32_t max_px, const particle& origin_px) {
    birth_millisecond = 0;
    max_alive_particle_number = max_px;
    last_generate_index = 0;
    particles.resize(max_px);
    generate(origin_px);
}

void particle_group::generate(const particle& new_px) {
    // 检查最早使用过的粒子
    for (uint32_t i = last_generate_index;i < max_alive_particle_number;i++) {
        if (!particles[i].alive()) {
            particles[i] = new_px;
            last_generate_index = i;
            return;
        }
    }
    // 从头开始检查
    for (uint32_t i = 0;i < last_generate_index;i++) {
        if (!particles[i].alive()) {
            particles[i] = new_px;
            last_generate_index = i;
            return;
        }
    }
    // 全部占满后 抢占最早创建的粒子
    ++last_generate_index;
    particles[last_generate_index] = new_px;
    return;
}

void particle_group::update(int64_t millisecond_passby) {
    birth_millisecond += millisecond_passby;
    for (auto it = particles.begin();it != particles.end();it++) {
        it->update(millisecond_passby);
        PathGenerator::gravity(it->position, it->velocity, millisecond_passby, 0.01);
    }
}

particle_group::~particle_group() {
    particles.clear();
}

/*********************************************************************************************
*********************************************************************************************/

void particle_generator::circle_surround(particle_group* px, const particle& root, int num, float sp, const glm::vec4& col, int64_t hp) {
    // 旋转轴
    glm::vec3 c = root.velocity;
    // 与 dire 正交的一个速度向量 src
    glm::vec3 src = root.velocity;
    if (src.x != 0) { src.y += 1; src = sp * glm::normalize(glm::cross(src, root.velocity)); }
    else if (src.y != 0) { src.z += 1; src = sp * glm::normalize(glm::cross(src, root.velocity)); }
    else if (src.z != 0) { src.x += 1; src = sp * glm::normalize(glm::cross(src, root.velocity)); }
    else {
        src = sp * glm::vec3(1.0f, 0.0f, 1.0f);
        c = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    // 旋转生成粒子
    glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(360.0f / num), c);
    for (int i = 0;i < num;i++) {
        src = glm::vec3(r * glm::vec4(src, 1.0f));
        px->generate(particle(root.position, src, col, hp));
    }
}