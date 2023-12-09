#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include "Emitter.h"
#include "Particle_Utils.hpp"

// 粒子发射器
// 负责维护粒子数组 更新粒子 上传粒子渲染数据
class ParticleEmitter {
protected:
    /**********************
    *       必需参数       *
    **********************/
    uint64_t max_particle_num;           // 最大容纳的粒子数
    std::vector<Particle> particles;     // 粒子数组
    std::shared_ptr<Emitter> emitter;    // 发射器 用于对粒子设置参数
    bool valid;                          // true->粒子发射器是合法的 会在render中被渲染
    int64_t lifetime;                    // 粒子发射器的剩余存活时间
    int64_t total_lifetime;              // 粒子发射器总存活时间
    uint64_t emit_time_passby;           // 粒子发射器距离上次发射经过的时间
    uint64_t last_generate_index;        // 上一次产生粒子的数组下标

    /**********************
    *    粒子更新选项      *
    **********************/
    
    bool one_shoot;                                     // 一次性发射所有(max_particle_num 个)粒子
    bool enable_color_interpolation;                    // 是否启用颜色插值更新
    Interpolation <glm::vec4> color_interpolation;      // 颜色插值标记点
    bool enable_velocity_interpolation;                 // 是否启用粒子速度插值更新
    Interpolation<float> velocity_interpolation;        // 速度插值标记点
    bool enable_lifetime_interpolation;                 // 启用粒子生命值线性插值
    Interpolation<int64_t> lifetime_interpolation;     // 粒子生命值插值标记点
    bool enable_emitter_radial_acc;                     // 是否启用粒子发射器径向加速度
    glm::vec3 radial_axle;                              // 粒子发射器径向加速度指向的中心轴

public:
    ParticleEmitter();
     /**
      *@brief 构造粒子发射器
      * 
      * @param _e_max_px_num uint64_t 粒子发射器可容纳的最大粒子数
      * @param _e_total_lifetime int64_t 粒子发射器存活时间
      * @param _p_center vec3 粒子产生的中心位置, 也是发射器中心所在的位置坐标
      * @param _p_color vec4 发射器产生的粒子的颜色, 可以激活颜色的线性插值, 从而产生渐变效果, 一个发射器中的所有粒子共用一种插值方式, 需要归一化到 [0, 1]
      * @param _p_size float 粒子的大小
      * @param _p_lifetime int64_t 粒子的生命周期, 即存活时间
      * @param _p_init_velocity float 粒子的初始速度大小, 配合粒子初始方向使用
      * @param _p_init_direction vec3 粒子的初始方向, 内部会进行单位化
      * @param _p_acceleration vec3 粒子的加速度, 发射器的所有粒子共用该加速度
      * @param _p_delta_time uint64_t 粒子产生的时间间隔
      * @param _p_texture unsigned int 发射器中粒子使用的纹理, 由 glGenTextures 产生
      * @param _e_velocity float 发射器运动的初始速度
      * @param _e_direction vec3 发射器运动的初始初始方向
      * @param _e_acceleration vec3 发射器运动的加速度
      * @param _e_type EmitterType 发射器的类型: 线型/圆型/球型
      * @param ... 根据粒子发射器类型传递对应参数
      */
    ParticleEmitter(
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
    );

    /**
      *@brief 设置粒子发射器参数
      *
      * @param _e_max_px_num uint64_t 粒子发射器可容纳的最大粒子数
      * @param _e_total_lifetime int64_t 粒子发射器存活时间
      * @param _p_center vec3 粒子产生的中心位置, 也是发射器中心所在的位置坐标
      * @param _p_color vec4 发射器产生的粒子的颜色, 可以激活颜色的线性插值, 从而产生渐变效果, 一个发射器中的所有粒子共用一种插值方式, 需要归一化到 [0, 1]
      * @param _p_size float 粒子的大小
      * @param _p_lifetime int64_t 粒子的生命周期, 即存活时间
      * @param _p_init_velocity float 粒子的初始速度大小, 配合粒子初始方向使用
      * @param _p_init_direction vec3 粒子的初始方向, 内部会进行单位化
      * @param _p_acceleration vec3 粒子的加速度, 发射器的所有粒子共用该加速度
      * @param _p_delta_time uint64_t 粒子产生的时间间隔
      * @param _p_texture unsigned int 发射器中粒子使用的纹理, 由 glGenTextures 产生
      * @param _e_velocity float 发射器运动的初始速度
      * @param _e_direction vec3 发射器运动的初始初始方向
      * @param _e_acceleration vec3 发射器运动的加速度
      * @param _e_type EmitterType 发射器的类型: 线型/圆型/球型
      * @param ... 根据粒子发射器类型传递对应参数
      */
    void SetParticleEmitter(
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
    );

