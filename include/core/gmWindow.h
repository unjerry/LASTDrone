#ifndef GMWINDOW_H
#define GMWINDOW_H
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
// Function prototypes
GLFWwindow* create_window(const char *name, int major, int minor);
GladGLContext* create_context(GLFWwindow *window);
void free_context(GladGLContext *context);
void draw(GLFWwindow *window, GladGLContext *context, float r, float g, float b);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

namespace gmWindow
{
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    struct gmWindowSpecification
    {
        /* data */
        const unsigned int SCR_WIDTH = 800;
        const unsigned int SCR_HEIGHT = 600;
    };

    class gmWindow
    {
    private:
        /* data */
        gmWindowSpecification mSpecification;
        GLFWwindow *window;
        GladGLContext *gl;

    public:
        gmWindow(const gmWindowSpecification &spec = gmWindowSpecification());
        ~gmWindow();
        GLFWwindow *getWindow();
        GladGLContext *getGl();
    };
    
} // namespace gmWindow

#endif
