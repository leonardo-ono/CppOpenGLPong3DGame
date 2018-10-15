#include "Camera.h"

Camera::Camera(Ball* b)
{
    //ctor
    ball = b;
    perspectiveTransformation = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 1000.0f);
}

Camera::~Camera()
{
    //dtor
}

void Camera::update()
{
    float cameraX = -ball->position.x * 0.05;
    float cameraZ = -ball->position.y * 0.05 - 60.0f;
    float cameraRotationY = -ball->position.x * 0.001;
    cameraTransformation = glm::translate(glm::mat4(1.0f), glm::vec3(cameraX, -20.0f, cameraZ));
    cameraTransformation = glm::rotate(cameraTransformation, glm::radians(40.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    cameraTransformation = glm::rotate(cameraTransformation, cameraRotationY, glm::vec3(0.0f, 1.0f, 0.0f));
}
