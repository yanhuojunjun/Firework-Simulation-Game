#include "Vertex_Manager.h"
Vertex_Manager::Vertex_Manager(int vn, int an){
    data=nullptr;
    vertex_num = vn;
    attr_num = an;
}

int Vertex_Manager::Initialize(int vn, int an){
    if(data != nullptr) delete[] data;
    data=nullptr;
    vertex_num = vn;
    attr_num = an;
}

int Vertex_Manager::ReadVertexFrom(const std::string& path){
    if(vertex_num==0||attr_num==0){
        std::cout << "vertex number should be zero, cant't read" << std::endl;
        return -1;
    }
    std::fstream file(path, std::ios_base::in);
    if(!file.is_open()){
        std::cout << "error: can't open " << path << std::endl;
        return -1;
    }
    data = new float[vertex_num * attr_num];
    for(int i=0;i<vertex_num;i++){
        for(int j=0;j<attr_num;j++){
            file >> data[i*attr_num+j];
            if(file.eof() && i*attr_num+j < vertex_num*attr_num-1){
                file.close();
                std::cout << "can't get enough number from" << path << std::endl;
                return -1;
            }
        }
    }

    file.close();
    return 0;
}

int Vertex_Manager::PrintVertex(){
    if(data == nullptr){
        std::cout << "vertex data is null, cant't print" << std::endl;
        return -1;
    }
    for(int i=0;i<vertex_num;i++){
        for(int j=0;j<attr_num;j++){
            std::cout << data[i*attr_num+j] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}

float* Vertex_Manager::GetVertexData(){
    return data;
}

size_t Vertex_Manager::GetDataSize(){
    return vertex_num*attr_num*sizeof(float);
}

unsigned int Vertex_Manager::GetDataNum(){
    return vertex_num*attr_num;
} 

int Vertex_Manager::GetAttrNum(){
    return attr_num;
}
int Vertex_Manager::GetVertexNum(){
    return vertex_num;
}
Vertex_Manager::~Vertex_Manager(){
    if(data != nullptr) delete[] data;
}