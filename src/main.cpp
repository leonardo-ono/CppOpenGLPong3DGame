#include <iostream>
#include <chrono>
#include <thread>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "Shader.hpp"
#include "Table.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Camera.hpp"

GLFWwindow* window;

void initializeOpenGL()
{
    if (!glfwInit())
    {
        std::cout << "could not initialize glfw !" << std::endl;
        exit(EXIT_FAILURE);
    }
    GLFWmonitor* monitor = NULL; // glfwGetPrimaryMonitor(); // -> fullscreen
    window = glfwCreateWindow(800, 600, "[C++ / OpenGL 3] Pong 3D Test", monitor, NULL);
    if (!window) {
        std::cout << "could not create window !" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cout << "could not initialize glad !" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwSwapInterval(1);
}

void startGame()
{
    Shader shader;
    Table table(&shader);
    Ball ball(&shader);
    Paddle paddlePlayer(window, false, &shader, &ball);
    Paddle paddleCPU(window, true, &shader, &ball);

    Camera camera(&ball);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    double startTime = glfwGetTime();
    double lastTime = startTime;
    double delta;
    double timePerFrame = 1.0 / 60.0;
    double unprocessedTime = 0;
    while (!glfwWindowShouldClose(window)) {
        startTime = glfwGetTime();
        delta = startTime - lastTime;
        lastTime = startTime;
        unprocessedTime += delta;

        while (unprocessedTime > timePerFrame) {
            unprocessedTime -= timePerFrame;

            camera.update();
            table.update();
            paddlePlayer.update();
            paddleCPU.update();
            ball.update();

            paddlePlayer.checkCollision();
            paddleCPU.checkCollision();
        }

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        table.render(&camera);
        paddlePlayer.render(&camera);
        paddleCPU.render(&camera);
        ball.render(&camera);

        glfwSwapBuffers(window);

        glfwPollEvents();

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

int main()
{
    initializeOpenGL();
    startGame();
    return EXIT_SUCCESS;
}

