#include "particle.h"

particle::particle() {
    state = particle_status::P_DEAD;
}

particle::particle(const glm::vec3& pos, const glm::vec3& v, const glm::vec4& col, int64_t hp) {
    position = pos;
    velocity = v;
    color = col;
    HP = hp;
    state = particle_status::P_ALIVE;
}

int particle::update(int64_t millisecond_passby) {
    // 更新生命值
    HP -= millisecond_passby;
    switch (state) {
    case particle_status::P_ALIVE:
        // 默认自然下坠
        PathGenerator::gravity(position, velocity, millisecond_passby, -0.5);
        // 状态转移
        if (HP <= 0) state = particle_status::P_DEAD;
        break;
    case particle_status::P_DYING:
        // 默认没有亡语
        break;
    default:
        break;
    }
    return 0;
}

bool particle::alive() {
    // 只要不是死亡都是存活的
    return state != particle_status::P_DEAD;
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
    last_generate_index = (last_generate_index + 1) % max_alive_particle_number;
    particles[last_generate_index] = new_px;
    return;
}

void particle_group::update(int64_t millisecond_passby) {
    birth_millisecond += millisecond_passby;
    for (auto it = particles.begin();it != particles.end();it++) {
        it->update(millisecond_passby);
    }
}

void particle_group::upload(std::vector<glm::vec4>& vbo_buffer, particle_attr attr) {
    if (attr == particle_attr::P_POSITON) {
        for (auto px : particles) {
            if (px.alive()) vbo_buffer.push_back(glm::vec4(px.position, 1.0f));
        }
    }
    else if (attr == particle_attr::P_COLOR) {
        for (auto px : particles) {
            if (px.alive()) vbo_buffer.push_back(px.color);
        }
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