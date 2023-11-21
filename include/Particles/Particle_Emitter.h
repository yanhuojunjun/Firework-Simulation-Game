#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include "Emitter.h"
#include <algorithm>

// 进行颜色插值的结构
// 实现颜色随时间变化而变化
//颜色 - 时刻
struct color_t_map {
    glm::vec4 color;
    float t;
};

class ParticleEmitter {
protected:
    uint64_t emit_time_passby;          // 粒子发射器距离上次发射经过的时间
    uint64_t last_generate_index;       // 上一次产生粒子的数组下标
    uint64_t max_particle_num;          // 最大容纳的粒子数
    std::vector<Particle> particles;    // 粒子数组
    std::unique_ptr<Emitter> emitter;   // 发射器 用于对粒子设置参数

    /**********************
    *    粒子更新选项      *
    **********************/
    // 一次性发射所有粒子 爆炸效果
    bool one_shoot;
    // 对颜色进行插值更新
    bool enable_color_interpolation;
    std::vector<color_t_map> color_points;

public:
    ParticleEmitter();
    /**
     *@brief Construct a new Particle Emitter object
     * 
     * @param max_px_num 最大粒子数
     * @param _center 粒子发射器中心
     * @param _color 粒子发射器颜色
     * @param _size 粒子大小
     * @param lifetime 粒子生命值
     * @param _v0 粒子初速度
     * @param dire 粒子发射器朝向
     * @param a 粒子的加速度
     * @param delta_time 发射间隔
     * @param _texture 粒子使用的纹理
     * @param _type 粒子发射器种类
     * @param ... 根据不同的种类需要传递不同数量的参数
     */
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

    // 启用一次性发射
    void EnableOneShoot();
    void DisableOneShoot();

    // 启用颜色线性插值 产生渐变效果
    // 颜色从start到end线性变化
    void EnableColorUpdater(glm::vec4 start, glm::vec4 end);
    /**
     *@brief 增加颜色变化的中间颜色
     * 
     * @param color 颜色
     * @param t 变为该颜色的时间, 范围 [0, 1]
     */
    void AddMidColor(glm::vec4 color, float t);
    void DisableColorUpdater();

    /**
     *@brief 启用生命值在误差范围内随机浮动
     * 
     * @param _lifetime 生命值随机浮动的误差, 相对于粒子生命值的百分比, 范围[0, 1]
     */
    void EnableRandom(float _lifetime);
    void DisableRandom();

    // 发射一个粒子
    void Emit();

    // 更新所有粒子
    void Update(uint64_t deltatime);

    /**
     *@brief 上传所有粒子的数据
     * 
     * @param vbo_buffer vbo缓冲
     * @return uint64_t 返会上传的粒子数量
     */
    uint64_t Upload(std::vector<float>& vbo_buffer);
    ~ParticleEmitter();
protected:
    void Generate(const Particle& new_particle);
    /**
     *@brief 颜色插值
     * 
     * @param color 粒子颜色的引用, 对此进行修改
     * @param t 粒子剩余的存活时间
     */
    void ColorInterpolation(glm::vec4& color, float t);
};

#endif