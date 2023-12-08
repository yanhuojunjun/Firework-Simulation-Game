#ifndef en
#define en
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Model.h"
#include "Icamera.h"
#include <iostream>

extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;
//场景类
class environment{
    public:
    Shader model_shader;
    Model house_model;
    ICamera* camera;
    environment(ICamera* _camera) :model_shader(Shader("Shaders/background.vs", "Shaders/background.fs")),
        house_model(Model("Object/scence/all_in_one.obj")),
    camera(_camera)
    {
    }
    // void draw_model(){
    //     // 模型的绘制
    //     // 房子模型绘制
    //     model_shader.use();
    //     glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    //     glm::mat4 view = camera->GetViewMatrix();
    //     model_shader.setMat4("projection", projection); // 房子的投影矩阵
    //     model_shader.setMat4("view", view); // 房子的观察矩阵
    //     glm::mat4 model = glm::mat4(1.0f); // 房子的模型矩阵
    //     model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    //     model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    //     model_shader.setMat4("model", model);
    //     house_model.Draw(model_shader);//绘制
    //     //发射器模型绘制
    //     model = glm::mat4(1.0f); // 发射器的模型矩阵
    //     model = glm::translate(model, glm::vec3(-5.0f, 5.0f, 10.0f)); // translate it down so it's at the center of the scene
    //     model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down
    //     model_shader.setMat4("model", model);
    //     fasheqi_model.Draw(model_shader);
    //     //树模型绘制
    //     model = glm::mat4(1.0f); // 树的模型矩阵
    //     model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 10.0f)); // translate it down so it's at the center of the scene
    //     model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    //     model_shader.setMat4("model", model);
    //     tree_model.Draw(model_shader);
    //     //城堡模型绘制
    //     model = glm::mat4(1.0f); // 城堡的模型矩阵
    //     model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    //     model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    //     model_shader.setMat4("model", model);
    //     castle.Draw(model_shader);
    //     //城堡2模型绘制
    //     model = glm::mat4(1.0f); // 城堡2的模型矩阵
    //     model = glm::translate(model, glm::vec3(20.0f, -20.0f, 0.0f)); // translate it down so it's at the center of the scene
    //     model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    //     model_shader.setMat4("model", model);
    //     castle2.Draw(model_shader);
    //     //一组房屋模型绘制
    //     model = glm::mat4(1.0f); // 城堡2的模型矩阵
    //     model = glm::translate(model, glm::vec3(-20.0f, -20.0f, 0.0f)); // translate it down so it's at the center of the scene
    //     model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    //     model_shader.setMat4("model", model);
    //     house_s.Draw(model_shader);
    //     //door模型绘制
    //     model = glm::mat4(1.0f); // 城堡2的模型矩阵
    //     model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    //     model = glm::scale(model, glm::vec3(1.f, 1.f, 1.f));	// it's a bit too big for our scene, so scale it down
    //     model_shader.setMat4("model", model);
    //     door.Draw(model_shader);
    // }
    void draw(const std::vector<float> light) {
        model_shader.use();
        int max_len = 0;
        if (light.size() / 6 < 1000) {
            max_len = light.size() / 6;
            model_shader.setInt("max_len", max_len);
        }
        else {
            max_len = 1000;
            model_shader.setInt("max_len", max_len);
        }
        model_shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        model_shader.setVec3("dirLight.ambient", 0.3f, 0.3f, 0.3f);
        model_shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        model_shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        model_shader.setVec3("dirLight.lightcolor", 1.0f, 1.0f, 1.0f);

        char buf[1000];
        for (int i = 0; i < max_len; i++) {
            sprintf(buf, "pointLights[%d].position", i);
            model_shader.setVec3(buf, light[i * 6], light[i * 6 + 1], light[i * 6 + 2]);
            sprintf(buf, "pointLights[%d].ambient", i);
            model_shader.setVec3(buf, 0.05f, 0.05f, 0.05f);
            sprintf(buf, "pointLights[%d].diffuse", i);
            model_shader.setVec3(buf, 0.8f, 0.8f, 0.8f);
            sprintf(buf, "pointLights[%d].specular", i);
            model_shader.setVec3(buf, 1.0f, 1.0f, 1.0f);
            sprintf(buf, "pointLights[%d].constant", i);
            model_shader.setFloat(buf, 1.0f);
            model_shader.setFloat("pointLights[0].linear", 0.09f);
            sprintf(buf, "pointLights[%d].quadratic", i);
            model_shader.setFloat(buf, 0.032f);
            sprintf(buf, "pointLights[%d].lightcolor", i);
            model_shader.setVec3(buf, light[i * 6 + 3], light[i * 6 + 4], light[i * 6 + 5]);
        }
        for (int i = max_len; i < 1000; i++) {
            sprintf(buf, "pointLights[%d].constant", i);
            model_shader.setFloat(buf, 10000.0f);
        }

        model_shader.setVec3("viewPos", camera->Position);
        model_shader.setFloat("material.shininess", 32.0f);
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
        model_shader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera->GetViewMatrix();
        model_shader.setMat4("view", view);

        // render boxes
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        // float angle = 0.0f; //20.0f * i;
        model = glm::translate(model, glm::vec3(0.0f, -0.51f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));	// it's a bit too big for our scene, so scale it down
        // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        model_shader.setMat4("model", model);
        house_model.Draw(model_shader);
    }
    ~environment() {
        
    }
};
#endif