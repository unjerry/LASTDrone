/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <game.h>
#include <resource_manager.h>

#include <core/gmWindow.h>

GladGLContext *gl;

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[])
{
    gmWindow::gmWindowSpecification spec(SCREEN_WIDTH, SCREEN_HEIGHT, "BreakOut");
    gmWindow::gmWindow WINDW(spec);
    GLFWwindow *window = WINDW.getWindow();
    gl = WINDW.getGl();

    glfwSetKeyCallback(window, key_callback);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL configuration
    // --------------------
    gl->Viewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gl->Enable(GL_BLEND);
    gl->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize game
    // ---------------
    Breakout.Init();

    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        // manage user input
        // -----------------
        Breakout.ProcessInput(deltaTime);

        // update game state
        // -----------------
        Breakout.Update(deltaTime);

        // render
        // ------
        gl->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        gl->Clear(GL_COLOR_BUFFER_BIT);
        Breakout.Render();

        glfwSwapBuffers(window);
    }

    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------
    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Breakout.Keys[key] = true;
        else if (action == GLFW_RELEASE)
            Breakout.Keys[key] = false;
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    gl->Viewport(0, 0, width, height);
}