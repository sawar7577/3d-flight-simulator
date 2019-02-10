#include "cuboid.h"
#include "main.h"

std::vector <glm::vec3> getAxis(Cuboid A, glm::mat4 rotateA);
bool checkCollision(Cuboid A, glm::mat4 rotateA, Cuboid B, glm::mat4 rotateB);
bool checkAxis(glm::vec3 axis, Cuboid A, glm::mat4 rotateA, Cuboid B, glm::mat4 rotateB);
float getProjection(glm::vec3 axis, glm::vec3 point);


bool checkCollision(Cuboid A, glm::mat4 rotateA, Cuboid B, glm::mat4 rotateB) {

    std::vector <glm::vec3> axisA, axisB;
    axisA = getAxis(A, rotateA);
    axisA = getAxis(B, rotateB);
    for(int i = 0 ; i < axisA.size() ; ++i) {
        if(checkAxis(axisA[i], A, rotateA, B, rotateB)){
            return true;
        }
    }

    for(int i = 0 ; i < axisB.size() ; ++i) {
        if(checkAxis(axisB[i], A, rotateA, B, rotateB)){
            return true;
        }
    }

    for(int i = 0 ; i < axisA.size() ; ++i) {
        for(int j = 0 ; j < axisB.size() ; ++j) {
            if(checkAxis(glm::cross(axisA[i],axisB[j]), A, rotateA, B, rotateB)){
                return true;
            }
        }
    }
    return false;
}

bool checkAxis(glm::vec3 axis, Cuboid A, glm::mat4 rotateA, Cuboid B, glm::mat4 rotateB) {
    std::pair <float, float> rangeA;
    std::pair <float, float> rangeB;
    glm::vec3 pointA, pointB;


    pointA = glm::vec3(glm::translate(A.position) * rotateA * glm::vec4(0,0,0,1));
    pointB = glm::vec3(glm::translate(B.position) * rotateB * glm::vec4(1,1,1,1));
    std::cout << " A " << pointA.x << " " << pointA.y << " " << pointA.z << std::endl;
    std::cout << " B " << pointB.x << " " << pointB.y << " " << pointB.z << std::endl;

    std::cout << "B" << std::endl;
    for(int i = 0 ; i < 3 ; ++i) {
        for(int j = 0 ; j < 3; ++j) {
            std::cout << rotateB[i][j] << " ";
        }
        std::cout << std::endl;
    }


    if(
        abs(glm::dot( glm::vec3(glm::translate(B.position) * rotateB * glm::vec4(0,0,0,1)) - glm::vec3(glm::translate(A.position) * rotateA * glm::vec4(0,0,0,1)), axis)) 
                                > abs(glm::dot( (A.length1/2)*glm::vec3(rotateA[0][0], rotateA[0][1], rotateA[0][2]), axis)) 
                                + abs(glm::dot( (A.height/2)*glm::vec3(rotateA[1][0], rotateA[1][1], rotateA[1][2]), axis)) 
                                + abs(glm::dot( (A.breadth1/2)*glm::vec3(rotateA[2][0], rotateA[2][1], rotateA[2][2]), axis))
                                + abs(glm::dot( (B.length1/2)*glm::vec3(rotateB[0][0], rotateB[0][1], rotateB[0][2]), axis))
                                + abs(glm::dot( (B.height/2)*glm::vec3(rotateB[1][0], rotateB[1][1], rotateB[1][2]), axis))
                                + abs(glm::dot( (B.breadth1/2)*glm::vec3(rotateB[2][0], rotateB[2][1], rotateB[2][2]), axis)) 
                                
    ) {
        return true;
    }    
    return false;

}


std::vector <glm::vec3> getAxis(Cuboid A, glm::mat4 rotateA) {
    std::vector <glm::vec3> ans;
    ans.push_back(glm::vec3(rotateA * glm::vec4(1,0,0,1)));
    ans.push_back(glm::vec3(rotateA * glm::vec4(0,1,0,1)));
    ans.push_back(glm::vec3(rotateA * glm::vec4(0,0,1,1)));
    return ans;
}