#ifndef MESH_H
#define MESH_H

#include "Shader.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera;

class Ball
{
    public:
        Ball(Shader* s);
        ~Ball();
        void update();
        void render(Camera* camera);

    private:
        void create();

    public:
        glm::vec2 velocity;
        glm::vec2 position;

    private:
        Shader* shader;
        GLuint buffer;
        int elementsPerVertex;
        int vertexCount;
        float angleX;
        glm::mat4 modelTransformation;
        glm::mat4 viewProjectionTransformation;
};

#endif // MESH_H
