#include "Animation_0.h"

Animation_0::Animation_0(std::shared_ptr<Pipe_Firework_Manager> _manager) :Animation(_manager) {}
void Animation_0::Build() {
    Animation_Frame new_frame;
    //*************************************************************** 空白
    new_frame.func = frame_empty;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 1000;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 开始的球形 -1000-
    new_frame.func = frame_3;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 2100;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** (-10, -40) 向右扫开始 -3100-
    new_frame.func = frame_4;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** -3240-
    new_frame.func = frame_5;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** -3380-
    new_frame.func = frame_6;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** -3520-
    new_frame.func = frame_7;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** -3660-
    new_frame.func = frame_8;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** -3800-
    new_frame.func = frame_9;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** (-10, -40) 向右扫结束 -3940-
    new_frame.func = frame_10;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** (10, -40) 向右扫开始 -4080-
    new_frame.func = frame_17;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** -4220-
    new_frame.func = frame_16;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** -4360-
    new_frame.func = frame_15;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** -4500-
    new_frame.func = frame_14;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** -4640-
    new_frame.func = frame_13;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** -4780-
    new_frame.func = frame_12;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** (10, -40) 向右扫结束 -4920-
    new_frame.func = frame_11;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 140;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 扇形 -5060-
    new_frame.func = frame_1;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 1150;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 一排 球 ->8210 爆炸 -6210-
    new_frame.func = frame_0;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 500;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 扇形 -6710-
    new_frame.func = frame_1;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 1000;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机一排 蓝色球 -7710-
    new_frame.func = frame_18;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 2640;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色,位置,生命值 球 12350 爆炸 -10350-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 650;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色,位置,生命值 球 13000 爆炸 -11000-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 690;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色,位置,生命值 球 13690 爆炸 -11690-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 590;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色,位置,生命值 球 14280 爆炸 -12280-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 636;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色,位置,生命值 球 14916 爆炸 -12916-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 930;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色,位置,生命值 球 15846 爆炸 -13846-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 988;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色,位置,生命值 球 16834 爆炸 -14834-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 626;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色,位置,生命值 球 17460 爆炸 -15460-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 2000;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向右 -17460-
    new_frame.func = frame_20;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 610;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向右 -18070-
    new_frame.func = frame_21;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 610;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向右 -18680-
    new_frame.func = frame_22;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 610;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向右 -19290-
    new_frame.func = frame_23;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 610;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向左 -19900-
    new_frame.func = frame_24;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 610;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向左 -20510-
    new_frame.func = frame_25;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 610;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向左 -21120-
    new_frame.func = frame_26;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 179;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 一排 随机颜色 球 23299 爆炸 -21299-
    new_frame.func = frame_0;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 431;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向左 -21730-
    new_frame.func = frame_27;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 1000;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -22730-
    new_frame.func = frame_28;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 200;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -22930-
    new_frame.func = frame_29;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 200;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -23130-
    new_frame.func = frame_30;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 200;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -23330-
    new_frame.func = frame_31;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 68;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 球+中心花 25398 爆炸 -23398-
    new_frame.func = frame_37;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 132;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -23530-
    new_frame.func = frame_32;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 200;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -23730-
    new_frame.func = frame_33;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 200;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -23930-
    new_frame.func = frame_34;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 200;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -24130-
    new_frame.func = frame_35;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 1268;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);

    //*************************************************************** 扇形 -25398- 
    new_frame.func = frame_1;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 1000;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 二阶 流星-球 28398 爆炸 -26398-
    new_frame.func = frame_36;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 5023;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 33421 爆炸 -31421-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 579;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 34000 爆炸 -32000-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 632;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 34632 爆炸 -32632-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 355;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 34897 爆炸 -32987-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 253;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 35240 爆炸 -33240-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 640;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 35880 爆炸 -33880-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 631;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 36511 爆炸 -34511-
    new_frame.func = frame_38;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 620;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 37131 爆炸 -35131-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 621;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 37752 爆炸 -35752-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 620;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 38372 爆炸 -36372-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 643;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 39015 爆炸 -37015-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 604;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 39619 爆炸 -37619-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 679;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 40298 爆炸 -38298-
    new_frame.func = frame_38;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 605;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 40903 爆炸 -38903-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 629;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 41532 爆炸 -39532-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 87;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向右 -39619-
    new_frame.func = frame_20;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 0;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -39619-
    new_frame.func = frame_28;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 0;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -39619-
    new_frame.func = frame_32;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 0;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向左 -39619-
    new_frame.func = frame_24;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 100;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向右 -39719-
    new_frame.func = frame_21;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 0;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -39719-
    new_frame.func = frame_29;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 0;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -39719-
    new_frame.func = frame_33;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 0;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向左 -39719-
    new_frame.func = frame_25;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 100;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向右 -39819-
    new_frame.func = frame_22;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 0;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -39819-
    new_frame.func = frame_30;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 0;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -39819-
    new_frame.func = frame_34;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 0;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向左 -39819-
    new_frame.func = frame_26;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 100;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向右 -39919-
    new_frame.func = frame_23;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 0;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -39919-
    new_frame.func = frame_31;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 0;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 团 -39919-
    new_frame.func = frame_35;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 0;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机颜色 斜直线 向左 -39919-
    new_frame.func = frame_27;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 210;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 42129 爆炸 -40129-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 626;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 42755 爆炸 -40755-
    new_frame.func = frame_38;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 655;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 43410 爆炸 -41410-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 590;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 44000 爆炸 -42000-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 633;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 44633 爆炸 -42633-
    new_frame.func = frame_38;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 626;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 45259 爆炸 -43259-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 612;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 45871 爆炸 -43871-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 640;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);
    //*************************************************************** 随机 球 46511 爆炸 -44511-
    new_frame.func = frame_19;
