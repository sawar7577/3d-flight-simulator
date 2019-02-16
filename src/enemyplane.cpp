#include "enemyplane.h"
#include "main.h"


Enemyplane::Enemyplane(float x, float y, float radius1 , float radius2, float ecc, float height, int vertices, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->pitch = 0;
    this->yaw = 0;
    this->roll = 0;
    this->dir = glm::vec3(0,1,0);
    this->up = glm::vec3(0,0,1);
    this->rotate = glm::mat4(1.0f);
    this->fvalue = 1.0f;
    this->velocity = glm::vec3(1.0f);
    this->pitch_v = false;
    this->roll_v = false;
    this->yaw_v = false;
  
    speed = 1;
    GLfloat vertex_buffer_data[100000];
    int i = 0;
    int j = 0;
    GLfloat *body = Cylinder::CylinderArray(1.25f, 0.75f, 1, 10.0f, 25);
    for(i = 0 ; i < 36*25 ; ++i) {
        vertex_buffer_data[j++] = body[i];
    }
    // std::cout << j << std::endl;
    free(body);

    GLfloat *front = Cylinder::CylinderArray(0.25f, 1.25f, 1, 1.5f, 25);
    for(i = 0 ; i < 36*25 ; ++i) {
        if(i%3 == 1)
            vertex_buffer_data[j++] = front[i] + 11.5f/2.0f;
        else
            vertex_buffer_data[j++] = front[i];
    }
    // std::cout << j << std::endl;
    free(front);

    GLfloat *wings = Cuboid::CuboidArray(20.75f,5.75,1,1.0f, 1.5);
    for(i = 0 ; i < 6*6*3 ; ++i) {
       vertex_buffer_data[j++] = wings[i];
    }
    // std::cout << j << std::endl;    
    free(wings);


    GLfloat *back = Cylinder::CylinderArray(0.75f, 1.0f, 1, 1.0f, 25);
    for(i = 0 ; i < 36*25 ; ++i) {
        if(i%3 == 1)
            vertex_buffer_data[j++] = back[i] - 5.5f;
        else
            vertex_buffer_data[j++] = back[i];
    }
    // std::cout << j << std::endl;    
    free(back);
    this->bounding = Cuboid(x,y,0,10, 10, 10, 10, 10, COLOR_RED);
    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, color, GL_FILL);
}


void Enemyplane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef

    glm::mat4 p(1.0f);
    glm::mat4 r(1.0f);
    glm::mat4 y(1.0f);
    p = glm::rotate(this->pitch,glm::vec3(1,0,0));
    r = glm::rotate(this->yaw,glm::vec3(0,0,-1));
    y = glm::rotate(this->roll,glm::vec3(0,-1,0));
    
    this->rotate *= p;
    this->rotate *= y;
    this->rotate *= r;

    this->dir = glm::normalize(glm::vec3(rotate[1][0],rotate[1][1],rotate[1][2]));
    this->up = glm::normalize(glm::vec3(rotate[2][0],rotate[2][1],rotate[2][2]));

    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]); 
    draw3DObject(this->object);
    // draw3DObject((this->bounding).object);
}

void Enemyplane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemyplane::tick() {
    
    this->pitch = this->pitch_v ? 0.01f : 0.0f;
    this->roll = this->roll_v ? 0.01f : 0.0f;
    this->yaw = this->yaw_v ? 0.01f : 0.0f;

    this->pitch_v = random()%100 ? this->pitch_v : !this->pitch_v;
    this->roll_v = random()%100 ? this->roll_v : !this->roll_v;
    this->yaw_v = random()%100 ? this->yaw_v : !this->yaw_v;


    this->position += this->dir/1.0f;
    this->bounding.position = this->position;
}

