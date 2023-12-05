#ifndef FIREBOX_HPP
#define FIREBOX_HPP

#include "ICamera.h"
#include "Shader.h"
#include <vector>

class Firebox {
    ICamera* mcamera;
    Shader* ourShader;
    float vertices[6 * 8 * 6];
    float z;
    std::vector<glm::vec3> cubePositions;
    std::vector<glm::vec3> fireboxPositions;
    unsigned int VBO, VAO;
    unsigned int texture1, texture2, texture3, texture4, texture5, texture6;
public:
    bool life;

public:
    Firebox(float z, ICamera* mcamera) : z(z + 1), mcamera(mcamera) {
        life = false;
        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);

        // build and compile our shader zprogram
        // ------------------------------------
        ourShader = new Shader("Shaders/background.vs", "Shaders/background.fs");

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices_t[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };
        float size = 0.01f;
        for (int i = 0; i < 36; i++) {
            vertices_t[i * 8 + 0] *= size;
            vertices_t[i * 8 + 1] *= size;
            vertices_t[i * 8 + 2] *= size;
        }
        memcpy(vertices, vertices_t, sizeof(vertices_t));
        // world space positions of our cubes        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //浣嶇疆
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //娉曞悜閲?
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //绾圭悊鍧愭爣
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // texture 1
        // ---------
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char* data = stbi_load("img/pumpkin_face_on.png", &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        // texture 2
        // ---------
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        data = stbi_load("img/pumpkin_face_off.png", &width, &height, &nrChannels, 0);
        if (data) {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        // texture 3
        // ---------
        glGenTextures(1, &texture3);
        glBindTexture(GL_TEXTURE_2D, texture3);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        data = stbi_load("img/pumpkin_top.png", &width, &height, &nrChannels, 0);
        if (data) {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        // texture 4
        // ---------
        glGenTextures(1, &texture4);
        glBindTexture(GL_TEXTURE_2D, texture4);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        data = stbi_load("img/red.jpg", &width, &height, &nrChannels, 0);
        if (data) {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        // texture 5
        // ---------
        glGenTextures(1, &texture5);
        glBindTexture(GL_TEXTURE_2D, texture5);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        data = stbi_load("img/yellow.jpg", &width, &height, &nrChannels, 0);
        if (data) {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        // texture 6
       // ---------
        glGenTextures(1, &texture6);
        glBindTexture(GL_TEXTURE_2D, texture6);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        data = stbi_load("img/brown.jpg", &width, &height, &nrChannels, 0);
        if (data) {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);


        ourShader->use();
        ourShader->setInt("texture1", 0);

        for (int i = 1; i < 15; i++) {
            cubePositions.push_back(glm::vec3(-2.0f, 1.0f * i, 0.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
            cubePositions.push_back(glm::vec3(-2.0f, 1.0f * i, 1.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
            cubePositions.push_back(glm::vec3(-1.0, 1.0f * i, 2.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
            cubePositions.push_back(glm::vec3(-1.0f, 1.0f * i, -1.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
            cubePositions.push_back(glm::vec3(0.0f, 1.0f * i, -2.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
            cubePositions.push_back(glm::vec3(1.0f, 1.0f * i, -2.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
            cubePositions.push_back(glm::vec3(0.0f, 1.0f * i, 3.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
            cubePositions.push_back(glm::vec3(1.0f, 1.0f * i, 3.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
            cubePositions.push_back(glm::vec3(2.0f, 1.0f * i, -1.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
            cubePositions.push_back(glm::vec3(2.0f, 1.0f * i, 2.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
            cubePositions.push_back(glm::vec3(3.0f, 1.0f * i, 0.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
            cubePositions.push_back(glm::vec3(3.0f, 1.0f * i, 1.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        }
        cubePositions.push_back(glm::vec3(2.0f, 1.0f * 14, 0.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(2.0f, 1.0f * 14, 1.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(1.0f, 1.0f * 14, 0.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(1.0f, 1.0f * 14, 1.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(1.0f, 1.0f * 14, -1.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(1.0f, 1.0f * 14, 2.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(0.0f, 1.0f * 14, 0.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(0.0f, 1.0f * 14, 1.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(0.0f, 1.0f * 14, -1.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(0.0f, 1.0f * 14, 2.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(-1.0f, 1.0f * 14, 0.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(-1.0f, 1.0f * 14, 1.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));

        cubePositions.push_back(glm::vec3(0.0f, 1.0f * 15, 0.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(0.0f, 1.0f * 16, 0.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(1.0f, 1.0f * 17, 1.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(1.0f, 1.0f * 18, 1.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));
        cubePositions.push_back(glm::vec3(0.0f, 1.0f * 19, 0.0f) * size + glm::vec3(0.0f, z - z * size + 0.5f, 0.0f));

        // for(int i = 0; i < 5; i++) {
        //     for(int j = 0; j < 5; j++) {
        //         fireboxPositions.push_back(glm::vec3(0.25f*i, 0.0f, 0.25f*j));
        //     }
        // }

    }

    ~Firebox() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        delete(ourShader);
    }

    void clear() {
        fireboxPositions.clear();
    }

    void push() {
        if (life) {
            glm::vec3 front = mcamera->Front;
            glm::vec3 pos = mcamera->Position;
            fireboxPositions.push_back(glm::vec3(front[0] * 4 + pos[0], 0, front[2] * 4 + pos[2]));
        }
    }

    void draw(const std::vector<float> light) {
        if (fireboxPositions.empty()) {
            push();
        }
        glm::vec3 front = mcamera->Front;
        glm::vec3 pos = mcamera->Position;
        if(life) fireboxPositions[0] = glm::vec3(front[0] * 4 + pos[0], 0, front[2] * 4 + pos[2]);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, texture2);

        // activate shader
        ourShader->use();
        int max_len = 0;
        if (light.size() / 6 < 1000) {
            max_len = light.size() / 6;
            ourShader->setInt("max_len", max_len);
        }
        else {
            max_len = 1000;
            ourShader->setInt("max_len", max_len);
        }
        ourShader->setVec3("dirLight.direction", 0.2f, -0.2f, 0.2f);
        ourShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        ourShader->setVec3("dirLight.diffuse", 0.8f, 0.8f, 0.8f);
        ourShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        ourShader->setVec3("dirLight.lightcolor", 1.0f, 1.0f, 1.0f);

        char buf[1000];
        for (int i = 0; i < max_len; i++) {
            sprintf(buf, "pointLights[%d].position", i);
            ourShader->setVec3(buf, light[i * 6], light[i * 6 + 1], light[i * 6 + 2]);
            sprintf(buf, "pointLights[%d].ambient", i);
            ourShader->setVec3(buf, 0.05f, 0.05f, 0.05f);
            sprintf(buf, "pointLights[%d].diffuse", i);
            ourShader->setVec3(buf, 0.8f, 0.8f, 0.8f);
            sprintf(buf, "pointLights[%d].specular", i);
            ourShader->setVec3(buf, 1.0f, 1.0f, 1.0f);
            sprintf(buf, "pointLights[%d].constant", i);
            ourShader->setFloat(buf, 1.0f);
            ourShader->setFloat("pointLights[0].linear", 0.09f);
            sprintf(buf, "pointLights[%d].quadratic", i);
            ourShader->setFloat(buf, 0.032f);
            sprintf(buf, "pointLights[%d].lightcolor", i);
            ourShader->setVec3(buf, light[i * 6 + 3], light[i * 6 + 4], light[i * 6 + 5]);
        }
        for (int i = max_len; i < 1000; i++) {
            sprintf(buf, "pointLights[%d].constant", i);
            ourShader->setFloat(buf, 10000.0f);
        }

        ourShader->setVec3("viewPos", mcamera->Position);
        ourShader->setFloat("material.shininess", 64.0f);
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(mcamera->Zoom), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
        ourShader->setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = mcamera->GetViewMatrix();
        ourShader->setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int j = 0; j < fireboxPositions.size(); j++) {
            if (!life && j == 0) continue;
            if (j == 0) {
                ourShader->setVec3("dirLight.direction", 0.2f, -0.2f, 0.2f);
                ourShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
                ourShader->setVec3("dirLight.diffuse", 0.1f, 0.1f, 0.1f);
                ourShader->setVec3("dirLight.specular", 0.1f, 0.1f, 0.1f);
                ourShader->setVec3("dirLight.lightcolor", 1.0f, 1.0f, 1.0f);
            }
            else {
                ourShader->setVec3("dirLight.direction", 0.2f, -0.2f, 0.2f);
                ourShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
                ourShader->setVec3("dirLight.diffuse", 0.8f, 0.8f, 0.8f);
                ourShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
                ourShader->setVec3("dirLight.lightcolor", 1.0f, 1.0f, 1.0f);
            }
            for (unsigned int i = 0; i < cubePositions.size(); i++) {

                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                model = glm::translate(model, cubePositions[i]);
                model = glm::translate(model, fireboxPositions[j]);
                // float angle = 0.0f; //20.0f * i;
                // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                ourShader->setMat4("model", model);
                // glActiveTexture(GL_TEXTURE0);
                // glBindTexture(GL_TEXTURE_2D, texture1);
                // glDrawArrays(GL_TRIANGLES, 0, 6);
                // glActiveTexture(GL_TEXTURE0);
                // glBindTexture(GL_TEXTURE_2D, texture2);
                // glDrawArrays(GL_TRIANGLES, 0, 30);
                // glActiveTexture(GL_TEXTURE0);
                // glBindTexture(GL_TEXTURE_2D, texture3);
                // glDrawArrays(GL_TRIANGLES, 0, 36);
                if (i / 12 == 1 || i / 12 == 12) {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, texture5);
                }
                else if (i >= 14 * 12 + 12) {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, texture6);
                }
                else {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, texture4);
                }

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }


    }
};

#endif