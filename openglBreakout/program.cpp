/*******************************************************************
** This code is part of LASTDrone.
******************************************************************/
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <game.h>
#include <resource_manager.h>
#include <learnopengl/filesystem.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <core/gmWindow.h>
#include <iostream>

GladGLContext *gl;

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

Game::Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[])
{
    gmWindow::gmWindowSpecification spec(SCREEN_WIDTH, SCREEN_HEIGHT, "BreakOut");
    gmWindow::gmWindow WINDW(spec);
    GLFWwindow *window = WINDW.getWindow();
    gl = WINDW.getGl();
    glfwSetKeyCallback(window, key_callback);
    WINDW.set_framebuffer_size_callback(framebuffer_size_callback);
    WINDW.set_window_icon(FileSystem::getPath("resources/textures/awesomeface.png").c_str());

    // GLFWimage images[1];
    // images[0].pixels = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &images[0].width, &images[0].height, 0, 4); // rgba channels
    // glfwSetWindowIcon(window, 1, images);
    // stbi_image_free(images[0].pixels);
    // OpenGL configuration
    // --------------------
    gl->Viewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gl->Enable(GL_BLEND);
    gl->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // // initialize game
    // ---------------
    Breakout.Init();

    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    std::cout << "sldkfj" << std::endl;
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile("rhd", aiProcess_Triangulate | aiProcess_FlipUVs); // retrieve the directory path of the filepath
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        // return 0;
    }
    // directory = path.substr(0, path.find_last_of('/'));
    // process ASSIMP's root node recursively
    // processNode(scene->mRootNode, scene);

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
        gl->ClearColor(0.1f, 0.2f, 0.4f, 1.0f);
        gl->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    Breakout.changeSize(width, height);
}