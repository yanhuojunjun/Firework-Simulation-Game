#include "circle_firework.h"
circle_firework::circle_firework(ICamera* cam, glm::vec3 pos, glm::vec4 col, uint32_t max_px)
    :shader("Shaders/particle.vs", "Shaders/particle.fs") {
    init(max_px, particle(pos, glm::vec3(0.0f, 5.0f, 0.0f), col, 20000));
    upload(buf_position, particle_attr::P_POSITON);
    upload(buf_color, particle_attr::P_COLOR);
    boom_millisecond = 1000;
    boom_count = 5;
    camera = cam;
    position = pos;
    color = col;
    // 复制顶点数据
    glGenBuffers(1, &VBO_position);
    glGenBuffers(1, &VBO_color);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    // 创建缓冲时预留足够大小
    glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
    glBufferData(GL_ARRAY_BUFFER, max_px * sizeof(glm::vec4), buf_position.data(), GL_STREAM_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    glBufferData(GL_ARRAY_BUFFER, max_px * sizeof(glm::vec4), buf_color.data(), GL_STREAM_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(1);

    //std::cout << "buf_position size: " << buf_position.size() * sizeof(glm::vec4) << " glm::vec4 size: " << sizeof(glm::vec4) << " float: " << sizeof(float) << std::endl;
    

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
    // 更新粒子
    if (boom_count > 0 && boom_millisecond <= birth_millisecond && boom_millisecond >= birth_millisecond-millisecond_passby) {
        particle_generator::circle_surround((particle_group*)this, particles[0], 10, 1);
        std::cout << particles.size() << std::endl;
        --boom_count;
        boom_millisecond += 1000;
    }
    for (auto it = particles.begin();it != particles.end();it++) {
        it->update(millisecond_passby);
    }
    // 上传数据
    buf_position.clear();
    buf_color.clear();
    upload(buf_position, particle_attr::P_POSITON);
    upload(buf_color, particle_attr::P_COLOR);
    //std::cout << "buf size: " << buf_position.size() << " , color size: " << buf_color.size() << std::endl;
    
    // 传到GPU缓冲
    glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
    glBufferSubData(GL_ARRAY_BUFFER, 0, buf_position.size() * sizeof(glm::vec4), buf_position.data());
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    glBufferSubData(GL_ARRAY_BUFFER, 0, buf_color.size() * sizeof(glm::vec4), buf_color.data());
    //std::cout << "GPU size: " << buf_position.size() * sizeof(glm::vec4) << std::endl;
    // 渲染
    render();
}

void circle_firework::render() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glBindVertexArray(VAO);
    shader.use();
    shader.setMat4("view", camera->GetViewMatrix());
    shader.setMat4("projection", glm::perspective(glm::radians(camera->Zoom), 800.0f / 600.0f, 0.1f, 100.0f));
    //shader->setMat4("model", glm::mat4(1.0f));
    shader.setInt("texture1", 0);
    glDrawArrays(GL_POINTS, 0, buf_position.size());
    //std::cout << "draw number " << buf_position.size() << std::endl;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
circle_firework::~circle_firework() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO_position);
    glDeleteBuffers(1, &VBO_color);
}