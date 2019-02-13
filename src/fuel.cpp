#include "main.h"
#include "fuel.h"

Fuel::Fuel(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotate = glm::mat4(1.0f);
    GLfloat vertex_buffer_data[10001];
    int j = 0;


    // fuel
    GLfloat *crosshar = Cuboid::CuboidArray(1.0f,1.0f,1.0f,1.0f,2.0f);
    for(int i = 0 ; i < 6*6*3 ; ++i){
        vertex_buffer_data[j++] = crosshar[i];
    }
    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_RED, GL_FILL);

}

void Fuel::draw(glm::mat4 VP) {
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
}

void Fuel::tick(float percent) {
    free(this->object);
    GLfloat vertex_buffer_data[10001];
    int j = 0;
    GLfloat *crosshar = Cuboid::CuboidArray(30.0f*percent,30.0f*percent,30.0f*percent,30.0f*percent,2.0f);
    for(int i = 0 ; i < 6*6*3 ; ++i){
        vertex_buffer_data[j++] = crosshar[i];
    }
    free(crosshar);
    this->position.x = -30.0f + 15.0f*percent;
    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_RED, GL_FILL);
}
