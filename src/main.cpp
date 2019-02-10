#include "main.h"
#include "timer.h"
#include "ball.h"
#include "cylinder.h"
#include "sterrain.h"
#include "airplane.h"
#include "cuboid.h"
#include "ring.h"
#include "collision.h"
#include <time.h>


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Cylinder cyl1;
// Terrain terr;
STerrain st;
Airplane air;
Cuboid d;
Cuboid sky;
Ring r;
int flag;
int stop;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float camera_x = 5, camera_y = 5, camera_z = 5;
clock_t tme;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    if(stop == 0)glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 pos = air.position - 20.0f*air.dir;
    glm::vec3 pos2= air.position;    
    pos2.y = air.position.y + 100.0f;
    glm::vec3 eye[2];
    eye[0] = pos;
    eye[1] = pos2;


    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (air.position.x, air.position.y , air.position.z );
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up[2];
    up[0] = air.up;
    up[1] = glm::vec3(0,0,-1);


    glm::vec3 testTarget = r.position;
    glm::vec3 testEye = glm::vec3(100,100,100);
    glm::vec3 testUp = glm::vec3(0,0,-1);

    // Matrices.view = glm::lookAt( testEye, testTarget, testUp ); // Rotating Camera for 3D


    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye[flag], target, up[flag] ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    if(stop == 0) {
    st.draw(VP);
    air.draw(VP);
    sky.draw(VP);
    r.draw(VP);
    d.draw(VP);
    }
    // terr.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int u = glfwGetKey(window, GLFW_KEY_X);
    int f = glfwGetKey(window, GLFW_KEY_Z);
    if (u) {
        flag = 0;
    }
    if(f) {
        flag = 1;
    }
    // if(flag == 1){
        camera_x = 0;
        camera_y = 170;
        camera_z = 0;
    // }
    // else
    // {
    //     camera_x = 500.0f;
    //     camera_y = 0.0f;
    //     camera_z = 0.0f;
    // }
    if(up)
    {
        cyl1.rotation += 1.0f;
        // terr.rotation += 1.0f;

    }
    if(down)
    {
        cyl1.rotation -= 1.0f;
        // terr.rotation -= 1.0f;    
    }
    
}

void tick_elements(GLFWwindow *window) {
   if(stop == 0) {
    air.tick(window);
    // terr.tick();
    // d.tick();
    st.tick();
   }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    
    // ball1       = Ball(0, 0, COLOR_RED);
    // cyl1        = Cylinder(0,0,2.0f,2.0f,1.0f,5.0f, 4, COLOR_RED);
    // terr        = Terrain(0,0,60,60, COLOR_RED);
    air         = Airplane(0,20.0f,1.0f,1.0f,1.0f,5.0f,30,COLOR_GREEN);
    sky         = Cuboid(0, 0, 0, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1.0f,COLOR_BLACK);
    d           = Cuboid(100,100,100, 10, 10, 10 ,10 ,10, COLOR_GREEN);
    st          = STerrain(0,0,129,COLOR_RED);
    r           = Ring(0,100,0,20,20,COLOR_BLACK);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements(window);
            tick_input(window);
            if(!checkCollision(d, glm::mat4(1.0f), air.bounding, air.rotate)){
                stop = 1;
            }
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}


void reset_screen() {
    float top    = screen_center_y + 30 / screen_zoom;
    float bottom = screen_center_y - 30 / screen_zoom;
    float left   = screen_center_x - 30 / screen_zoom;
    float right  = screen_center_x + 30 / screen_zoom;
    Matrices.projection = glm::perspective(45.0f, (right - left)/(top - bottom), 1.0f, 500.0f);
}
