#include "missile.h"
#include "main.h"

// struct Point {
//     float x, y, z;
// };

// std::vector <Point> returnRectangles(Point a, Point b, Point c, Point d) {
//     std::vector <Point> rec;
//     rec.push_back(a);
//     rec.push_back(b);
//     rec.push_back(c);
//     rec.push_back(c);
//     rec.push_back(d);
//     rec.push_back(a);
//     return rec;
// }

Missile::Missile(float x, float y, float z, float radius, float length, int vertices, glm::vec3 d, color_t color) {

    this->rotate = glm::mat4(1.0f);
    this->position = glm::vec3(x, y, z);
    this->follow = NULL;
    this->dir = d;
    GLfloat vertex_buffer_data[100000];
    int i = 0;
    int j = 0;
    GLfloat *body = Cylinder::CylinderArray(radius, 0.8*radius, 1, 0.7*length, 25);
    for(i = 0 ; i < 36*25 ; ++i, ++j) {
        vertex_buffer_data[j] = body[i];
    }
    free(body);

    GLfloat *front = Cylinder::CylinderArray(0.25f, radius, 1, 0.15*length, 25);
    for(i = 0 ; i < 36*25 ; ++i, ++j) {
        if(i%3 == 1)
            vertex_buffer_data[j] = front[i] + (0.7*length + 0.15*length)/2;
        else
            vertex_buffer_data[j] = front[i];
    }
    free(front);

    GLfloat *back = Cylinder::CylinderArray(0.8*radius, radius, 1, 0.15*length, 25);
    for(i = 0 ; i < 36*25 ; ++i, ++j) {
        if(i%3 == 1)
            vertex_buffer_data[j] = back[i] - (0.7*length + 0.15*length)/2;
        else
            vertex_buffer_data[j] = back[i];
    }
    free(back);
    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, color, GL_FILL);
}


void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Missile::tick()
{
    if(this->follow != NULL){
        
        this->dir = (glm::normalize((this->follow)->position - this->position));
        this->position += this->dir;
 
        std::cout << (this->follow)->position.x << " " << (this->follow)->position.y << " " << (this->follow)->position.z << std::endl;
        glm::vec3 d = glm::normalize((this->follow)->position - this->position);
        glm::vec3 k = glm::normalize(d + glm::vec3(0,1,0));
        glm::vec3 a = glm::cross(k,d);
        glm::vec3 b = glm::cross(a,d);
        rotate[1][0] = d.x;
        rotate[1][1] = d.y;
        rotate[1][2] = d.z;
        
        rotate[2][0] = a.x;
        rotate[2][1] = a.y;
        rotate[2][2] = a.z;
        
        rotate[0][0] = b.x;
        rotate[0][1] = b.y;
        rotate[0][2] = b.z;

    }
    else{
        this->position += this->dir;

        glm::vec3 d = glm::normalize(this->dir);
        glm::vec3 k = glm::normalize(d + glm::vec3(0,1,0));
        glm::vec3 a = glm::cross(k,d);
        glm::vec3 b = glm::cross(a,d);
        rotate[1][0] = d.x;
        rotate[1][1] = d.y;
        rotate[1][2] = d.z;
        
        rotate[2][0] = a.x;
        rotate[2][1] = a.y;
        rotate[2][2] = a.z;
        
        rotate[0][0] = b.x;
        rotate[0][1] = b.y;
        rotate[0][2] = b.z;
    }
    
}




