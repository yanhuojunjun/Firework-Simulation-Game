#ifndef SHADER_H
#define SHADER_H

#include "glad.h" // 包含glad来获取所有的必须OpenGL头文件

#include "glm.hpp"
#include "gtc/type_ptr.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
public:
    // 程序ID
    unsigned int ID;

    Shader();
    // 构造器读取并构建着色器
    Shader(const char* vertexPath, const char* fragmentPath);
    int Build(const char* vertexPath, const char* fragmentPath);
    // 使用/激活程序
    void use();
    // uniform工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &value) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void deleteShader();
    
private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif