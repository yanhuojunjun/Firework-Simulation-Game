#include "World.h"


World::World() {
    
}

void World::Create() {
    v.Initialize(6, 6);
    v.ReadVertexFrom("Object/base_world.v");
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, v.GetDataSize(), v.GetVertexData(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    position.y = v.GetVertexData()[1];
}

bool World::OnGround(glm::vec3 pos) {
    return pos.y > position.y;
}

void World::Display() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, v.GetVertexNum());
    glBindVertexArray(0);
}

World::~World() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}