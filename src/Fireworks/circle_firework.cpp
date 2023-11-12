#include "circle_firework.h"
circle_firework::circle_firework(Shader* shd, ICamera* cam, glm::vec3 pos, glm::vec4 col, uint32_t max_px) {
    init(max_px, particle(pos, glm::vec3(0.0f, 5.0f, 0.0f), col, 20000));
    boom_millisecond = 10000;
    boom_flag = true;
    shader = shd;
    camera = cam;
    position = pos;
    color = col;
    float vertices[] = {
        //     ---- 位置 ----     - 纹理坐标 -
             0.1f,  0.1f, 0.0f,   1.0f, 1.0f,   // 右上
             0.1f, -0.1f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.1f, -0.1f, 0.0f,   0.0f, 0.0f,   // 左下
            -0.1f,  0.1f, 0.0f,   0.0f, 1.0f    // 左上
    };
    // 定义顶点索引
    unsigned int indices[] = {
        // 注意索引从0开始! 
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    // 复制顶点数据
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //std::cout << "vert size: " << sizeof(vertices)<<" indx size: " << sizeof(indices)<<" float: " <<sizeof(float)<< std::endl;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 载入纹理
    // 载入图像
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("img/particle_demo.png", &width, &height, &nrChannels, 0);
    // 创建纹理
    glGenTextures(1, &texture);
    // 激活纹理单元
    glActiveTexture(GL_TEXTURE0);
    // 绑定纹理
    glBindTexture(GL_TEXTURE_2D, texture);
    // 根据图像数据生成纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    // 生成多级渐远纹理
    glGenerateMipmap(GL_TEXTURE_2D);
    // 生成纹理后释放图片数据
    stbi_image_free(data);
}

void circle_firework::update(int64_t millisecond_passby) {
    birth_millisecond += millisecond_passby;
    if (boom_flag && boom_millisecond < birth_millisecond) {
        particle_generator::circle_surround((particle_group*)this, particles[0], 10, 1);
        boom_flag = false;
    }
    for (auto it = particles.begin();it != particles.end();it++) {
        if (it->update(millisecond_passby)) {
            PathGenerator::gravity(it->position, it->velocity, millisecond_passby, -0.5);
        }
    }
    render();
}

void circle_firework::render() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    shader->use();
    shader->setMat4("view", camera->GetViewMatrix());
    shader->setMat4("projection", glm::perspective(glm::radians(camera->Zoom), 800.0f / 600.0f, 0.1f, 100.0f));
    //shader->setMat4("model", glm::mat4(1.0f));
    shader->setInt("texture1", 0);
    glBindVertexArray(VAO);
    for (auto it = particles.begin();it != particles.end();it++) {
        if (it->alive()) {
            shader->setVec4("aColor", it->color);
            shader->setMat4("model", glm::translate(glm::mat4(1.0f), it->position));
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
circle_firework::~circle_firework() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}