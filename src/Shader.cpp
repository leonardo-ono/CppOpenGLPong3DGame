#include <glad/glad.h>
#include "Shader.h"

#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

Shader::Shader()
{
    //ctor
    create();
}

Shader::~Shader()
{
    //dtor
}

void Shader::create()
{
    program = glCreateProgram();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const std::string vertexShaderSource =
        "#version 130\n"
        "uniform mat4 model;\n"
        "uniform mat4 viewProjection;\n"
        "uniform vec4 color;\n"
        "in vec4 position;\n"
        "in vec3 normal;\n"
        "out vec4 sNormal;\n"
        "out vec4 sColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = viewProjection * model * position;\n"
        "   sNormal = model * vec4(normal, 0.0);\n"
        "   sColor = color;\n"
        "}\n";

    const std::string fragmentShaderSource =
        "#version 130\n"
        "in vec4 sColor;\n"
        "in vec4 sNormal;\n"
        "out vec4 fragColor;"
        "void main()\n"
        "{\n"
        "   vec4 normal = normalize(sNormal);\n"
        "   vec4 lightDirection = vec4(-1.0, 0.85, 1.0, 0.0);\n"
        "   float diffuse = 0.9 * max(dot(normal, lightDirection), 0.0);\n"
        "   float ambient = 0.1;\n"
        "   fragColor = (ambient + diffuse) * sColor;\n"
        "}\n";

    const char* vss = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vss, NULL);
    glCompileShader(vertexShader);

    const char* fss = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fss, NULL);
    glCompileShader(fragmentShader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    vmodel_location = glGetUniformLocation(program, "model");
    vviewProjection_location = glGetUniformLocation(program, "viewProjection");
    vpos_location = glGetAttribLocation(program, "position");
    vnormal_location = glGetAttribLocation(program, "normal");
    vcolor_location = glGetUniformLocation(program, "color");
}

void Shader::use()
{
    glUseProgram(program);
}
