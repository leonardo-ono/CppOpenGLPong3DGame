#ifndef PADDLE_H
#define PADDLE_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Shader.h"
#include "Ball.h"
#include "Camera.h"

class Paddle
{
    public:
        Paddle();
        ~Paddle();
        void create(GLFWwindow* w, bool isCpuSet, Shader* s, Ball* ball);
        void update();
        void render(Camera* camera);
        void checkCollision();

    private:
        void updateCPU();
        void updatePlayer();

    private:
        GLFWwindow* window;
        bool isCpu;
        Shader* shader;
        Ball* ball;
        GLuint buffer;
        int elementsPerVertex;
        int vertexCount;
        glm::mat4 modelTransformation;
        glm::mat4 viewProjectionTransformation;
        glm::vec2 position;
};

#endif // PADDLE_H
