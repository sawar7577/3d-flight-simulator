
#include "sterrain.h"
#include "main.h"


float arr[3000][3000];
inline static float random(int range)
{
    int ret = (rand() % (range * 2)) - range;
    ret = std::max(ret, -15);
    ret = std::min(ret, 15);
    return ret;
}
float mx;
float mn;
void algo_step(int x, int y, int size) {
    if(size <= 2){
        return;
    }
    arr[x+size/2][y+size/2] = (arr[x][y] + arr[x+2*(size/2)][y] + 
    arr[x][y+2*(size/2)] + arr[x+2*(size/2)][y+2*(size/2)])/4;

    arr[x+size/2][y+size/2] = std::min(mx, arr[x+size/2][y+size/2]);
    arr[x+size/2][y+size/2] = std::max(mn, arr[x+size/2][y+size/2]);

    
    //Diamond steps
    arr[x+size/2][y]            = (arr[x][y] + arr[x+size/2][y+size/2] + arr[x+2*(size/2)][y])/3;
    arr[x+size/2][y]            += random(size/3 + 1);
    arr[x+size/2][y] = std::min(mx, arr[x+size/2][y]);
    arr[x+size/2][y] = std::max(mn, arr[x+size/2][y]);



    arr[x+2*(size/2)][y+size/2] = (arr[x][y+2*(size/2)] + arr[x+size/2][y+size/2] + arr[x+2*(size/2)][y+2*(size/2)])/3;
    arr[x+2*(size/2)][y+size/2] += random(size/3 + 1);
    arr[x+2*(size/2)][y+size/2] = std::min(mx, arr[x+2*(size/2)][y+size/2]);
    arr[x+2*(size/2)][y+size/2] = std::max(mn, arr[x+2*(size/2)][y+size/2]);



    arr[x][y+size/2]            = (arr[x][y] + arr[x+size/2][y+size/2] + arr[x][y+2*(size/2)])/3;
    arr[x][y+size/2]            += random(size/3 + 1); 
    arr[x][y+size/2] = std::min(mx, arr[x][y+size/2]);
    arr[x][y+size/2] = std::max(mn, arr[x][y+size/2]);



    arr[x+size/2][y+2*(size/2)] = (arr[x][y+2*(size/2)] + arr[x+size/2][y+size/2] + arr[x+2*(size/2)][y+2*(size/2)])/3;
    arr[x+size/2][y+2*(size/2)] += random(size/3 + 1);
    arr[x+size/2][y+2*(size/2)] = std::min(mx, arr[x+size/2][y+2*(size/2)]);
    arr[x+size/2][y+2*(size/2)] = std::max(mn, arr[x+size/2][y+2*(size/2)]);



    //algo steps
    algo_step(x,y,size/2 + 1);
    algo_step(x+size/2,y,size/2 + 1);
    algo_step(x,y+size/2,size/2 + 1);
    algo_step(x+size/2,y+size/2,size/2 + 1);

}

STerrain::STerrain(int x, int y, int z, int width, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    float scale = 2.5f;
    float scale2 = 2.5f;
    this->kill = false;
    this->bounding = Cuboid(x+scale2+width, 1, z+scale2+width, (float)width*scale2, (float)width*scale2, (float)width*scale2, (float)width*scale2, 1, COLOR_RED);
    this->rotate = glm::mat4(1.0f);
    // this->bounding = Cuboid(x,y+1,z,width,width,width,width,1,COLOR_GREEN);
    // width = 129;
    // speed = 0.05;
    srand(clock());
    arr[1][1] = arr[1][width] = arr[width][1] = arr[width][width] = 0;
    mx = width;
    mn = -2;
    algo_step(1,1,width);   
    int i,j,k;
    j = 0;
    GLfloat vertex_buffer_data[500000];
    for(i = 1; i < width ; ++i) {
        for(k = 1; k < width ; ++k){

            if(i%2 == 1){
                vertex_buffer_data[j++] =  scale2 * i;
                vertex_buffer_data[j++] =  scale * arr[i][k];
                vertex_buffer_data[j++] =  scale2 * k;
                
                vertex_buffer_data[j++] =  scale2 * i;
                vertex_buffer_data[j++] =  scale * arr[i][k+1];
                vertex_buffer_data[j++] =  scale2 * (k+1);
                
                vertex_buffer_data[j++] =  scale2 * (i+1);
                vertex_buffer_data[j++] =  scale * arr[i+1][k+1];
                vertex_buffer_data[j++] =  scale2 * (k+1);

                vertex_buffer_data[j++] =  scale2 * (i+1);
                vertex_buffer_data[j++] =  scale * arr[i+1][k];
                vertex_buffer_data[j++] =  scale2 * k;
                
                vertex_buffer_data[j++] =  scale2 * (i+1);
                vertex_buffer_data[j++] =  scale * arr[i+1][k+1];
                vertex_buffer_data[j++] =  scale2 * (k+1);
                
                vertex_buffer_data[j++] =  scale2 * (i+2);
                vertex_buffer_data[j++] =  scale * arr[i+2][k+1];
                vertex_buffer_data[j++] =  scale2 * (k+1);
                
            }
            else {
                vertex_buffer_data[j++] =  scale2 * i;
                vertex_buffer_data[j++] =  scale * arr[i][k];
                vertex_buffer_data[j++] =  scale2 * k;
                
                vertex_buffer_data[j++] =  scale2 * i;
                vertex_buffer_data[j++] =  scale * arr[i][k+1];
                vertex_buffer_data[j++] =  scale2 * (k+1);
                
                vertex_buffer_data[j++] =  scale2 * (i-1);
                vertex_buffer_data[j++] =  scale * arr[i-1][k];
                vertex_buffer_data[j++] =  scale2 *k;


                vertex_buffer_data[j++] =  scale2 * (i+1);
                vertex_buffer_data[j++] =  scale * arr[i+1][k];
                vertex_buffer_data[j++] =  scale2 * k;
                
                vertex_buffer_data[j++] =  scale2 * (i+1);
                vertex_buffer_data[j++] =  scale * arr[i+1][k+1];
                vertex_buffer_data[j++] =  scale2 * (k+1);
                
                vertex_buffer_data[j++] =  scale2 * i;
                vertex_buffer_data[j++] =  scale * arr[i][k];
                vertex_buffer_data[j++] =  scale2 * k;
            }

        }
    }

    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_BROWN, GL_FILL);
}

void STerrain::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // this->bounding.draw(VP);
}

void STerrain::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void STerrain::tick() {

}
