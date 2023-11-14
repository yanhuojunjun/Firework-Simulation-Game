#ifndef CIRCLE_FIREWORK_H
#define CIRCLE_FIREWORK_H

#include "glad.h"
#include "SDL.h"
#include "stb_image.h"

#include "particle.h"
#include "particle_render.h"

#include "Camera_SDL.h"
#include "Shader.h"
#include <cmath>
#include <vector>
#include <iostream>



class circle_firework :particle_group {
protected:

    Shader shader;
    ICamera* camera;
    glm::vec3 position; // 起始地点
    glm::vec4 color; // 
    uint64_t boom_millisecond;
    int boom_count;

    std::vector<glm::vec4> buf_position, buf_color;
    
    unsigned int texture;
    unsigned int VAO;
    unsigned int VBO_position, VBO_color;
public:
    circle_firework(ICamera* cam, glm::vec3 pos, glm::vec4 col, uint32_t max_px);
    void update(int64_t millisecond_passby);
    ~circle_firework();
protected:
    void render();
};

#endif