#include "main.h"
#include "canon.h"
#include "airplane.h"
#include "bullet.h"
#include "rectangle.h"

// std::list <Bullet> bs;


Canon::Canon(float x, float y, float z, Airplane *target) : Enemy(x, y, z) {
    this->position = glm::vec3(x,y+8,z);
    this->dir = glm::vec3(0,1,0);
    this->target = target;
    this->rotate = glm::mat4(1.0f);
    GLfloat vertex_buffer_data[100001];
    float angle = 0;
    float angle2 = -M_PI/2;
    float inc = M_PI/10;
    float inc2 = M_PI/5;
    float radius = 10.0f;
    float radius2 = 02.5f;
    float width = 1.0f;
    this->damage = 0;
    this->points = 10;
    this->kill = false;
    this->bounding = Cuboid(x,y+8,z,20,20,20,20,20,COLOR_GREEN);
    int j = 0;
    for(int i = 0 ; i < 20 ; ++i){
        angle = 0;
        for(int k = 0 ; k < 10 ; ++k) {
            Point a1, b1, c1, d1;
            a1.x = radius*cos(angle)*cos(angle2);
            a1.z = radius*sin(angle)*cos(angle2);
            a1.y = radius*sin(angle2);

            b1.x = radius*cos(angle+inc2)*cos(angle2);
            b1.z = radius*sin(angle+inc2)*cos(angle2);
            b1.y = radius*sin(angle2);

            d1.x = radius*cos(angle)*cos(angle2+inc);
            d1.z = radius*sin(angle)*cos(angle2+inc);
            d1.y = radius*sin(angle2+inc);

            c1.x = radius*cos(angle+inc2)*cos(angle2+inc);
            c1.z = radius*sin(angle+inc2)*cos(angle2+inc);
            c1.y = radius*sin(angle2+inc);

            std::vector < Point > recs = returnRectangles(a1,b1,c1,d1);
            for(int m = 0 ; m < recs.size() ; ++m) {
                vertex_buffer_data[j++] = recs[m].x;
                vertex_buffer_data[j++] = recs[m].y;
                vertex_buffer_data[j++] = recs[m].z;
            }
            angle+=inc;
        }
        angle2+=inc;
    }
    
    GLfloat *body =CuboidArray(1.0f,1.0f,1.0f,1.0f, 30.5f);;
    for(int i = 0 ; i < 6*6*3 ; ++i){
        if(i%3 == 0){
            vertex_buffer_data[j++] = body[i] - 2.0f;
        }
        else if(i%3 == 1) {
            vertex_buffer_data[j++] = body[i] + 5.0f;
        }
        else {
            vertex_buffer_data[j++] = body[i];
        }
    }
    for(int i = 0 ; i < 6*6*3 ; ++i){
        if(i%3 == 0){
            vertex_buffer_data[j++] = body[i] + 2.0f;
        }
        else if(i%3 == 1) {
            vertex_buffer_data[j++] = body[i] + 5.0f;
        }
        else {
            vertex_buffer_data[j++] = body[i];
        }
    }
    // free(body);
    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_STEEL, GL_FILL);
}

void Canon::tick(){
    this->dir = (glm::normalize((this->target)->position - this->position));
    // this->position += this->dir;
    int rad = rand();
    if(rad %100 == 0) {
        bs.push_back(Bullet(this->position.x, this->position.y, this->position.z, 1.0f, 1.0f, 5, this->dir + ((this->target)->dir)/8.0f, COLOR_BLACK));
    }
    // std::cout << (this->target)->position.x << " " << (this->follow)->position.y << " " << (this->follow)->position.z << std::endl;
    glm::vec3 d = glm::normalize((this->target)->position - this->position);
    glm::vec3 k = glm::normalize(glm::vec3(d.y,-d.x,1));
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

void Canon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef

    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // this->bounding.draw(VP);
}