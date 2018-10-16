#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <math.h>
#include <cmath>
#include <iostream>
#include "Ball.h"
#include "Camera.h"

Ball::Ball(Shader* s)
{
    //ctor
    shader = s;
    velocity.x = 1;
    velocity.y = -0.5;
    position.y = -40;
    angleX = 0.0f;
    create();
}

Ball::~Ball()
{
    //dtor
}

void Ball::create()
{
	GLfloat vertices[] = {
		0.0f, -1.0f, 0.0f, 1.0f, 0.1024f, -0.9435f, 0.3151f,
		0.425323f, -0.850654f, 0.309011f, 1.0f, 0.1024f, -0.9435f, 0.3151f,
		-0.162456f, -0.850654f, 0.499995f, 1.0f, 0.1024f, -0.9435f, 0.3151f,

		0.723607f, -0.44722f, 0.525725f, 1.0f, 0.7002f, -0.6617f, 0.268f,
		0.425323f, -0.850654f, 0.309011f, 1.0f, 0.7002f, -0.6617f, 0.268f,
		0.850648f, -0.525736f, 0.0f, 1.0f, 0.7002f, -0.6617f, 0.268f,

		0.0f, -1.0f, 0.0f, 1.0f, -0.268f, -0.9435f, 0.1947f,
		-0.162456f, -0.850654f, 0.499995f, 1.0f, -0.268f, -0.9435f, 0.1947f,
		-0.52573f, -0.850652f, 0.0f, 1.0f, -0.268f, -0.9435f, 0.1947f,

		0.0f, -1.0f, 0.0f, 1.0f, -0.268f, -0.9435f, -0.1947f,
		-0.52573f, -0.850652f, 0.0f, 1.0f, -0.268f, -0.9435f, -0.1947f,
		-0.162456f, -0.850654f, -0.499995f, 1.0f, -0.268f, -0.9435f, -0.1947f,

		0.0f, -1.0f, 0.0f, 1.0f, 0.1024f, -0.9435f, -0.3151f,
		-0.162456f, -0.850654f, -0.499995f, 1.0f, 0.1024f, -0.9435f, -0.3151f,
		0.425323f, -0.850654f, -0.309011f, 1.0f, 0.1024f, -0.9435f, -0.3151f,

		0.723607f, -0.44722f, 0.525725f, 1.0f, 0.905f, -0.3304f, 0.268f,
		0.850648f, -0.525736f, 0.0f, 1.0f, 0.905f, -0.3304f, 0.268f,
		0.951058f, 0.0f, 0.309013f, 1.0f, 0.905f, -0.3304f, 0.268f,

		-0.276388f, -0.44722f, 0.850649f, 1.0f, 0.0247f, -0.3304f, 0.9435f,
		0.262869f, -0.525738f, 0.809012f, 1.0f, 0.0247f, -0.3304f, 0.9435f,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0247f, -0.3304f, 0.9435f,

		-0.894426f, -0.447216f, 0.0f, 1.0f, -0.8897f, -0.3304f, 0.3151f,
		-0.688189f, -0.525736f, 0.499997f, 1.0f, -0.8897f, -0.3304f, 0.3151f,
		-0.951058f, 0.0f, 0.309013f, 1.0f, -0.8897f, -0.3304f, 0.3151f,

		-0.276388f, -0.44722f, -0.850649f, 1.0f, -0.5746f, -0.3304f, -0.7488f,
		-0.688189f, -0.525736f, -0.499997f, 1.0f, -0.5746f, -0.3304f, -0.7488f,
		-0.587786f, 0.0f, -0.809017f, 1.0f, -0.5746f, -0.3304f, -0.7488f,

		0.723607f, -0.44722f, -0.525725f, 1.0f, 0.5346f, -0.3304f, -0.7779f,
		0.262869f, -0.525738f, -0.809012f, 1.0f, 0.5346f, -0.3304f, -0.7779f,
		0.587786f, 0.0f, -0.809017f, 1.0f, 0.5346f, -0.3304f, -0.7779f,

		0.723607f, -0.44722f, 0.525725f, 1.0f, 0.8026f, -0.1256f, 0.5831f,
		0.951058f, 0.0f, 0.309013f, 1.0f, 0.8026f, -0.1256f, 0.5831f,
		0.587786f, 0.0f, 0.809017f, 1.0f, 0.8026f, -0.1256f, 0.5831f,

		-0.276388f, -0.44722f, 0.850649f, 1.0f, -0.3066f, -0.1256f, 0.9435f,
		0.0f, 0.0f, 1.0f, 1.0f, -0.3066f, -0.1256f, 0.9435f,
		-0.587786f, 0.0f, 0.809017f, 1.0f, -0.3066f, -0.1256f, 0.9435f,

		-0.894426f, -0.447216f, 0.0f, 1.0f, -0.9921f, -0.1256f, 0.0f,
		-0.951058f, 0.0f, 0.309013f, 1.0f, -0.9921f, -0.1256f, 0.0f,
		-0.951058f, 0.0f, -0.309013f, 1.0f, -0.9921f, -0.1256f, 0.0f,

		-0.276388f, -0.44722f, -0.850649f, 1.0f, -0.3066f, -0.1256f, -0.9435f,
		-0.587786f, 0.0f, -0.809017f, 1.0f, -0.3066f, -0.1256f, -0.9435f,
		0.0f, 0.0f, -1.0f, 1.0f, -0.3066f, -0.1256f, -0.9435f,

		0.723607f, -0.44722f, -0.525725f, 1.0f, 0.8026f, -0.1256f, -0.5831f,
		0.587786f, 0.0f, -0.809017f, 1.0f, 0.8026f, -0.1256f, -0.5831f,
		0.951058f, 0.0f, -0.309013f, 1.0f, 0.8026f, -0.1256f, -0.5831f,

		0.276388f, 0.44722f, 0.850649f, 1.0f, 0.4089f, 0.6617f, 0.6284f,
		0.688189f, 0.525736f, 0.499997f, 1.0f, 0.4089f, 0.6617f, 0.6284f,
		0.162456f, 0.850654f, 0.499995f, 1.0f, 0.4089f, 0.6617f, 0.6284f,

		-0.723607f, 0.44722f, 0.525725f, 1.0f, -0.4713f, 0.6617f, 0.5831f,
		-0.262869f, 0.525738f, 0.809012f, 1.0f, -0.4713f, 0.6617f, 0.5831f,
		-0.425323f, 0.850654f, 0.309011f, 1.0f, -0.4713f, 0.6617f, 0.5831f,

		-0.723607f, 0.44722f, -0.525725f, 1.0f, -0.7002f, 0.6617f, -0.268f,
		-0.850648f, 0.525736f, 0.0f, 1.0f, -0.7002f, 0.6617f, -0.268f,
		-0.425323f, 0.850654f, -0.309011f, 1.0f, -0.7002f, 0.6617f, -0.268f,

		0.276388f, 0.44722f, -0.850649f, 1.0f, 0.0385f, 0.6617f, -0.7488f,
		-0.262869f, 0.525738f, -0.809012f, 1.0f, 0.0385f, 0.6617f, -0.7488f,
		0.162456f, 0.850654f, -0.499995f, 1.0f, 0.0385f, 0.6617f, -0.7488f,

		0.894426f, 0.447216f, 0.0f, 1.0f, 0.724f, 0.6617f, -0.1947f,
		0.688189f, 0.525736f, -0.499997f, 1.0f, 0.724f, 0.6617f, -0.1947f,
		0.52573f, 0.850652f, 0.0f, 1.0f, 0.724f, 0.6617f, -0.1947f,

		0.52573f, 0.850652f, 0.0f, 1.0f, 0.268f, 0.9435f, -0.1947f,
		0.162456f, 0.850654f, -0.499995f, 1.0f, 0.268f, 0.9435f, -0.1947f,
		0.0f, 1.0f, 0.0f, 1.0f, 0.268f, 0.9435f, -0.1947f,

		0.52573f, 0.850652f, 0.0f, 1.0f, 0.4911f, 0.7947f, -0.3568f,
		0.688189f, 0.525736f, -0.499997f, 1.0f, 0.4911f, 0.7947f, -0.3568f,
		0.162456f, 0.850654f, -0.499995f, 1.0f, 0.4911f, 0.7947f, -0.3568f,

		0.688189f, 0.525736f, -0.499997f, 1.0f, 0.4089f, 0.6617f, -0.6284f,
		0.276388f, 0.44722f, -0.850649f, 1.0f, 0.4089f, 0.6617f, -0.6284f,
		0.162456f, 0.850654f, -0.499995f, 1.0f, 0.4089f, 0.6617f, -0.6284f,

		0.162456f, 0.850654f, -0.499995f, 1.0f, -0.1024f, 0.9435f, -0.3151f,
		-0.425323f, 0.850654f, -0.309011f, 1.0f, -0.1024f, 0.9435f, -0.3151f,
		0.0f, 1.0f, 0.0f, 1.0f, -0.1024f, 0.9435f, -0.3151f,

		0.162456f, 0.850654f, -0.499995f, 1.0f, -0.1876f, 0.7947f, -0.5773f,
		-0.262869f, 0.525738f, -0.809012f, 1.0f, -0.1876f, 0.7947f, -0.5773f,
		-0.425323f, 0.850654f, -0.309011f, 1.0f, -0.1876f, 0.7947f, -0.5773f,

		-0.262869f, 0.525738f, -0.809012f, 1.0f, -0.4713f, 0.6617f, -0.5831f,
		-0.723607f, 0.44722f, -0.525725f, 1.0f, -0.4713f, 0.6617f, -0.5831f,
		-0.425323f, 0.850654f, -0.309011f, 1.0f, -0.4713f, 0.6617f, -0.5831f,

		-0.425323f, 0.850654f, -0.309011f, 1.0f, -0.3313f, 0.9435f, 0.0f,
		-0.425323f, 0.850654f, 0.309011f, 1.0f, -0.3313f, 0.9435f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f, -0.3313f, 0.9435f, 0.0f,

		-0.425323f, 0.850654f, -0.309011f, 1.0f, -0.6071f, 0.7947f, 0.0f,
		-0.850648f, 0.525736f, 0.0f, 1.0f, -0.6071f, 0.7947f, 0.0f,
		-0.425323f, 0.850654f, 0.309011f, 1.0f, -0.6071f, 0.7947f, 0.0f,

		-0.850648f, 0.525736f, 0.0f, 1.0f, -0.7002f, 0.6617f, 0.268f,
		-0.723607f, 0.44722f, 0.525725f, 1.0f, -0.7002f, 0.6617f, 0.268f,
		-0.425323f, 0.850654f, 0.309011f, 1.0f, -0.7002f, 0.6617f, 0.268f,

		-0.425323f, 0.850654f, 0.309011f, 1.0f, -0.1024f, 0.9435f, 0.3151f,
		0.162456f, 0.850654f, 0.499995f, 1.0f, -0.1024f, 0.9435f, 0.3151f,
		0.0f, 1.0f, 0.0f, 1.0f, -0.1024f, 0.9435f, 0.3151f,

		-0.425323f, 0.850654f, 0.309011f, 1.0f, -0.1876f, 0.7947f, 0.5773f,
		-0.262869f, 0.525738f, 0.809012f, 1.0f, -0.1876f, 0.7947f, 0.5773f,
		0.162456f, 0.850654f, 0.499995f, 1.0f, -0.1876f, 0.7947f, 0.5773f,

		-0.262869f, 0.525738f, 0.809012f, 1.0f, 0.0385f, 0.6617f, 0.7488f,
		0.276388f, 0.44722f, 0.850649f, 1.0f, 0.0385f, 0.6617f, 0.7488f,
		0.162456f, 0.850654f, 0.499995f, 1.0f, 0.0385f, 0.6617f, 0.7488f,

		0.162456f, 0.850654f, 0.499995f, 1.0f, 0.268f, 0.9435f, 0.1947f,
		0.52573f, 0.850652f, 0.0f, 1.0f, 0.268f, 0.9435f, 0.1947f,
		0.0f, 1.0f, 0.0f, 1.0f, 0.268f, 0.9435f, 0.1947f,

		0.162456f, 0.850654f, 0.499995f, 1.0f, 0.4911f, 0.7947f, 0.3568f,
		0.688189f, 0.525736f, 0.499997f, 1.0f, 0.4911f, 0.7947f, 0.3568f,
		0.52573f, 0.850652f, 0.0f, 1.0f, 0.4911f, 0.7947f, 0.3568f,

		0.688189f, 0.525736f, 0.499997f, 1.0f, 0.724f, 0.6617f, 0.1947f,
		0.894426f, 0.447216f, 0.0f, 1.0f, 0.724f, 0.6617f, 0.1947f,
		0.52573f, 0.850652f, 0.0f, 1.0f, 0.724f, 0.6617f, 0.1947f,

		0.951058f, 0.0f, -0.309013f, 1.0f, 0.8897f, 0.3304f, -0.3151f,
		0.688189f, 0.525736f, -0.499997f, 1.0f, 0.8897f, 0.3304f, -0.3151f,
		0.894426f, 0.447216f, 0.0f, 1.0f, 0.8897f, 0.3304f, -0.3151f,

		0.951058f, 0.0f, -0.309013f, 1.0f, 0.7947f, 0.1876f, -0.5773f,
		0.587786f, 0.0f, -0.809017f, 1.0f, 0.7947f, 0.1876f, -0.5773f,
		0.688189f, 0.525736f, -0.499997f, 1.0f, 0.7947f, 0.1876f, -0.5773f,

		0.587786f, 0.0f, -0.809017f, 1.0f, 0.5746f, 0.3304f, -0.7488f,
		0.276388f, 0.44722f, -0.850649f, 1.0f, 0.5746f, 0.3304f, -0.7488f,
		0.688189f, 0.525736f, -0.499997f, 1.0f, 0.5746f, 0.3304f, -0.7488f,

		0.0f, 0.0f, -1.0f, 1.0f, -0.0247f, 0.3304f, -0.9435f,
		-0.262869f, 0.525738f, -0.809012f, 1.0f, -0.0247f, 0.3304f, -0.9435f,
		0.276388f, 0.44722f, -0.850649f, 1.0f, -0.0247f, 0.3304f, -0.9435f,

		0.0f, 0.0f, -1.0f, 1.0f, -0.3035f, 0.1876f, -0.9342f,
		-0.587786f, 0.0f, -0.809017f, 1.0f, -0.3035f, 0.1876f, -0.9342f,
		-0.262869f, 0.525738f, -0.809012f, 1.0f, -0.3035f, 0.1876f, -0.9342f,

		-0.587786f, 0.0f, -0.809017f, 1.0f, -0.5346f, 0.3304f, -0.7779f,
		-0.723607f, 0.44722f, -0.525725f, 1.0f, -0.5346f, 0.3304f, -0.7779f,
		-0.262869f, 0.525738f, -0.809012f, 1.0f, -0.5346f, 0.3304f, -0.7779f,

		-0.951058f, 0.0f, -0.309013f, 1.0f, -0.905f, 0.3304f, -0.268f,
		-0.850648f, 0.525736f, 0.0f, 1.0f, -0.905f, 0.3304f, -0.268f,
		-0.723607f, 0.44722f, -0.525725f, 1.0f, -0.905f, 0.3304f, -0.268f,

		-0.951058f, 0.0f, -0.309013f, 1.0f, -0.9822f, 0.1876f, 0.0f,
		-0.951058f, 0.0f, 0.309013f, 1.0f, -0.9822f, 0.1876f, 0.0f,
		-0.850648f, 0.525736f, 0.0f, 1.0f, -0.9822f, 0.1876f, 0.0f,

		-0.951058f, 0.0f, 0.309013f, 1.0f, -0.905f, 0.3304f, 0.268f,
		-0.723607f, 0.44722f, 0.525725f, 1.0f, -0.905f, 0.3304f, 0.268f,
		-0.850648f, 0.525736f, 0.0f, 1.0f, -0.905f, 0.3304f, 0.268f,

		-0.587786f, 0.0f, 0.809017f, 1.0f, -0.5346f, 0.3304f, 0.7779f,
		-0.262869f, 0.525738f, 0.809012f, 1.0f, -0.5346f, 0.3304f, 0.7779f,
		-0.723607f, 0.44722f, 0.525725f, 1.0f, -0.5346f, 0.3304f, 0.7779f,

		-0.587786f, 0.0f, 0.809017f, 1.0f, -0.3035f, 0.1876f, 0.9342f,
		0.0f, 0.0f, 1.0f, 1.0f, -0.3035f, 0.1876f, 0.9342f,
		-0.262869f, 0.525738f, 0.809012f, 1.0f, -0.3035f, 0.1876f, 0.9342f,

		0.0f, 0.0f, 1.0f, 1.0f, -0.0247f, 0.3304f, 0.9435f,
		0.276388f, 0.44722f, 0.850649f, 1.0f, -0.0247f, 0.3304f, 0.9435f,
		-0.262869f, 0.525738f, 0.809012f, 1.0f, -0.0247f, 0.3304f, 0.9435f,

		0.587786f, 0.0f, 0.809017f, 1.0f, 0.5746f, 0.3304f, 0.7488f,
		0.688189f, 0.525736f, 0.499997f, 1.0f, 0.5746f, 0.3304f, 0.7488f,
		0.276388f, 0.44722f, 0.850649f, 1.0f, 0.5746f, 0.3304f, 0.7488f,

		0.587786f, 0.0f, 0.809017f, 1.0f, 0.7947f, 0.1876f, 0.5773f,
		0.951058f, 0.0f, 0.309013f, 1.0f, 0.7947f, 0.1876f, 0.5773f,
		0.688189f, 0.525736f, 0.499997f, 1.0f, 0.7947f, 0.1876f, 0.5773f,

		0.951058f, 0.0f, 0.309013f, 1.0f, 0.8897f, 0.3304f, 0.3151f,
		0.894426f, 0.447216f, 0.0f, 1.0f, 0.8897f, 0.3304f, 0.3151f,
		0.688189f, 0.525736f, 0.499997f, 1.0f, 0.8897f, 0.3304f, 0.3151f,

		0.587786f, 0.0f, -0.809017f, 1.0f, 0.3066f, 0.1256f, -0.9435f,
		0.0f, 0.0f, -1.0f, 1.0f, 0.3066f, 0.1256f, -0.9435f,
		0.276388f, 0.44722f, -0.850649f, 1.0f, 0.3066f, 0.1256f, -0.9435f,

		0.587786f, 0.0f, -0.809017f, 1.0f, 0.3035f, -0.1876f, -0.9342f,
		0.262869f, -0.525738f, -0.809012f, 1.0f, 0.3035f, -0.1876f, -0.9342f,
		0.0f, 0.0f, -1.0f, 1.0f, 0.3035f, -0.1876f, -0.9342f,

		0.262869f, -0.525738f, -0.809012f, 1.0f, 0.0247f, -0.3304f, -0.9435f,
		-0.276388f, -0.44722f, -0.850649f, 1.0f, 0.0247f, -0.3304f, -0.9435f,
		0.0f, 0.0f, -1.0f, 1.0f, 0.0247f, -0.3304f, -0.9435f,

		-0.587786f, 0.0f, -0.809017f, 1.0f, -0.8026f, 0.1256f, -0.5831f,
		-0.951058f, 0.0f, -0.309013f, 1.0f, -0.8026f, 0.1256f, -0.5831f,
		-0.723607f, 0.44722f, -0.525725f, 1.0f, -0.8026f, 0.1256f, -0.5831f,

		-0.587786f, 0.0f, -0.809017f, 1.0f, -0.7947f, -0.1876f, -0.5773f,
		-0.688189f, -0.525736f, -0.499997f, 1.0f, -0.7947f, -0.1876f, -0.5773f,
		-0.951058f, 0.0f, -0.309013f, 1.0f, -0.7947f, -0.1876f, -0.5773f,

		-0.688189f, -0.525736f, -0.499997f, 1.0f, -0.8897f, -0.3304f, -0.3151f,
		-0.894426f, -0.447216f, 0.0f, 1.0f, -0.8897f, -0.3304f, -0.3151f,
		-0.951058f, 0.0f, -0.309013f, 1.0f, -0.8897f, -0.3304f, -0.3151f,

		-0.951058f, 0.0f, 0.309013f, 1.0f, -0.8026f, 0.1256f, 0.5831f,
		-0.587786f, 0.0f, 0.809017f, 1.0f, -0.8026f, 0.1256f, 0.5831f,
		-0.723607f, 0.44722f, 0.525725f, 1.0f, -0.8026f, 0.1256f, 0.5831f,

		-0.951058f, 0.0f, 0.309013f, 1.0f, -0.7947f, -0.1876f, 0.5773f,
		-0.688189f, -0.525736f, 0.499997f, 1.0f, -0.7947f, -0.1876f, 0.5773f,
		-0.587786f, 0.0f, 0.809017f, 1.0f, -0.7947f, -0.1876f, 0.5773f,

		-0.688189f, -0.525736f, 0.499997f, 1.0f, -0.5746f, -0.3304f, 0.7488f,
		-0.276388f, -0.44722f, 0.850649f, 1.0f, -0.5746f, -0.3304f, 0.7488f,
		-0.587786f, 0.0f, 0.809017f, 1.0f, -0.5746f, -0.3304f, 0.7488f,

		0.0f, 0.0f, 1.0f, 1.0f, 0.3066f, 0.1256f, 0.9435f,
		0.587786f, 0.0f, 0.809017f, 1.0f, 0.3066f, 0.1256f, 0.9435f,
		0.276388f, 0.44722f, 0.850649f, 1.0f, 0.3066f, 0.1256f, 0.9435f,

		0.0f, 0.0f, 1.0f, 1.0f, 0.3035f, -0.1876f, 0.9342f,
		0.262869f, -0.525738f, 0.809012f, 1.0f, 0.3035f, -0.1876f, 0.9342f,
		0.587786f, 0.0f, 0.809017f, 1.0f, 0.3035f, -0.1876f, 0.9342f,

		0.262869f, -0.525738f, 0.809012f, 1.0f, 0.5346f, -0.3304f, 0.7779f,
		0.723607f, -0.44722f, 0.525725f, 1.0f, 0.5346f, -0.3304f, 0.7779f,
		0.587786f, 0.0f, 0.809017f, 1.0f, 0.5346f, -0.3304f, 0.7779f,

		0.951058f, 0.0f, 0.309013f, 1.0f, 0.9921f, 0.1256f, 0.0f,
		0.951058f, 0.0f, -0.309013f, 1.0f, 0.9921f, 0.1256f, 0.0f,
		0.894426f, 0.447216f, 0.0f, 1.0f, 0.9921f, 0.1256f, 0.0f,

		0.951058f, 0.0f, 0.309013f, 1.0f, 0.9822f, -0.1876f, 0.0f,
		0.850648f, -0.525736f, 0.0f, 1.0f, 0.9822f, -0.1876f, 0.0f,
		0.951058f, 0.0f, -0.309013f, 1.0f, 0.9822f, -0.1876f, 0.0f,

		0.850648f, -0.525736f, 0.0f, 1.0f, 0.905f, -0.3304f, -0.268f,
		0.723607f, -0.44722f, -0.525725f, 1.0f, 0.905f, -0.3304f, -0.268f,
		0.951058f, 0.0f, -0.309013f, 1.0f, 0.905f, -0.3304f, -0.268f,

		0.425323f, -0.850654f, -0.309011f, 1.0f, 0.4713f, -0.6617f, -0.5831f,
		0.262869f, -0.525738f, -0.809012f, 1.0f, 0.4713f, -0.6617f, -0.5831f,
		0.723607f, -0.44722f, -0.525725f, 1.0f, 0.4713f, -0.6617f, -0.5831f,

		0.425323f, -0.850654f, -0.309011f, 1.0f, 0.1876f, -0.7947f, -0.5773f,
		-0.162456f, -0.850654f, -0.499995f, 1.0f, 0.1876f, -0.7947f, -0.5773f,
		0.262869f, -0.525738f, -0.809012f, 1.0f, 0.1876f, -0.7947f, -0.5773f,

		-0.162456f, -0.850654f, -0.499995f, 1.0f, -0.0385f, -0.6617f, -0.7488f,
		-0.276388f, -0.44722f, -0.850649f, 1.0f, -0.0385f, -0.6617f, -0.7488f,
		0.262869f, -0.525738f, -0.809012f, 1.0f, -0.0385f, -0.6617f, -0.7488f,

		-0.162456f, -0.850654f, -0.499995f, 1.0f, -0.4089f, -0.6617f, -0.6284f,
		-0.688189f, -0.525736f, -0.499997f, 1.0f, -0.4089f, -0.6617f, -0.6284f,
		-0.276388f, -0.44722f, -0.850649f, 1.0f, -0.4089f, -0.6617f, -0.6284f,

		-0.162456f, -0.850654f, -0.499995f, 1.0f, -0.4911f, -0.7947f, -0.3568f,
		-0.52573f, -0.850652f, 0.0f, 1.0f, -0.4911f, -0.7947f, -0.3568f,
		-0.688189f, -0.525736f, -0.499997f, 1.0f, -0.4911f, -0.7947f, -0.3568f,

		-0.52573f, -0.850652f, 0.0f, 1.0f, -0.724f, -0.6617f, -0.1947f,
		-0.894426f, -0.447216f, 0.0f, 1.0f, -0.724f, -0.6617f, -0.1947f,
		-0.688189f, -0.525736f, -0.499997f, 1.0f, -0.724f, -0.6617f, -0.1947f,

		-0.52573f, -0.850652f, 0.0f, 1.0f, -0.724f, -0.6617f, 0.1947f,
		-0.688189f, -0.525736f, 0.499997f, 1.0f, -0.724f, -0.6617f, 0.1947f,
		-0.894426f, -0.447216f, 0.0f, 1.0f, -0.724f, -0.6617f, 0.1947f,

		-0.52573f, -0.850652f, 0.0f, 1.0f, -0.4911f, -0.7947f, 0.3568f,
		-0.162456f, -0.850654f, 0.499995f, 1.0f, -0.4911f, -0.7947f, 0.3568f,
		-0.688189f, -0.525736f, 0.499997f, 1.0f, -0.4911f, -0.7947f, 0.3568f,

		-0.162456f, -0.850654f, 0.499995f, 1.0f, -0.4089f, -0.6617f, 0.6284f,
		-0.276388f, -0.44722f, 0.850649f, 1.0f, -0.4089f, -0.6617f, 0.6284f,
		-0.688189f, -0.525736f, 0.499997f, 1.0f, -0.4089f, -0.6617f, 0.6284f,

		0.850648f, -0.525736f, 0.0f, 1.0f, 0.7002f, -0.6617f, -0.268f,
		0.425323f, -0.850654f, -0.309011f, 1.0f, 0.7002f, -0.6617f, -0.268f,
		0.723607f, -0.44722f, -0.525725f, 1.0f, 0.7002f, -0.6617f, -0.268f,

		0.850648f, -0.525736f, 0.0f, 1.0f, 0.6071f, -0.7947f, 0.0f,
		0.425323f, -0.850654f, 0.309011f, 1.0f, 0.6071f, -0.7947f, 0.0f,
		0.425323f, -0.850654f, -0.309011f, 1.0f, 0.6071f, -0.7947f, 0.0f,

		0.425323f, -0.850654f, 0.309011f, 1.0f, 0.3313f, -0.9435f, 0.0f,
		0.0f, -1.0f, 0.0f, 1.0f, 0.3313f, -0.9435f, 0.0f,
		0.425323f, -0.850654f, -0.309011f, 1.0f, 0.3313f, -0.9435f, 0.0f,

		-0.162456f, -0.850654f, 0.499995f, 1.0f, -0.0385f, -0.6617f, 0.7488f,
		0.262869f, -0.525738f, 0.809012f, 1.0f, -0.0385f, -0.6617f, 0.7488f,
		-0.276388f, -0.44722f, 0.850649f, 1.0f, -0.0385f, -0.6617f, 0.7488f,

		-0.162456f, -0.850654f, 0.499995f, 1.0f, 0.1876f, -0.7947f, 0.5773f,
		0.425323f, -0.850654f, 0.309011f, 1.0f, 0.1876f, -0.7947f, 0.5773f,
		0.262869f, -0.525738f, 0.809012f, 1.0f, 0.1876f, -0.7947f, 0.5773f,

		0.425323f, -0.850654f, 0.309011f, 1.0f, 0.4713f, -0.6617f, 0.5831f,
		0.723607f, -0.44722f, 0.525725f, 1.0f, 0.4713f, -0.6617f, 0.5831f,
		0.262869f, -0.525738f, 0.809012f, 1.0f, 0.4713f, -0.6617f, 0.5831f
	};

    elementsPerVertex = 7;
    vertexCount = sizeof(vertices) / sizeof(GLfloat) / elementsPerVertex;

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Ball::update()
{
    position += velocity;
    if (position.x < -28) {
        position.x = -28;
        velocity.x *= -1;
    }
    else if (position.x > 28) {
        position.x = 28;
        velocity.x *= -1;
    }

    // reset game
    if (position.y < -160 || position.y > 160)
    {
        velocity.x = 1;
        velocity.y = -0.5;
        position.y = -40;
        angleX = 0;
    }

    angleX += velocity.length() * 0.05;
    //std::cout << "angleX = " << angleX << std::endl;

    modelTransformation = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, 0.75f, position.y));
    modelTransformation = glm::rotate(modelTransformation, std::atan2(velocity.x, velocity.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelTransformation = glm::rotate(modelTransformation, angleX, glm::vec3(1.0f, 0.0f, 0.0f));
    modelTransformation = glm::scale(modelTransformation, glm::vec3(2.0f, 2.0f, 2.0f));
}

void Ball::render(Camera* camera)
{
    shader->use();
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glUniform4f(shader->vcolor_location, 1.0f, 0.0f, 0.0f, 1.0f);

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