    // 启用一次性发射
    void EnableOneShoot();
    // 取消一次性发射
    void DisableOneShoot();

    /**
     *@brief 启用粒子颜色线性插值产生渐变效果, 颜色从start到end线性变化
     * 
     * @param start vec4 粒子初始颜色
     * @param end vec4 粒子消失颜色(一般可设置为 vec4(0.0f))
     */
    void EnableColorUpdater(glm::vec4 start, glm::vec4 end);
    /**
     *@brief 增加颜色变化的中间颜色
     * 
     * @param color 颜色
     * @param t 变为该颜色的时间点, 范围 [0, 1]
     */
    void AddMidColor(glm::vec4 color, float t);
    // 取消颜色插值
    void DisableColorUpdater();
    /**
     *@brief 启用粒子速度线性插值产生变速效果, 速度从start到end线性变化
     * 
     * @param start float 粒子初始速度
     * @param end float 粒子消失速度
     */
    void EnableVelocityUpdater(float start, float end);
    /**
     *@brief 添加速度变化的中间点, 实现对速度的多段线性插值
     * 
     * @param v 速度
     * @param t 变为该速度时间点, 范围 [0, 1]
     */
    void AddMidVelocity(float v, float t);
    // 取消速度插值
    void DisableVelocityUpdater();
    /**
     *@brief 启用粒子生命值线性插值产生同时消失效果, 生命值从start到end线性变化
     *
     * @param start int64_t 粒子发射器初始时产生的粒子的生命值
     * @param end int64_t 粒子发射器消失时产生的粒子的生命值
     */
    void EnableLifetimeUpdater(int64_t start, int64_t end);
    /**
     *@brief 添加产生粒子生命值变化的中间点, 实现对粒子发射器产生的粒子生命值的多段线性插值
     *
     * @param l int64_t 粒子生命值
     * @param t 粒子发射器产生该生命值粒子的时间点, 范围 [0, 1]
     */
    void AddMidLifetime(int64_t l, float t);
    // 取消速度插值
    void DisableLifetimeUpdater();

    /**
     *@brief 启用并设置粒子发射器径向加速度
     * 
     * @param _radial_acc float 径向加速度
     * @param _radial_axle vec3 径向加速度指向的中心轴
     */
    void EnableRadialAcc(float _radial_acc, glm::vec3 _radial_axle);
    // 取消粒子发射器径向加速度
    void DisableRadialAcc();

    /**
     *@brief 激活粒子存活时间误差
     *
     * @param _lifetime 粒子存活时间的误差百分比, 范围为 (0, 1)
     */
    void EnableLifetimeTolerance(float _lifetime);
    // 取消粒子存活时间误差
    void DisableLifetimeTolerance();

    // 使粒子发射器生效
    void Validate();
    // 使粒子发射器无效
    void Invalidate();
    // 返回粒子发射器是否有效
    bool isValid();
    // 返回粒子发射器生命值是否大于 0 
    bool isAlive();
    // 发射一个粒子
    void Emit();

    /**
     *@brief 更新所有粒子
     * 
     * @param deltatime 帧时间
     * @return true 代表该粒子发射器中还有粒子未消散, 需要继续被渲染
     * @return false 代表粒子发射器将不再产生粒子, 需要被删除
     */
    bool Update(uint64_t deltatime);

    /**
     *@brief 上传所有粒子的数据
     * 
     * @param vbo_buffer vbo缓冲
     * @return uint64_t 返会上传的粒子数量
     */
    uint64_t Upload(std::vector<float>& vbo_buffer);

    // 返回粒子发射器的中心
    glm::vec3 GetEmitterCenter();
    // 返回粒子发射器的颜色
    glm::vec3 GetEmitterColor();
    ~ParticleEmitter();
};

#endif