#include "main.h"
#include "timer.h"
#include "ball.h"
#include "cylinder.h"
#include "sterrain.h"
#include "airplane.h"
#include "cuboid.h"
#include "ring.h"
#include "collision.h"
#include "missile.h"
#include "parachute.h"
#include "dashboard.h"
#include "canon.h"
#include "bullet.h"
#include "arrow.h"
#include "volcano.h"
#include "fuelup.h"
#include "enemyplane.h"
#include "bomb.h"
#include <time.h>
#include <list>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

unsigned long int XOR()
{
  static unsigned long y=2463534242;
  y = y ^ (y<<13);
    y=(y>>17); 
  return (y = y ^(y<<5)); 
};


Canon c;
STerrain st;
Airplane air;
Cuboid sky;
Dashboard dash;
int flag;
int stop;
bool tg[3];
Arrow a;
list <Missile> ms;
list <Parachute> ps;
list <Enemyplane> es;
list <Bomb> bms;
list <Bullet> bs;
list <Volcano> vs;
list <Fuelup> fs;
list <Ring> rs;
list <STerrain> ss;


float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float camera_x = 5, camera_y = 5, camera_z = 5;
clock_t tme;


template <typename Type> void tick_sprite(list <Type> &l) {
    typename list <Type> :: iterator it;
    for(it = l.begin() ; it != l.end() ; ++it) {
        (*it).tick();
    }
}

template <typename Type> void draw_sprite(list <Type> &l, glm::mat4 VP) {
    typename list <Type> :: iterator it;
    for(it = l.begin() ; it != l.end() ; ++it) {
        (*it).draw(VP);
    }
}

template <typename Type> void check_enemy(list <Type> &l) {
    float top    = screen_center_y + 30 / screen_zoom;
    float bottom = screen_center_y - 30 / screen_zoom;
    float left   = screen_center_x - 30 / screen_zoom;
    float right  = screen_center_x + 30 / screen_zoom;
    typename list <Type> :: iterator it;
    for(it = l.begin() ; it != l.end() ; ++it) {
        glm::mat4 VP = glm::ortho(left, right, bottom, top, 0.0f, 500.0f) * Matrices.view;
        glm::vec3 loc = (*it).locationScreen(VP);
        if(glm::dot(loc,loc) < 0.3f) {
            tg[(*it).arg] = true;
            dash.setCrosshair(true);
            air.setTarget((void *)(&(*it)),(*it).arg);
            return;
        }
    }
    return;
}

template <typename Type> void add_sprite(list <Type> &l, int seed, glm::vec3 top, glm::vec3 bottom, int limit) {
    int ran = random()%seed;
    if(ran == 0 && l.size() < limit ) {
        float x = bottom.x + XOR()%( (int)(top.x - bottom.x + 1) );
        float y = bottom.y + XOR()%( (int)(top.y - bottom.y + 1) );
        float z = bottom.z + XOR()%( (int)(top.z - bottom.z + 1) );
        l.push_back(Type(x,y,z));
    }
}

template <typename Type> void clear_lists(list <Type> &l) {
    typename list <Type> :: iterator it;
    for(it = l.begin() ; it != l.end() ;) {
        glm::vec3 dist = (*it).position - air.position;
        if(sqrt(glm::dot(dist, dist)) > 10000 || (*it).kill) {
            l.erase(it++);
        }
        else{
            it++;
        }
    }
}


template <typename Type1, typename Type2> void check_collision(list <Type1> &a, list <Type2> &b) {
    typename list <Type1> :: iterator it1;
    typename list <Type2> :: iterator it2;
    for(it1  = a.begin() ; it1 != a.end() ; it1++) {
        for(it2 = b.begin() ; it2 != b.end() ; it2++) {
            if(!checkCollision((*it1).bounding, (*it1).rotate, (*it2).bounding, (*it2).rotate)) {
                (*it1).kill = true;
                (*it2).kill = true;
            }
        }
    }
}


Timer t60(1.0 / 60);

glm::vec3 eye[6];
glm::vec3 up[6];
glm::vec3 target[6];
clock_t ts;

