#ifndef ANIMATION_0_H
#define ANIMATION_0_H

#include "Animation.h"

static glm::vec4 firework_color[] = {
    glm::vec4(64.0f / 255.0f, 186.0f / 255.0f, 238.0f / 255.0f, 1.0f),      // 0 蓝色
    glm::vec4(139.0f / 255.0f, 63.0f / 255.0f, 238.0f / 255.0f, 1.0f),      // 1 紫色
    glm::vec4(238.0f / 255.0f, 63.0f / 255.0f, 104.0f / 255.0f, 1.0f),      // 2 洋红色
    glm::vec4(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f),         // 3 红色
    glm::vec4(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 1.0f),       // 4 黄色
    glm::vec4(13.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 1.0f),        // 5 绿色
    glm::vec4(0.0f / 255.0f, 255.0f / 255.0f, 187.0f / 255.0f, 1.0f),       // 6 青色
    glm::vec4(255.0f / 255.0f, 149.0f / 255.0f, 0.0f / 255.0f, 1.0f)        // 7 橙色 
};

static int32_t firework_color_num = 7;

class Animation_0 :public Animation {
public:
    Animation_0(std::shared_ptr<Pipe_Firework_Manager> _manager);
    void Build() override;
    ~Animation_0();
};

void frame_empty(std::shared_ptr<Pipe_Firework_Manager>);

void frame_0(std::shared_ptr<Pipe_Firework_Manager>);
void frame_1(std::shared_ptr<Pipe_Firework_Manager>);
void frame_2(std::shared_ptr<Pipe_Firework_Manager>);
void frame_3(std::shared_ptr<Pipe_Firework_Manager>);
void frame_4(std::shared_ptr<Pipe_Firework_Manager>);
void frame_5(std::shared_ptr<Pipe_Firework_Manager>);
void frame_6(std::shared_ptr<Pipe_Firework_Manager>);
void frame_7(std::shared_ptr<Pipe_Firework_Manager>);
void frame_8(std::shared_ptr<Pipe_Firework_Manager>);
void frame_9(std::shared_ptr<Pipe_Firework_Manager>);
void frame_10(std::shared_ptr<Pipe_Firework_Manager>);
void frame_11(std::shared_ptr<Pipe_Firework_Manager>);
void frame_12(std::shared_ptr<Pipe_Firework_Manager>);
void frame_13(std::shared_ptr<Pipe_Firework_Manager>);
void frame_14(std::shared_ptr<Pipe_Firework_Manager>);
void frame_15(std::shared_ptr<Pipe_Firework_Manager>);
void frame_16(std::shared_ptr<Pipe_Firework_Manager>);
void frame_17(std::shared_ptr<Pipe_Firework_Manager>);
void frame_18(std::shared_ptr<Pipe_Firework_Manager>);
void frame_19(std::shared_ptr<Pipe_Firework_Manager>);
void frame_20(std::shared_ptr<Pipe_Firework_Manager>);
void frame_21(std::shared_ptr<Pipe_Firework_Manager>);
void frame_22(std::shared_ptr<Pipe_Firework_Manager>);
void frame_23(std::shared_ptr<Pipe_Firework_Manager>);
void frame_24(std::shared_ptr<Pipe_Firework_Manager>);
void frame_25(std::shared_ptr<Pipe_Firework_Manager>);
void frame_26(std::shared_ptr<Pipe_Firework_Manager>);
void frame_27(std::shared_ptr<Pipe_Firework_Manager>);
void frame_28(std::shared_ptr<Pipe_Firework_Manager>);
void frame_29(std::shared_ptr<Pipe_Firework_Manager>);
void frame_30(std::shared_ptr<Pipe_Firework_Manager>);
void frame_31(std::shared_ptr<Pipe_Firework_Manager>);
void frame_32(std::shared_ptr<Pipe_Firework_Manager>);
void frame_33(std::shared_ptr<Pipe_Firework_Manager>);
void frame_34(std::shared_ptr<Pipe_Firework_Manager>);
void frame_35(std::shared_ptr<Pipe_Firework_Manager>);
void frame_36(std::shared_ptr<Pipe_Firework_Manager>);
void frame_37(std::shared_ptr<Pipe_Firework_Manager>);
void frame_38(std::shared_ptr<Pipe_Firework_Manager>);
void frame_39(std::shared_ptr<Pipe_Firework_Manager>);
#endif