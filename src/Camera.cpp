#include "../include/Camera.hpp"


Camera::Camera(int imageWidth, int imageHeight, float fovDegrees)
    : width(imageWidth), height(imageHeight), fieldOfView(fovDegrees), origin(0.0f, 0.0f, 0.0f)
{
    aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    float theta = glm::radians(fieldOfView);
    float viewportHeight = 2.0f * tan(theta / 2.0f);
    float viewportWidth = aspectRatio * viewportHeight;

    horizontal = glm::vec3(viewportWidth, 0.0f, 0.0f);
    vertical = glm::vec3(0.0f, viewportHeight, 0.0f);
    lowerLeftCorner = origin - horizontal * 0.5f - vertical * 0.5f - glm::vec3(0, 0, 1.0f);
}

Camera::Ray Camera::getRay(int pixelX, int pixelY) const {
    float u = static_cast<float>(pixelX) / (width - 1);
    float v = static_cast<float>(pixelY) / (height - 1);
    glm::vec3 direction = lowerLeftCorner + u * horizontal + v * vertical - origin;
    return Ray(origin, direction);
}
