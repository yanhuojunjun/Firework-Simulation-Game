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
    Model house_model, fasheqi_model, tree_model, castle, castle2, house_s, door;
    ICamera* camera;
    environment(ICamera* _camera):model_shader(Shader("Shaders/insert_model.vs", "Shaders/insert_model.fs")),
    house_model(Model("D:/gitee/Git/SYSU_Final_CG/run/bin/Object/House/House.obj")),
    fasheqi_model(Model("D:/gitee/Git/SYSU_Final_CG/run/bin/Object/rocket_v3_L1.123c033fa9c8-2eec-48df-95eb-2f459c1d4497/12215_rocket_v3_l1.obj")),
    tree_model(Model("D:/gitee/Git/SYSU_Final_CG/run/bin/Object/Tree1/Tree1.obj")),
    castle(Model("D:/gitee/Git/SYSU_Final_CG/run/bin/Object/Castle/Castle OBJ.obj")),
    castle2(Model("D:/gitee/Git/SYSU_Final_CG/run/bin/Object/Castle/Castle OBJ2.obj")),
    house_s(Model("D:/cg_model_test/uploads_files_969463_building_collection.obj")),
    door(Model("D:/cg_model_test/door/uploads_files_2896564_arch.obj")),
    camera(_camera)
    {
    }
    void draw_model(){
        // 模型的绘制
        // 房子模型绘制
        model_shader.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();
        model_shader.setMat4("projection", projection); // 房子的投影矩阵
        model_shader.setMat4("view", view); // 房子的观察矩阵
        glm::mat4 model = glm::mat4(1.0f); // 房子的模型矩阵
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
        model_shader.setMat4("model", model);
        house_model.Draw(model_shader);//绘制
        //发射器模型绘制
        model = glm::mat4(1.0f); // 发射器的模型矩阵
        model = glm::translate(model, glm::vec3(-5.0f, 5.0f, 10.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down
        model_shader.setMat4("model", model);
        fasheqi_model.Draw(model_shader);
        //树模型绘制
        model = glm::mat4(1.0f); // 树的模型矩阵
        model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 10.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
        model_shader.setMat4("model", model);
        tree_model.Draw(model_shader);
        //城堡模型绘制
        model = glm::mat4(1.0f); // 城堡的模型矩阵
        model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
        model_shader.setMat4("model", model);
        castle.Draw(model_shader);
        //城堡2模型绘制
        model = glm::mat4(1.0f); // 城堡2的模型矩阵
        model = glm::translate(model, glm::vec3(20.0f, -20.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
        model_shader.setMat4("model", model);
        castle2.Draw(model_shader);
        //一组房屋模型绘制
        model = glm::mat4(1.0f); // 城堡2的模型矩阵
        model = glm::translate(model, glm::vec3(-20.0f, -20.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
        model_shader.setMat4("model", model);
        house_s.Draw(model_shader);
        //door模型绘制
        model = glm::mat4(1.0f); // 城堡2的模型矩阵
        model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.f, 1.f, 1.f));	// it's a bit too big for our scene, so scale it down
        model_shader.setMat4("model", model);
        door.Draw(model_shader);
    }
};
#endif