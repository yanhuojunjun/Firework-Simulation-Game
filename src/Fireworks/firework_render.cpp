#include "firework_render.h"

firework_render::firework_render(ICamera* cam) 
    :shader("Shaders/particle.vs", "Shaders/particle.fs"){

    camera = cam;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("img/particle_demo.png", &width, &height, &nrChannels, 0); // 载入纹理图片
    glGenTextures(1, &texture); // 创建纹理
    glActiveTexture(GL_TEXTURE0); // 激活纹理单元
    glBindTexture(GL_TEXTURE_2D, texture);// 绑定纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // 生成纹理
    glGenerateMipmap(GL_TEXTURE_2D); // 生成多级渐远纹理
    stbi_image_free(data); // 生成纹理后释放图片数据
}

void firework_render::add_group(particle_group *new_group) {
    particle_groups.push_back(new_group);
}

void firework_render::update_and_collect(int64_t millisecond_passby) {
    //遍历paticle_groups，更新每个粒子群，若死亡则自动删除，upload粒子群数据
    vbo_buffer.clear();
    for (auto it = particle_groups.begin();it != particle_groups.end();) {
        if ((*it)->update(millisecond_passby)){
            (*it)->upload(vbo_buffer);
            it++;
        }
        else particle_groups.erase(it);  
    }
}

void firework_render::render() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDisable(GL_DEPTH);

    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, vbo_buffer.size() * sizeof(float), vbo_buffer.data(), GL_DYNAMIC_DRAW);//动态更新VBO，会自动改变大小
    shader.use();
    shader.setMat4("view", camera->GetViewMatrix());
    shader.setMat4("projection", glm::perspective(glm::radians(camera->Zoom), 800.0f / 600.0f, 0.1f, 100.0f));
    shader.setInt("texture1", 0);
    glDrawArrays(GL_POINTS, 0, vbo_buffer.size()/7);//绘制VBO中的所有点
    
    glEnable(GL_DEPTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
firework_render::~firework_render() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.deleteShader();
}