#include <core/gmWindow.h>

namespace gmWindow
{
    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glfwMakeContextCurrent(window);
        GladGLContext *gl = (GladGLContext *)calloc(1, sizeof(GladGLContext));
        if (!gl)
        {
            throw std::invalid_argument("Failed to create context");
        }

        int version = gladLoadGLContext(gl, glfwGetProcAddress);
        std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;
        gl->Viewport(0, 0, width, height);
        free(gl);
    }
    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
}