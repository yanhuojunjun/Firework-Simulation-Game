#include "particle_render.h"

particle_render::particle_render() {
    /*
        TODO:
        创建 shader
        生成VBO, VAO缓冲 要足够大能放下所有顶点数据 或者可以在不够时扩容

    */

}

void particle_render::AddGroup(particle_group* new_group) {
    /*
        TODO:
        增加一个新的粒子群
        这里是一个最最简陋的方法
    */
    particle_groups.push_back(new_group);
}

void particle_render::DeleteGroup(/*args*/) {
    /*
        TODO:
        当一个粒子群死亡时需要从待渲染的粒子群列表中删除
    */
}

void particle_render::collect() {
    /*
        TODO:
        从 particle_groups 中收集所有顶点数据(调用particle_group的upload函数即可)到CPU缓冲
        将收集到的数据写入GPU缓冲即VBO
        这里可能需要扩充VBO大小(删除重建大概?)
    */
}

void particle_render::render() {
    /*
        TODO:
        用 GL_DrawArrays(GL_POINTS, , )去渲染所有收集到的顶点(粒子)
    */
}

particle_render::~particle_render() {
    /*
        TODO:
        删除着色器, 顶点缓冲
    */
}