void draw() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram (programID);

    eye[0] = air.position - 40.0f*air.dir + 20.0f*air.up;
    eye[1] = air.position + glm::vec3(0,100.0f,0);

    up[0] = air.up;
    up[1] = glm::vec3(0,0,-1);
    up[2] = glm::vec3(0,1,0);
    target[2] = air.position;

    target[0] = air.position;
    target[1] = air.position + air.up * 10.0f;
    // glm::vec3 target = air.position ;
    


    // glm::vec3 testTarget = r.position;
    glm::vec3 testEye = glm::vec3(100,100,100);
    glm::vec3 testUp = glm::vec3(0,0,-1);

    // Matrices.view = glm::lookAt( testEye, testTarget, testUp ); // Rotating Camera for 3D

    Matrices.view = glm::lookAt( eye[flag], target[flag], up[flag] ); // Rotating Camera for 3D
    glm::mat4 VP = Matrices.projection * Matrices.view;
   
    tg[0] = tg[1] = false;
    check_enemy(es);
    check_enemy(ps);
    if(tg[0] == false) {
        air.target = NULL;
    }
    if(tg[1] == false) {
        air.etarget = NULL;
    }
    dash.setCrosshair(tg[0] || tg[1]);

    glm::mat4 MVP;  // MVP = Projection * View * Model

    st.draw(VP);
    air.draw(VP);
    sky.draw(VP);
    c.draw(VP);
    a.draw(VP);
    dash.draw(VP);
    draw_sprite(ms, VP);
    draw_sprite(es, VP);
    draw_sprite(ps, VP);
    draw_sprite(bs, VP);
    draw_sprite(bms, VP);
    draw_sprite(vs, VP);
    draw_sprite(fs, VP);
    draw_sprite(rs, VP);
    draw_sprite(ss, VP);    

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int u = glfwGetKey(window, GLFW_KEY_X);
    int f = glfwGetKey(window, GLFW_KEY_Z);
    int c = glfwGetKey(window, GLFW_KEY_C);
    int sp = glfwGetKey(window, GLFW_KEY_SPACE);
    int b = glfwGetKey(window, GLFW_KEY_B);
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    float theta, phi, radius;
    phi = -(M_PI * (xpos - 500)/1000)/2;
    theta = -(M_PI * (ypos - 500)/1000)/2; 
    radius = 40.0f;
    eye[2] = air.position + radius * glm::vec3(cos(theta) * cos(phi), sin(theta), cos(theta) * sin(phi));

    // std::cout << xpos << " " << ypos << std::endl;
    if (u) {
        flag = 0;
    }
    if(f) {
        flag = 1;
    }
    if(c) {
        flag = 2;
    }
}

void tick_elements(GLFWwindow *window) {
    air.tick(window);
    st.tick();
    dash.tick(air);
    
    tick_sprite(ps);
    tick_sprite(ms);
    tick_sprite(bs);
    tick_sprite(es);
    tick_sprite(bms);

    check_collision(ms, ps);
    check_collision(ms, es);


    clear_lists(ps);
    clear_lists(ms);
    clear_lists(bs);
    clear_lists(es);
    clear_lists(bms);
    clear_lists(vs);
    clear_lists(fs);
    clear_lists(rs);
    // clear_lists(ss);




    c.tick();
    add_sprite(ps, 100, glm::vec3(200,200,200) + air.position, glm::vec3(-200,-200,-200) + air.position, 100);
    add_sprite(vs, 200, air.position + glm::vec3(200,-air.position.y,200), air.position + glm::vec3(-200,-air.position.y,-200), 10);
    add_sprite(es, 100, air.position + glm::vec3(400,400,400), air.position + glm::vec3(200,200,200), 100);
    add_sprite(fs, 100, air.position + glm::vec3(400,400,400), air.position + glm::vec3(200,200,200), 100);
    add_sprite(rs, 100, air.position + glm::vec3(400,400,400), air.position + glm::vec3(200,200,200), 100);

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    air         = Airplane(0,20.0f,1.0f,1.0f,1.0f,5.0f,30,COLOR_GREEN);
    sky         = Cuboid(0, 0, 0, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1.0f,COLOR_BLACK);
    st          = STerrain(0,0,513,COLOR_RED);
    a           = Arrow(200,200,200);
    c           = Canon(200,200,200, &air);
    dash        = Dashboard(0,0,0);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

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
    ts = clock();
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
