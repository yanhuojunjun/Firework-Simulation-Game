#ifndef EMITTER_H
#define EMITTER_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "glm/gtc/random.hpp"

#include <vector>
#include <memory>
#include <cstdarg>
#include <iostream>

// 粒子类
struct Particle {
    // 渲染所需参数
    glm::vec3 position;     // 粒子位置
    glm::vec4 color;        // 粒子颜色 RGBA
    float size;             // 粒子大小
    // 更新粒子所需参数
    glm::vec3 velocity;     // 粒子速度, 更新 position = velocity * delta_time
    int64_t lifetime;      // 粒子剩余存活时间
    int64_t totallifetime;  // 粒子总存活时间
    inline bool alive() { return lifetime > 0; }
};

// 发射器类型
enum EmitterType {
    Line,           // 直线型发射器 拥有散度参数
    Circle,         // 圆型发射器 拥有半径和方向类型(DirectionType)参数
    Sphere         // 球型发射器 拥有半径和方向类型(DirectionType)参数
};

// 圆型/球型发射器的初速度设置类型
enum DirectionType {
    Direct,         // 设置粒子初速度方向将朝向发射器的发射方向
    Outer           // 设置粒子初速度将朝向球心外发散(随机生成)
};

// 发射器接口类
// 用于设置粒子的参数
class Emitter {
public:
    /**********************
    *       接口          *
    **********************/

    /**
     *@brief 发射器的接口, 派生类必须重写此接口, 实现各自的功能
     *
     * @param particle 待修改的粒子
     */
    virtual void EmitParticle(Particle& particle) = 0;

    /**********************
    *       成员方法       *
    **********************/

    Emitter() = default;

    /**
     *@brief 设置发射器基本参数
     *
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
     */
    void SetEmitter(
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
        );
    /**
     *@brief 激活粒子存活时间误差
     *
     * @param _lifetime 粒子存活时间的误差百分比, 范围为 (0, 1)
     */
    void EnableLifetimeTolerance(float _lifetime_tolerance);
    // 取消粒子存活时间误差
    void DisableLifetimeTolerance();
    // 虚析构 保证析构可被正常调用
    virtual ~Emitter() = default;
public:

    /**********************
    *      必要参数        *
    **********************/

    glm::vec3 emitter_center;                // 粒子产生的中心位置, 发射器的中心
    glm::vec4 particle_color;                // 发射器产生的粒子的颜色
    float particle_size;                     // 粒子大小
    uint64_t particle_lifetime;              // 粒子生命周期
    float particle_initial_velocity;         // 粒子初速度
    glm::vec3 particle_initial_direction;    // 发射粒子的方向
    glm::vec3 particle_initial_acceleration; // 发射粒子的加速度
    uint64_t emission_delta_time;            // 发射粒子的时间间隔
    unsigned int texture;                    // 粒子使用的纹理
    glm::vec3 emitter_velocity;              // 发射器的速度
    glm::vec3 emitter_acceleration;          // 发射器的加速度
    EmitterType emitter_type;                // 发射器类型, 见 EmitterType 定义

    /**********************
    *      可选选项        *
    **********************/
    float emitter_radial_acceleration;       // 粒子发射器径向加速度
    float lifetime_tolerance;                // 粒子生命周期误差范围 相对于生命周期的百分比
};


/********************************************************
*                    发射器派生类                        *
********************************************************/

// 线型发射器
class LineEmitter :public Emitter {
public:
    LineEmitter(float _divergence = 0.0f);
    void EmitParticle(Particle& particle) override;
protected:
    float divergence;   // 散度
};

// 圆型发射器
class CircleEmitter :public Emitter {
public:
    CircleEmitter(float _radius = 1.0f, DirectionType d_type = DirectionType::Outer);
    void EmitParticle(Particle& particle) override;
protected:
    float radius;                   // 半径
    DirectionType direction_type;   // 方向类型
};

// 球型发射器
class SphereEmitter :public Emitter {
public:
    SphereEmitter(float _radius = 1.0f, DirectionType d_type = DirectionType::Outer);
    void EmitParticle(Particle& particle) override;
protected:
    float radius;                   // 半径
    DirectionType direction_type;   // 方向类型
};

#endif