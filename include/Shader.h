#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
    public:
        Shader();
        ~Shader();
        void create();
        void use();

    public:
        GLint vmodel_location;
        GLint vviewProjection_location;
        GLint vpos_location;
        GLint vnormal_location;
        GLint vcolor_location;

    private:
        GLuint program;
        GLuint vertexShader;
        GLuint fragmentShader;
};

#endif // SHADER_H
