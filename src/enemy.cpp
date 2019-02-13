#include "main.h"
#include "enemy.h"

Enemy::Enemy(float x, float y, float z){
    this->position = glm::vec3(x,y,z);
    this->rotate = glm::mat4(1.0f);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

glm::vec3 Enemy::locationScreen(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    std::cout << this->position.y << std::endl;
    return glm::vec3(VP * translate * glm::vec4(this->position,1));
}