#ifndef CIRCLE_FIREWORK_H
#define CIRCLE_FIREWORK_H

#include "glad.h"
#include "SDL.h"
#include "stb_image.h"

#include "particle.h"

#include "Camera_SDL.h"
#include "Shader.h"
#include <cmath>
#include <vector>
#include <iostream>



class circle_firework :particle_group {
protected:

    Shader* shader;
    ICamera* camera;
    glm::vec3 position; // 起始地点
    glm::vec4 color; // 
    uint64_t boom_millisecond;
    bool boom_flag;
    
    unsigned int texture;
    unsigned int VAO, VBO, EBO;
public:
    circle_firework(Shader* shd, ICamera* cam, glm::vec3 pos, glm::vec4 col, uint32_t max_px);
    void update(int64_t millisecond_passby);
    ~circle_firework();
protected:
    void render();
};

#endif