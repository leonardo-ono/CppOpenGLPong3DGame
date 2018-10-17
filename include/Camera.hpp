#ifndef CAMERA_H
#define CAMERA_H

#include "Ball.hpp"

class Camera
{
    public:
        Camera(Ball* b);
        ~Camera();
        void update();

    public:
        Ball* ball;
        glm::mat4 perspectiveTransformation;
        glm::mat4 cameraTransformation;
};

#endif // CAMERA_H
