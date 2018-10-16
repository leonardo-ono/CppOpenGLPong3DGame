#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <math.h>

#include "Table.h"

Table::Table(Shader* s)
{
    //ctor
    shader = s;
    create();
}

Table::~Table()
{
    //dtor
}

void Table::create()
{
	GLfloat vertices[] = {
		-31.0f, 2.0f, -80.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-31.0f, 0.0f, -80.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-31.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,

		-29.0f, 2.0f, -80.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-29.0f, 0.0f, -80.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-31.0f, 0.0f, -80.0f, 1.0f, 0.0f, 0.0f, -1.0f,

		-29.0f, 2.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-29.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-29.0f, 0.0f, -80.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-31.0f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-31.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-29.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		-31.0f, 0.0f, -80.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		-29.0f, 0.0f, -80.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		-29.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

		-29.0f, 2.0f, -80.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-31.0f, 2.0f, -80.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-31.0f, 2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

		-31.0f, 2.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-31.0f, 2.0f, -80.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-31.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,

		-31.0f, 2.0f, -80.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-29.0f, 2.0f, -80.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-31.0f, 0.0f, -80.0f, 1.0f, 0.0f, 0.0f, -1.0f,

		-29.0f, 2.0f, -80.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-29.0f, 2.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-29.0f, 0.0f, -80.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-29.0f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-31.0f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-29.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		-31.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		-31.0f, 0.0f, -80.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		-29.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

		-29.0f, 2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-29.0f, 2.0f, -80.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-31.0f, 2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

		29.0f, 2.0f, -80.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		29.0f, 0.0f, -80.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		29.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,

		31.0f, 2.0f, -80.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		31.0f, 0.0f, -80.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		29.0f, 0.0f, -80.0f, 1.0f, 0.0f, 0.0f, -1.0f,

		31.0f, 2.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		31.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		31.0f, 0.0f, -80.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		29.0f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		29.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		31.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		29.0f, 0.0f, -80.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		31.0f, 0.0f, -80.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		31.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

		31.0f, 2.0f, -80.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		29.0f, 2.0f, -80.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		29.0f, 2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

		29.0f, 2.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		29.0f, 2.0f, -80.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		29.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,

		29.0f, 2.0f, -80.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		31.0f, 2.0f, -80.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		29.0f, 0.0f, -80.0f, 1.0f, 0.0f, 0.0f, -1.0f,

		31.0f, 2.0f, -80.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		31.0f, 2.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		31.0f, 0.0f, -80.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		31.0f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		29.0f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		31.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		29.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		29.0f, 0.0f, -80.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		31.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

		31.0f, 2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		31.0f, 2.0f, -80.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		29.0f, 2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

		30.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		30.0f, 0.0f, -80.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-30.0f, 0.0f, -80.0f, 1.0f, 0.0f, 1.0f, 0.0f,

		-30.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		30.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-30.0f, 0.0f, -80.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};

    elementsPerVertex = 7;
    vertexCount = sizeof(vertices) / sizeof(GLfloat) / elementsPerVertex;

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Table::update()
{
    modelTransformation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    // modelTransformation = glm::rotate(modelTransformation, (float) glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
}

void Table::render(Camera* camera)
{
    shader->use();
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glUniform4f(shader->vcolor_location, 0.7f, 0.7f, 1.0f, 1.0f);

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
