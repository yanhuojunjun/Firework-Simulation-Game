#ifndef BLOOM_H
#define BLOOM_H

#include "glad.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Shader.h"


class bloom //实现辉光效果
{
public:
    //创建帧缓冲hdrFBO（两个颜色附件，一个存储所有内容，一个存储烟花），两个帧缓冲pingpangFBO（每一个含有一个颜色附件，用来交替进行gauss模糊）
    //创建screen_shader（用来绘制屏幕），gauss_shader（用来进行gauss模糊）两个着色器
    //创建用来将帧缓冲绘制到帧缓冲的VBO，VAO，
    bloom(bool _bloom,float _exposure,int width,int height); 
    void draw_world(); //准备绘制世界+烟花
    void draw_firework(); //准备绘制烟花
    void draw_gauss(); //进行高斯模糊
    void draw_screen(); //将帧缓冲内容复制到屏幕
    ~bloom(); //删除帧缓冲，VAO,VBO

    unsigned int hdrFBO; //帧缓冲
    unsigned int colorBuffers[2], rboDepth; //两个颜色附件,一个深度缓冲
    unsigned int world_attachment[1]; //绑定一个颜色附件
    unsigned int firework_attachment[1]; //绑定另一个颜色附件
    unsigned int pingpongFBO[2];//帧缓冲
    unsigned int pingpongColorbuffers[2];//两个颜色附件
    Shader screen_shader, gauss_shader, draw_light_shader; //着色器
    unsigned int quadVAO, quadVBO;
    bool use_bloom; // 选择是否爆炸
    float exposure; // 曝光度
    bool horizontal, first_iteration;//用于高斯模糊
    int WIN_WIDTH, WIN_HEIGHT;
};


#endif