#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <core/gmWindow.h>
// Function prototypes
// GLFWwindow* create_window(const char *name, int major, int minor);
// GladGLContext* create_context(GLFWwindow *window);
// void free_context(GladGLContext *context);
// void draw(GLFWwindow *window, GladGLContext *context, float r, float g, float b);
// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// settings

int main()
{
    std::cout << "Hello Opengl" << std::endl;

    const size_t windowNum = 5;
    gmWindow::gmWindow window[windowNum];
    bool shallClose = false;

    // render loop
    // -----------
    while (true)
    {
        if (shallClose)
        {
            break;
        }
        for (size_t i = 0; i < windowNum; i++)
        {
            if (glfwWindowShouldClose(window[i].getWindow()))
            {
                shallClose = true;
                break;
            }
            window[i].run();
        }
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
