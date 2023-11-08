#ifndef VERTEX_MANAGER_H
#define VERTEX_MANAGER_H

#include <string>
#include <iostream>
#include <fstream>

class Vertex_Manager{
public:
    Vertex_Manager(int vn = 0, int an = 0);

    /*
        初始化顶点数据, 此时没有申请空间
        vn是顶点个数
        an是一个顶点有多少个属性(属性为一个float值)
    */
    int Initialize(int vn, int an);

    /*
        根据文件路径读取顶点数据并申请空间
        必须保证文件中包含的顶点数据符合初始化时定义的格式
    */ 
    int ReadVertexFrom(const std::string& path);

    /*
        控制台打印顶点数据
    */
    int PrintVertex();

    /*
        返回实际顶点数据
    */
    float* GetVertexData();
    /*
        返回顶点数据大小
        单位: 字节
    */
    size_t GetDataSize();
    /*
        返回顶点数据值个数
        单位: 个
    */
    unsigned int GetDataNum();
    /*
        返回一个顶点中共有多少个float值
    */
    int GetAttrNum();
    /*
        返回顶点数
    */
    int GetVertexNum();
    ~Vertex_Manager();

private:
    // 顶点数据数组 动态申请
    float* data;
    // 顶点个数 顶点属性个数
    int vertex_num, attr_num;

};

#endif