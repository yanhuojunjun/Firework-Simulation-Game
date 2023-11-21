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
struct Particle
{
    // 渲染所需参数
    glm::vec3 position;     // 粒子位置
    glm::vec4 color;        // 粒子颜色, 透明度隐含在该选项中
    float size;             // 粒子大小
    // 更新粒子所需参数
    glm::vec3 velocity;     // 粒子速度, 更新时使用 velocity * delta_time
    int64_t lifetime;      // 粒子剩余存活时间
    int64_t totallifetime;  // 粒子总存活时间
    inline bool alive() { return lifetime > 0; }
};

enum EmitterType {
    Line,           // 直线
    Circle,         // 圆
    Sphere,         // 球
    Rectangle,      // 矩形
    Box             // 立方盒
};

enum DirectionType {
    Direct,         // 粒子朝向粒子发射器的方向
    Outer           // 粒子向球心外发散
};

class Emitter
{
public:
    /**********************
    *       接口          *
    **********************/

    /**
     *@brief 发射器需要实现的接口, 给定一个粒子, 按照不同类型发射器进行参数设置
     * 
     * @param particle 
     */
    virtual void EmitParticle(Particle& particle) = 0;

    /**********************
    *       成员方法       *
    **********************/

    /**
     *@brief 设置发射器参数
     * 
     * @param _center 粒子发射器中心, 粒子将从该位置附近产生
     * @param _color 粒子发射器发射的粒子颜色(只用单一颜色时, 可以激活线性插值忽略该变量)
     * @param _size 粒子的大小
     * @param lifetime 粒子生命周期, 可以激活随机生命周期, 在该值附近浮动
     * @param _v0 粒子发射的初速度
     * @param dire 粒子发射器的朝向
     * @param a 粒子发射器给予粒子的加速度
     * @param delta_time 粒子发射器发射粒子的时间间隔
     * @param _texture 粒子发射器使用的纹理
     * @param _type 粒子发射器的类型, 已实现直线, 圆, 球
     */
    void SetEmitter(glm::vec3 _center, glm::vec4 _color, float _size, int64_t lifetime, float _v0, glm::vec3 dire, glm::vec3 a, uint64_t delta_time, unsigned int _texture, EmitterType _type);
    /**
     *@brief 激活粒子生命值随机浮动, 浮动误差为生命值的百分比
     * 
     * @param _lifetime 粒子生命值浮动百分比, 必须小于1
     */
    void EnableRandom(float _lifetime);
    /**
     *@brief 取消激活粒子生命值浮动
     * 
     */
    void DisableRandom();
public:
    
    /**********************
    *       选项          *
    **********************/
    
    glm::vec3 emitter_center;       // 粒子发射器的中心
    glm::vec4 particle_color;       // 发射粒子的颜色
    float particle_size;            // 粒子大小
    uint64_t particle_lifetime;     // 粒子生命周期
    float initial_velocity;         // 粒子初速度
    glm::vec3 emission_direction;   // 发射粒子的方向
    glm::vec3 acceleration;         // 发射粒子的加速度
    uint64_t emission_delta_time;   // 发射粒子的时间间隔
    unsigned int texture;           // 粒子使用的纹理
    EmitterType emitter_type;       // 发射器类型, 见 EmitterType 定义

    float lifetime_random;          // 粒子生命周期随机度 相对于生命周期
};

class LineEmitter :public Emitter {
public:
    void EmitParticle(Particle& particle) override;
};

class CircleEmitter :public Emitter {
public:
    CircleEmitter(float _radius = 1.0f, DirectionType d_type = DirectionType::Outer);
    void EmitParticle(Particle& particle) override;
protected:
    float radius;
    DirectionType direction_type;
};

class SphereEmitter :public Emitter {
public:
    SphereEmitter(float _radius = 1.0f, DirectionType d_type = DirectionType::Outer);
    void EmitParticle(Particle& particle) override;
protected:
    float radius;
    DirectionType direction_type;
};

#endif