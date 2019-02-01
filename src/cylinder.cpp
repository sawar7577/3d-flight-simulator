#include "cylinder.h"
#include "main.h"

Cylinder::Cylinder(float x, float y, float radius1 , float radius2, float ecc, float height, int vertices, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    
    speed = 1;
    float angle = 0;
    float incr = 2*M_PI/vertices;
    GLfloat vertex_buffer_data[100000];
    GLfloat *body = CylinderArray(radius1, radius2, ecc, height, vertices);
    int j = 0;
    int i = 0;
    for(i = 0 ; i < 4*vertices*9 ; ++i,++j){
        vertex_buffer_data[i] = body[i];
    }
    free(body);
    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, color, GL_FILL);
}

GLfloat * Cylinder::CylinderArray(float radius1 , float radius2, float ecc, float height, int vertices) {
    float angle = 0;
    float incr = 2*M_PI/vertices;
    GLfloat * vertex_buffer_data = (GLfloat *)malloc(sizeof(GLfloat) * (36*vertices));
    int j = 0;
    int i = 0;
    for(i = 0 ; i < vertices; ++i)
    {
        vertex_buffer_data[j++] = 0.0f; 
        vertex_buffer_data[j++] = 0.0f + height/2;
        vertex_buffer_data[j++] = 0.0f;

        vertex_buffer_data[j++] = radius1*cos(angle); 
        vertex_buffer_data[j++] = 0.0f + height/2;
        vertex_buffer_data[j++] = radius1*sin(angle)*ecc;

        vertex_buffer_data[j++] = radius1*cos(angle + incr); 
        vertex_buffer_data[j++] = 0.0f + height/2;
        vertex_buffer_data[j++] = radius1*sin(angle + incr)*ecc;

        angle += incr;
    }
    
    for(i = 0 ; i < vertices; ++i)
    {
        vertex_buffer_data[j++] = 0.0f; 
        vertex_buffer_data[j++] = 0.0f - height/2;
        vertex_buffer_data[j++] = 0.0f;

        vertex_buffer_data[j++] = radius2*cos(angle); 
        vertex_buffer_data[j++] = 0.0f - height/2;
        vertex_buffer_data[j++] = radius2*sin(angle)*ecc;

        vertex_buffer_data[j++] = radius2*cos(angle + incr); 
        vertex_buffer_data[j++] = 0.0f - height/2;
        vertex_buffer_data[j++] = radius2*sin(angle + incr)*ecc;

        angle += incr;
    }

    for(i = 0 ; i < vertices; ++i)
    {
        vertex_buffer_data[j++] = radius2*cos(angle); 
        vertex_buffer_data[j++] = 0.0f - height/2;
        vertex_buffer_data[j++] = radius2*sin(angle)*ecc;

        vertex_buffer_data[j++] = radius2*cos(angle + incr); 
        vertex_buffer_data[j++] = 0.0f - height/2;
        vertex_buffer_data[j++] = radius2*sin(angle + incr)*ecc;

        vertex_buffer_data[j++] = radius1*cos(angle); 
        vertex_buffer_data[j++] = 0.0f + height/2;
        vertex_buffer_data[j++] = radius1*sin(angle)*ecc;

        angle += incr;
    }

    angle = 0;

    for(i = 0 ; i < vertices; ++i)
    {
        vertex_buffer_data[j++] = radius1*cos(angle); 
        vertex_buffer_data[j++] = 0.0f + height/2;
        vertex_buffer_data[j++] = radius1*sin(angle)*ecc;

        vertex_buffer_data[j++] = radius1*cos(angle + incr); 
        vertex_buffer_data[j++] = 0.0f + height/2;
        vertex_buffer_data[j++] = radius1*sin(angle + incr)*ecc;

        vertex_buffer_data[j++] = radius2*cos(angle + incr); 
        vertex_buffer_data[j++] = 0.0f - height/2;
        vertex_buffer_data[j++] = radius2*sin(angle + incr)*ecc;

        angle += incr;
    }
    return vertex_buffer_data;
}

void Cylinder::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cylinder::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cylinder::tick() {
    this->rotation += speed;
    // this->position.x -= speed/100;
    // this->position.y -= speed;
}

