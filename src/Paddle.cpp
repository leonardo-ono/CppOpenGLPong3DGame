#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <math.h>
#include <cmath>
#include <stdlib.h>

#include "Paddle.hpp"

Paddle::Paddle(GLFWwindow* w, bool isCpuSet, Shader* s, Ball* b)
{
    //ctor
    window = w;
    isCpu = isCpuSet;
    shader = s;
    ball = b;
    create();
}

Paddle::~Paddle()
{
    //dtor
}

void Paddle::create()
{
	GLfloat vertices[] = {
		-4.0f, 1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-4.0f, -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-4.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,

		4.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		4.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-4.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f,

		4.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		4.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		4.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-4.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-4.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		4.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		-4.0f, -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		4.0f, -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		4.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,

		4.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-4.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-4.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

		-4.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-4.0f, 1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-4.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,

		-4.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		4.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-4.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f,

		4.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		4.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		4.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		4.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-4.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		4.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		-4.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		-4.0f, -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		4.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,

		4.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		4.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-4.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};

    elementsPerVertex = 7;
    vertexCount = sizeof(vertices) / sizeof(GLfloat) / elementsPerVertex;

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Paddle::update()
{
    if (isCpu)
    {
        updateCPU();
    }
    else
    {
        updatePlayer();
    }
    position = glm::clamp(position, glm::vec2(-25.0f, 0.0f), glm::vec2(25.0f, 0.0f));
    float z = isCpu ? -79.0f : -1.0f;
    modelTransformation = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, 1.0f, z));
    // modelTransformation = glm::rotate(modelTransformation, (float) glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
}

void Paddle::updateCPU()
{
    position.x = ball->position.x;
}

void Paddle::updatePlayer()
{
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        position.x -= 1;
        //std::cout << position.x << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        position.x += 1;
        //std::cout << position.x << std::endl;
    }
}

void Paddle::render(Camera* camera)
{
    shader->use();
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glUniform4f(shader->vcolor_location, 0.0f, 0.0f, 1.0f, 1.0f);

    viewProjectionTransformation = camera->perspectiveTransformation * camera->cameraTransformation;

    glUniformMatrix4fv(shader->vmodel_location, 1, GL_FALSE, &modelTransformation[0][0]);
    glUniformMatrix4fv(shader->vviewProjection_location, 1, GL_FALSE, &viewProjectionTransformation[0][0]);

    glEnableVertexAttribArray(shader->vpos_location);
    glVertexAttribPointer(shader->vpos_location, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * elementsPerVertex, (void*) 0);

    glEnableVertexAttribArray(shader->vnormal_location);
    glVertexAttribPointer(shader->vnormal_location, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * elementsPerVertex, (void*) (sizeof(GLfloat) * 4));

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glDisableVertexAttribArray(shader->vpos_location);
}

void Paddle::checkCollision()
{
    if (std::abs(position.x - ball->position.x) > 5) {
        return;
    }

    float randomNumber = rand() / (float) RAND_MAX;
    if (isCpu) {
        if (ball->position.y < -76 && ball->position.y > -78)
        {
            ball->velocity.x = 2 * randomNumber - 1;
            ball->velocity.y *= -1.05;
        }
    }
    else {
        if (ball->position.y < -1 && ball->position.y > -3)
        {
            ball->velocity.x = 2 * randomNumber - 1;
            ball->velocity.y *= -1.05;
        }
    }
}
