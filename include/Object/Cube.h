#ifndef CUBE_H
#define CUBE_H

#include "glad/glad.h"
// #include "glfw3.h"

#include "stb_image.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <vector>

#include "Vertex_Manager.h"

class Cube{
public:

    // 不允许不指定顶点格式的构造
    Cube()=delete;

    /*
        指明顶点数据格式, 一共有vn*an个float值
        vn 是顶点个数
        an 是一个顶点的属性个数
        path 顶点数据文件路径
        把顶点数据拷贝到GPU并创建一个 VBO
    */
    Cube(int vn, int an, std::string path);

    /*
        attr_num 是一个顶点数据中有几种属性, 即val_num数组中数据的个数
        val_num 是一个数组, 其中应该有每一个属性包含的float值数量
        if_norm 指明顶点数据是否需要标准化
        该函数会检查所定义的属性解析方式是否符合要求
        
        返回新创建的立方体的下标index, 可使用[]去访问
    */
    int CreateCube(unsigned int attr_num, unsigned int* val_num, bool if_norm);
    /*
        显示立方体
        index 指定要绘制哪个立方体
    */
    int DrawCube(unsigned int index);

    unsigned int operator[](int index);
    ~Cube();
public:
    // 管理原始顶点数据
    Vertex_Manager vertex;
    // VBO 顶点缓冲对象 
    unsigned int VBO;
    /* 
        VAO 顶点数组对象
        对于解析顶点数据的方式可以有多个
    */
    std::vector<unsigned int> VAO;

};

#endif