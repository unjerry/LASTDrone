#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
void processInput(GLFWwindow *window);
void keyback(GLFWwindow *window, int key, int scancode, int action, int mods);
class opwindow
{
private:
    GLFWwindow *window;
    int version;
    GladGLContext *gl;

public:
    void bdwindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);
        gl = (GladGLContext *)calloc(1, sizeof(GladGLContext));
        if (!gl)
        {
            throw std::invalid_argument("Failed to create context");
        }

        version = gladLoadGLContext(gl, glfwGetProcAddress);
        std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;
        gl->Viewport(0, 0, 800, 600);
        glfwSetKeyCallback(window, keyback);
        while (!glfwWindowShouldClose(window))
        {
            glfwSwapBuffers(window);
            glfwPollEvents();
            processInput(window);
            gl->ClearColor(0.f, 0.8f, 0.f, 1.0f);
            gl->Clear(GL_COLOR_BUFFER_BIT);
        }
        glfwTerminate();
    }
};
int main()
{
    opwindow a;
    a.bdwindow();
    // glfwInit();
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    // if (window == NULL)
    // {
    //     std::cout << "Failed to create GLFW window" << std::endl;
    //     glfwTerminate();
    //     return -1;
    // }

    // glfwMakeContextCurrent(window);
    // GladGLContext *gl = (GladGLContext *)calloc(1, sizeof(GladGLContext));
    // if (!gl)
    // {
    //     throw std::invalid_argument("Failed to create context");
    // }

    // int version = gladLoadGLContext(gl, glfwGetProcAddress);
    // std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;
    // gl->Viewport(0, 0, 800, 600);
    // glfwSetKeyCallback(window, keyback);
    // while (!glfwWindowShouldClose(window))
    // {
    //     glfwSwapBuffers(window);
    //     glfwPollEvents();
    //     processInput(window);
    //     gl->ClearColor(0.f, 0.8f, 0.f, 1.0f);
    //     gl->Clear(GL_COLOR_BUFFER_BIT);
    // }
    // glfwTerminate();
    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     0.0f, 0.5f, 0.0f};
    // unsigned int VBO;
    // gl->GenBuffers(1, &VBO);
    // gl->BindBuffer(GL_ARRAY_BUFFER, VBO);
    // gl->BufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void keyback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == 1)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
