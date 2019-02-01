#include "airplane.h"
#include "main.h"

Airplane::Airplane(float x, float y, float radius1 , float radius2, float ecc, float height, int vertices, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    GLfloat vertex_buffer_data[100000];
    int i = 0;
    int j = 0;
    GLfloat *body = Cylinder::CylinderArray(0.75f, 1.25f, 1, 10.0f, 25);
    for(i = 0 ; i < 36*25 ; ++i, ++j) {
        vertex_buffer_data[j] = body[i];
    }
    std::cout << j << std::endl;
    free(body);

    GLfloat *front = Cylinder::CylinderArray(1.25f, 0.0f, 1, 2.0f, 25);
    for(i = 0 ; i < 36*25 ; ++i, ++j) {
        if(i%3 == 1)
            vertex_buffer_data[j] = front[i] - 6.0f;
        else
            vertex_buffer_data[j] = front[i];
    }
    std::cout << j << std::endl;    
    free(front);


    GLfloat *back = Cylinder::CylinderArray(1.0f, 0.75f, 1, 1.0f, 25);
    for(i = 0 ; i < 36*25 ; ++i, ++j) {
        if(i%3 == 1)
            vertex_buffer_data[j] = back[i] + 5.5f;
        else
            vertex_buffer_data[j] = back[i];
    }
    std::cout << j << std::endl;    
    free(back);

    // GLfloat *wings = Cylinder::CylinderArray(6.25f, 6.0f, 2.0f, 2.0f, 4);
    // for(i = 0 ; i < 36*4 ; ++i, ++j) {
    //         vertex_buffer_data[j] = wings[i];
    // }
    // std::cout << j << std::endl;    
    // free(wings);


    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, color, GL_FILL);
}

void Airplane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Airplane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Airplane::tick() {
    // this->rotation += speed;
    // this->position.x -= speed/100;
    // this->position.y -= speed;
}