#ifdef SDL2_LIB
    new_frame.total_sleep_time.sdl_sleep_time = 1000;
#else
    new_frame.total_sleep_time.glfw_sleep_time = 5000.0;
#endif
    frames.push_back(new_frame);

}
Animation_0::~Animation_0() {}

// 空白帧
void frame_empty(std::shared_ptr<Pipe_Firework_Manager>) {}

// 一排 6 个 球形 普通 2 秒
void frame_0(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    for (float pos_x = -20.0f; pos_x <= 20.0f; pos_x += 8.0f) {
        _manager->Register_Firework(
            1,                                  // 烟花种类
            glm::linearRand(8.0f, 12.0f),                              // 初始速度
            glm::vec3(pos_x, 0.0f, -60.0f),     // 初始位置
            glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
            firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
            2000,                               // 爆炸倒计时/粒子发射器生命值
            0                                   // 上升过程种类
        );
    }
}
// 扇形 直线 2 秒
void frame_1(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    for (float dire_x = 60.0f; dire_x <= 120.0f; dire_x += 6.0f) {
        _manager->Register_Firework(
            3,                                  // 烟花种类
            8.0f,                              // 初始速度
            glm::vec3(0.0f, 0.0f, -40.0f),        // 初始位置
            glm::vec3(glm::cos(glm::radians(dire_x)), glm::sin(glm::radians(dire_x)), 0.0f),        // 初始方向
            glm::vec4(1.0f, 0.5f, 0.5f, 1.0f),  // 初始颜色
            2000,                               // 爆炸倒计时/粒子发射器生命值
            1                                   // 上升过程种类
        );
    }

}
// 球形 线 2 秒
void frame_2(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    for (float pos_x = -30.0f; pos_x <= 30.0f; pos_x += 20.0f) {
        _manager->Register_Firework(
            4,                                  // 烟花种类
            10.0f,                              // 初始速度
            glm::vec3(pos_x, 0.0f, -60.0f),     // 初始位置
            glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
            glm::vec4(1.0f, 0.5f, 0.5f, 1.0f),  // 初始颜色
            2000,                               // 爆炸倒计时/粒子发射器生命值
            0                                   // 上升过程种类
        );
    }
}
// 一个 球形 红色 (0, -60) 飞行 2 秒后爆炸
void frame_3(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        1,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(0.0f, 0.0f, -60.0f),     // 初始位置
        glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.2f, 0.2f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        0                                   // 上升过程种类
    );

}
// 直线 橙色 (-10, -60) 与x正方向夹角 120 度 2 秒
void frame_4(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(-10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(120.0f)), glm::sin(glm::radians(120.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 直线 橙色 (-10, -60) 与x正方向夹角 110 度 2 秒
void frame_5(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(-10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(110.0f)), glm::sin(glm::radians(110.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 直线 橙色 (-10, -60) 与x正方向夹角 100 度 2 秒
void frame_6(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(-10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(100.0f)), glm::sin(glm::radians(100.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 直线 橙色 (-10, -60) 与x正方向夹角 90 度 2 秒
void frame_7(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(-10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(90.0f)), glm::sin(glm::radians(90.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 直线 橙色 (-10, -60) 与x正方向夹角 80 度 2 秒
void frame_8(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(-10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(80.0f)), glm::sin(glm::radians(80.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 直线 橙色 (-10, -60) 与x正方向夹角 70 度 2 秒
void frame_9(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(-10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(70.0f)), glm::sin(glm::radians(70.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 直线 橙色 (-10, -60) 与x正方向夹角 60 度 2 秒
void frame_10(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(-10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(60.0f)), glm::sin(glm::radians(60.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 直线 橙色 (10, -60) 与x正方向夹角 60 度 2 秒
void frame_11(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(60.0f)), glm::sin(glm::radians(60.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 直线 橙色 (10, -60) 与x正方向夹角 70 度 2 秒
void frame_12(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(70.0f)), glm::sin(glm::radians(70.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 直线 橙色 (10, -60) 与x正方向夹角 80 度 2 秒
void frame_13(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(80.0f)), glm::sin(glm::radians(80.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 直线 橙色 (10, -60) 与x正方向夹角 90 度 2 秒
void frame_14(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(90.0f)), glm::sin(glm::radians(90.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 直线 橙色 (10, -60) 与x正方向夹角 100 度 2 秒
void frame_15(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(100.0f)), glm::sin(glm::radians(100.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 直线 橙色 (10, -60) 与x正方向夹角 110 度 2 秒
void frame_16(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(110.0f)), glm::sin(glm::radians(110.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 直线 橙色 (10, -60) 与x正方向夹角 120 度 2 秒
void frame_17(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(10.0f, 0.0f, -40.0f),     // 初始位置
        glm::vec3(glm::cos(glm::radians(120.0f)), glm::sin(glm::radians(120.0f)), 0.0f),        // 初始方向
        glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 普通球形 蓝色 随机数量位置 数量 2 秒
void frame_18(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    int num = glm::linearRand(1, 7);
    for (int i = 0;i < num;i++) {
        _manager->Register_Firework(
            1,                                  // 烟花种类
            glm::linearRand(8.0f, 12.0f),                              // 初始速度
            glm::vec3(glm::linearRand(-20.0f, 20.0f), 0.0f, -40.0f),        // 初始位置
            glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
            glm::vec4(64.0f / 255.0f, 186.0f / 255.0f, 238.0f / 255.0f, 1.0f),  // 初始颜色
            2000.0f,                               // 爆炸倒计时/粒子发射器生命值
            1                                   // 上升过程种类
        );
    }
}
// 普通球形 预定的随机颜色 随机位置 随机初速度 一个 2 秒爆炸
void frame_19(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        1,                                  // 烟花种类
        glm::linearRand(8.0f, 12.0f),                              // 初始速度
        glm::vec3(glm::linearRand(-20.0f, 20.0f), 0.0f, glm::linearRand(-60.0f, -40.0f)),        // 初始位置
        glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000.0f,                               // 爆炸倒计时/粒子发射器生命值
        0                                   // 上升过程种类
    );
}
// 烟花线 向右偏 (-10, -40) 预定的随机颜色 2 秒
void frame_20(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(-10.0f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 烟花线 向右偏 (-7.5, -40) 预定的随机颜色 2 秒
void frame_21(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(-7.5f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 烟花线 向右偏 (-5, -40) 预定的随机颜色 2 秒
void frame_22(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(-5.0f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 烟花线 向右偏 (-2.5, -40) 预定的随机颜色 2 秒
void frame_23(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(-2.5f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}

// 烟花线 向左偏 (10, -40) 预定的随机颜色 2 秒
void frame_24(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(10.0f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(-1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 烟花线 向左偏 (7.5, -40) 预定的随机颜色 2 秒
void frame_25(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(7.5f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(-1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 烟花线 向左偏 (5, -40) 预定的随机颜色 2 秒
void frame_26(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(5.0f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(-1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}
// 烟花线 向左偏 (2.5, -40) 预定的随机颜色 2 秒
void frame_27(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        10.0f,                              // 初始速度
        glm::vec3(2.5f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(-1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        1                                   // 上升过程种类
    );
}

// 烟花团 向右偏 (-10, -40) 预定的随机颜色 2 秒
void frame_28(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(-10.0f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        2                                   // 上升过程种类
    );
}
// 烟花团 向右偏 (-7.5, -40) 预定的随机颜色 2 秒
void frame_29(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(-7.5f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        2                                   // 上升过程种类
    );
}
// 烟花团 向右偏 (-5, -40) 预定的随机颜色 2 秒
void frame_30(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(-5.0f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        2                                   // 上升过程种类
    );
}
// 烟花团 向右偏 (-2.5, -40) 预定的随机颜色 2 秒
void frame_31(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(-2.5f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        2                                   // 上升过程种类
    );
}

// 烟花团 向左偏 (10, -40) 预定的随机颜色 2 秒
void frame_32(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(10.0f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(-1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        2                                   // 上升过程种类
    );
}
// 烟花团 向左偏 (7.5, -40) 预定的随机颜色 2 秒
void frame_33(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(7.5f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(-1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        2                                   // 上升过程种类
    );
}
// 烟花团 向左偏 (5, -40) 预定的随机颜色 2 秒
void frame_34(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(5.0f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(-1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        2                                   // 上升过程种类
    );
}
// 烟花团 向左偏 (2.5, -40) 预定的随机颜色 2 秒
void frame_35(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        3,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(2.5f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(-1.0f, 2.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        2                                   // 上升过程种类
    );
}
// 烟花团 向左偏 (2.5, -40) 预定的随机颜色 2 秒
void frame_36(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        0,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(0.0f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        0                                   // 上升过程种类
    );
}
// 两层球+中心花 对称分布 0 号上升类型
void frame_37(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        2,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(10.0f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        0                                   // 上升过程种类
    );
    _manager->Register_Firework(
        2,                                  // 烟花种类
        8.0f,                              // 初始速度
        glm::vec3(-10.0f, 0.0f, -40.0f),        // 初始位置
        glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        0                                   // 上升过程种类
    );
}
void frame_38(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    _manager->Register_Firework(
        2,                                  // 烟花种类
        glm::linearRand(8.0f, 12.0f),                              // 初始速度
        glm::vec3(glm::linearRand(-20.0f, 20.0f), 0.0f, glm::linearRand(-60.0f, -40.0f)),        // 初始位置
        glm::vec3(0.0f, 1.0f, 0.0f),        // 初始方向
        firework_color[glm::linearRand(0, firework_color_num)],  // 初始颜色
        2000,                               // 爆炸倒计时/粒子发射器生命值
        0                                   // 上升过程种类
    );
}
void frame_39(std::shared_ptr<Pipe_Firework_Manager> _manager) {
    
}