#pragma once
#include <glm/glm.hpp>
#include <cmath>

class Camera{
public:
    struct Ray{
        glm::vec3 origin;
        glm::vec3 direction;
        Ray(const glm::vec3& o,const glm::vec3 d) : origin(o), direction(glm::normalize (d)) {}
    };
    
    Camera(int imageWidth, int imageHeight, float fieldOfViewDegrees);
    
    Ray getRay(int pixelX, int pixelY) const;
    
private:
    int width;
    int height;
    float aspectRatio;
    float fieldOfView;
    glm::vec3 origin;
    glm::vec3 lowerLeftCorner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
};
