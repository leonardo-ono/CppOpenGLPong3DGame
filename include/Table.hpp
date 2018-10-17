#ifndef TABLE_H
#define TABLE_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Shader.hpp"
#include "Camera.hpp"

class Table
{
    public:
        Table(Shader* s);
        ~Table();
        void update();
        void render(Camera* camera);

    private:
        void create();

    private:
        Shader* shader;
        GLuint buffer;
        int elementsPerVertex;
        int vertexCount;
        glm::mat4 modelTransformation;
        glm::mat4 viewProjectionTransformation;
};

#endif // TABLE_H
