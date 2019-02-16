#include "main.h"
#include "altimeter.h"

Altimeter::Altimeter(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotate = glm::mat4(1.0f);
    GLfloat vertex_buffer_data[1000001];
    int j = 0;

    // Altimeter
    GLfloat *crosshar = Cuboid::CuboidArray(0.5f,0.5f,0.5f,0.5f,40.0f);
    for(int i = 0 ; i < 6*6*3 ; ++i){
        vertex_buffer_data[j++] = crosshar[i];
    }
    free(crosshar);
    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_RED, GL_FILL);
    
    crosshar = Cuboid::CuboidArray(2.0f,2.0f,2.0f,2.0f,0.5f);
    j = 0;
    for(int i = 0 ; i < 6*6*3 ; ++i) {
        vertex_buffer_data[j++] = crosshar[i];
    }
    free(crosshar);
    this->meter = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Altimeter::draw(glm::mat4 VP) {
    float top    = screen_center_y + 30 / screen_zoom;
    float bottom = screen_center_y - 30 / screen_zoom;
    float left   = screen_center_x - 30 / screen_zoom;
    float right  = screen_center_x + 30 / screen_zoom;
    VP = glm::ortho(left, right, bottom, top, 0.0f, 500.0f);

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    Matrices.model = glm::translate(this->meterposition) * Matrices.model;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->meter);
}

void Altimeter::changeHeight(Airplane &airp) {
    this->meterposition = glm::vec3(0,-20+40*std::min((airp.position.y/1000.0f),1.0f),0);
}