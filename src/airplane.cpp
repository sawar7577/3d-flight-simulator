#include "airplane.h"
#include "main.h"


Airplane::Airplane(float x, float y, float radius1 , float radius2, float ecc, float height, int vertices, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->pitch = -M_PI/2;
    this->yaw = 0;
    this->roll = 0;
    this->dir = glm::vec3(0,1,0);
    this->up = glm::vec3(0,0,1);
    this->rotate = glm::mat4(1.0f);
    this->fvalue = 1.0f;
    this->velocity = glm::vec3(1.0f);
    this->barrel_roll = false;
    this->loop_the_loop = false;
    this->counter = 0;
    this->score = 23;
    this->health = 20;
    this->cooldown = clock();

    this->speed = 1.1f;
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


void Airplane::draw(glm::mat4 VP) {
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
    int lp = glGetUniformLocation(programID, "lightpos");
    glProgramUniform3f(programID, lp, this->position.x, this->position.y, this->position.z); 
    draw3DObject(this->object);
    // draw3DObject((this->bounding).object);
}

void Airplane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Airplane::tick(GLFWwindow *window) {
    static float total_pitch;
    this->pitch = 0.0f;
    this->yaw = 0.0f;
    this->roll = 0.0f;
    this->fvalue = std::max(this->fvalue-0.0001f,0.0f);
    if(!this->loop_the_loop && !this->barrel_roll) {
        this->counter = 0;
        if(glfwGetKey(window, GLFW_KEY_UP)){
            this->pitch = 0.02f;
        }
        if(glfwGetKey(window, GLFW_KEY_DOWN)){
            this->pitch = -0.02f ;    
        }
        if(glfwGetKey(window, GLFW_KEY_RIGHT)){
            this->roll = -0.02f;
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT)){
            this->roll = 0.02f;
        }
        if(glfwGetKey(window, GLFW_KEY_S)){
            this->yaw = -0.02f;
        }
        if(glfwGetKey(window, GLFW_KEY_E)){
            this->yaw = 0.02f;
        }
        if(glfwGetKey(window, GLFW_KEY_T)){
            this->speed += 0.02f;
        }
        if(glfwGetKey(window, GLFW_KEY_SPACE)) {
            if( (clock() - this->cooldown)/CLOCKS_PER_SEC > 0.125f) {
                this->cooldown = clock();
                std::cout << "in " << std::endl;
                if(this->target == NULL) {
                    std::cout << "follow null" << std::endl;
                }
                if(this->etarget == NULL) {
                    std::cout << "efollow null" << std::endl;
                }
                Missile m = Missile(this->position.x, this->position.y, this->position.z, 1.0f,1.0f,30, this->dir, COLOR_GREEN);
                m.follow = this->target;
                m.efollow = this->etarget;
                if(m.follow == NULL) {
                    std::cout << "2follow null" << std::endl;
                }
                if(m.efollow == NULL) {
                    std::cout << "2efollow null" << std::endl;
                }
                ms.push_back(m);
            }
        }
        if(glfwGetKey(window, GLFW_KEY_B)) {
            if( (clock() - this->cooldown)/CLOCKS_PER_SEC > 0.125f) {
                this->cooldown = clock();
                Bomb b = Bomb(this->position.x, this->position.y, this->position.z, 1.0f,1.0f,30, this->dir, COLOR_GREEN);
            
                bms.push_back(b);
            }
        }
    }
    else {
        if(this->barrel_roll) {

        }
        if(this->loop_the_loop) {
            if(total_pitch >= 2*M_PI) {
                this->loop_the_loop = false;
                total_pitch = 0.0f;
            }
            else {
                this->counter++;
                this->pitch = 0.008f;
                total_pitch += 0.008f;
            }
        }
    }
    this->position += glm::normalize(this->dir)*this->speed*1.0f;
    this->bounding.position = this->position;
}

