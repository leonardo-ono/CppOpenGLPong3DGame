#ifndef TABLE_H
#define TABLE_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Shader.h"
#include "Camera.h"

class Table
{
    public:
        Table();
        ~Table();
        void create(Shader* s);
        void update();
        void render(Camera* camera);

    private:
        Shader* shader;
        GLuint buffer;
        int elementsPerVertex;
        int vertexCount;
        glm::mat4 modelTransformation;
        glm::mat4 viewProjectionTransformation;
};

#endif // TABLE_H
