#ifndef PADDLE_H
#define PADDLE_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Shader.hpp"
#include "Ball.hpp"
#include "Camera.hpp"

class Paddle
{
    public:
        Paddle(GLFWwindow* w, bool isCpuSet, Shader* s, Ball* ball);
        ~Paddle();
        void update();
        void render(Camera* camera);
        void checkCollision();

    private:
        void create();
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
