#include "Cube.h"

Cube::Cube(int vn, int an, std::string path){
    vertex.Initialize(vn, an);
    vertex.ReadVertexFrom(path);
    VBO = 0;
    VAO.clear();
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex.GetDataSize(), vertex.GetVertexData(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int Cube::CreateCube(unsigned int attr_num, unsigned int* val_num, bool if_norm){
    // 检查
    unsigned int attr_sum = 0;
    for(int i=0;i<attr_num;i++){
        attr_sum += val_num[i];
    }
    if(attr_sum > vertex.GetAttrNum()){
        std::cout << "can't creat cube" << std::endl;
        return -1;
    }

    // 新建一个 VAO
    unsigned int new_VAO;
    glGenVertexArrays(1, &new_VAO);
    glBindVertexArray(new_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 定义顶点属性指针
    attr_sum = 0;
    for(int i=0;i<attr_num;i++){
        glVertexAttribPointer(i, val_num[i], GL_FLOAT, if_norm, vertex.GetAttrNum() * sizeof(float), (void*)(attr_sum));
        glEnableVertexAttribArray(i);
        attr_sum += val_num[i]*sizeof(float);
    }
    VAO.push_back(new_VAO);
    //glBindVertexArray(0);

    return VAO.size()-1;
}

int Cube::DrawCube(unsigned int index){
    if(index > VAO.size()){
        std::cout << "DrawCube out of range" << std::endl;
        return -1;
    }
    glBindVertexArray(VAO[index]);
    glDrawArrays(GL_TRIANGLES, 0, vertex.GetVertexNum());
    glBindVertexArray(0);
    return 0;
}

unsigned int Cube::operator[](int index){
    return VAO[index];
}

Cube::~Cube(){
    glDeleteVertexArrays(VAO.size(), VAO.data());
    glDeleteBuffers(1, &VBO);
}