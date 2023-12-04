#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "ICamera.h"
#include "Shader.h"
#include <vector>

extern unsigned int WIN_WIDTH;
extern unsigned int WIN_HEIGHT;

class Background {
    ICamera* mcamera;
    Shader* ourShader;
    float vertices[6 * 8 * 6];
    std::vector<glm::vec3> cubePositions;
    int h; // background length 
    int w; // bcakgournd width
    float z; // background height
    unsigned int VBO, VAO;
    unsigned int texture1, texture2, texture3, texture4, texture5, texture6;
    std::vector<int> texture_random;
public:
    Background(int h, int w, int z, ICamera* mcamera) : h(h), w(w), z(z), mcamera(mcamera) {
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
        memcpy(vertices, vertices_t, sizeof(vertices_t));
        // world space positions of our cubes        
        for (int i = -h; i < h; i++) {
            for (int j = -w; j < w; j++) {
                cubePositions.push_back(glm::vec3(1.0f * i, 0.0f + z, 1.0f * j));
            }
        }
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
        unsigned char* data = stbi_load("img/grass2.png", &width, &height, &nrChannels, 0);
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
        data = stbi_load("img/road.jpg", &width, &height, &nrChannels, 0);
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
        data = stbi_load("img/road_r.jpg", &width, &height, &nrChannels, 0);
        if (data) {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // load image, create texture and generate mipmaps
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        data = stbi_load("img/grass_side.png", &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // load image, create texture and generate mipmaps
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        data = stbi_load("img/stone.png", &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // load image, create texture and generate mipmaps
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        data = stbi_load("img/tree.png", &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);


        for (int i = 0; i < cubePositions.size(); i++) texture_random.push_back(rand() % 3);
        // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
        // -------------------------------------------------------------------------------------------
        ourShader->use();
        ourShader->setInt("texture1", 0);
        // ourShader->setInt("texture2", 1);

        // ourShader->setInt("material.diffuse", 0);
        // ourShader->setInt("material.specular", 0);
    }

    ~Background() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        delete(ourShader);
    }

    void draw(const std::vector<float> light) {
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
        ourShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        ourShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        ourShader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        ourShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        ourShader->setVec3("dirLight.lightcolor", 1.0f, 1.0f, 1.0f);

        char buf[1000];
        for (int i = 0; i < max_len; i++) {
            sprintf(buf, "pointLights[%d].position", i);
            ourShader->setVec3(buf, light[i * 1], light[i * 2 + 1], light[i * 3 + 2]);
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
            ourShader->setVec3(buf, light[i * 4 + 3], light[i * 5 + 4], light[i * 6 + 5]);
        }
        for (int i = max_len; i < 1000; i++) {
            sprintf(buf, "pointLights[%d].constant", i);
            ourShader->setFloat(buf, 10000.0f);
        }

        ourShader->setVec3("viewPos", mcamera->Position);
        ourShader->setFloat("material.shininess", 32.0f);
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(mcamera->Zoom), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
        ourShader->setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = mcamera->GetViewMatrix();
        ourShader->setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < cubePositions.size(); i++) {
            int nx = i / (2 * h);
            int ny = i % (2 * h);
            if (ny == h) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture2);
            }
            else if (nx == w && ny != h) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture3);
            }
            else if (nx == w + 1 || nx == w - 1 || ny == h + 1 || ny == h - 1) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture5);
            }
            else {
                switch (texture_random[i]) {
                case 0: // grass
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, texture1);
                    break;
                case 1: // grass_side
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, texture1);
                    break;
                case 2: // stone
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, texture1);
                    break;
                    // case 3:
                    //     glActiveTexture(GL_TEXTURE0);
                    //     glBindTexture(GL_TEXTURE_2D, texture6);
                    //     break;
                }

            }
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            // float angle = 0.0f; //20.0f * i;
            // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader->setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

    }
};

#endif