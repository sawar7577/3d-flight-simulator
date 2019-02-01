
#include "terrain.h"
#include "main.h"
// #define RANDOM (10-20*((double)rand()/RAND_MAX));
const int featuresize=16;

unsigned long xorshf96(void) {          //period 2^96-1
	static unsigned long x=123456789, y=362436069, z=521288629;
	unsigned long t;
		x ^= x << 16;
		x ^= x >> 5;
		x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z;
}

double values[1000000];

double sample(int x, int y, int width, int height)
{
    return values[(x & (width - 1)) + (y & (height - 1))*width ];
}

void setSample(int x, int y, double value,  int width, int height)
{
    values[(x & (width - 1)) + (y & (height - 1)) * width] = value;
}

void sampleSquare(int x, int y, int size, double value, int width, int height)
{
    int hs = size / 2;

    // a     b
    //
    //    x
    //
    // c     d

    double a = sample(x - hs, y - hs, width, height);
    double b = sample(x + hs, y - hs, width, height);
    double c = sample(x - hs, y + hs, width, height);
    double d = sample(x + hs, y + hs, width, height);

    setSample(x, y, ((a + b + c + d) / 4.0) + value, width, height);

}

void sampleDiamond(int x, int y, int size, double value, int width, int height)
{
    int hs = size / 2;

    //   c
    //
    //a  x  b
    //
    //   d

    double a = sample(x - hs, y, width, height);
    double b = sample(x + hs, y, width, height);
    double c = sample(x, y - hs, width, height);
    double d = sample(x, y + hs, width, height);

    setSample(x, y, ((a + b + c + d) / 4.0) + value, width, height);
}


void DiamondSquare(int stepsize, double scale, int width, int height)
{

    int halfstep= stepsize / 2;



    for (int y = halfstep; y < height + halfstep; y += stepsize)
    {
        for (int x = halfstep; x < width + halfstep; x += stepsize)
        {
            sampleSquare(x, y, stepsize, (10-20*((double)rand()/RAND_MAX)) * scale, width, height);
        }
    }

    for (int y = 0; y < height; y += stepsize)
    {
        for (int x = 0; x < width; x += stepsize)
        {
            sampleDiamond(x + halfstep, y, stepsize, (10-20*((double)rand()/RAND_MAX)) * scale, width, height);
            sampleDiamond(x, y + halfstep, stepsize, (10-20*((double)rand()/RAND_MAX)) * scale, width, height);

        }
    }

}


Terrain::Terrain(int x, int y, int width, int height, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 90.0f;
    speed = 1;
    srand(0);
    for( int y = 0; y < height; y += featuresize)
    for (int x = 0; x < width; x += featuresize)
    {
        srand(0);
        setSample(x, y, (10-20*((double)rand()/RAND_MAX)), width, height);  //IMPORTANT: frand() is a (10-20*((double)rand()/RAND_MAX)) function that returns a value between -1 and 1.
    }

    int samplesize = featuresize;

    double scale = 0.25;

    while (samplesize > 1)
    {

        DiamondSquare(samplesize, scale, width, height);

        samplesize /= 2;
        scale /= 2.0;
    }

    GLfloat vertex_buffer_data[100000];

    int j = 0;
    for( int y = 0; y < height; y += 1)
    for (int x = 0; x < width; x += 1)
    {
        vertex_buffer_data[j++] = x;
        vertex_buffer_data[j++] = y;
        vertex_buffer_data[j++] = sample(x,y,width, height);


        vertex_buffer_data[j++] = x+1;
        vertex_buffer_data[j++] = y;
        vertex_buffer_data[j++] = sample(x+1,y,width, height);


        vertex_buffer_data[j++] = x;
        vertex_buffer_data[j++] = y+1;
        vertex_buffer_data[j++] = sample(x,y+1,width, height);

        vertex_buffer_data[j++] = x+1;
        vertex_buffer_data[j++] = y+1;
        vertex_buffer_data[j++] = sample(x+1,y+1,width, height);


        vertex_buffer_data[j++] = x+1;
        vertex_buffer_data[j++] = y;
        vertex_buffer_data[j++] = sample(x+1,y,width, height);


        vertex_buffer_data[j++] = x;
        vertex_buffer_data[j++] = y+1;
        vertex_buffer_data[j++] = sample(x,y+1,width, height);
    }

    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, color, GL_FILL);
}

void Terrain::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Terrain::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Terrain::tick() {
    // this->rotation += speed;
    // this->position.x -= speed/100;
    // this->position.y -= speed;
}

