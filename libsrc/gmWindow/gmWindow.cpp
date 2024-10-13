#include <core/gmWindow.h>
namespace gmWindow
{

    GLFWwindow *gmWindow::getWindow()
    {
        return window;
    }
    GladGLContext *gmWindow::getGl()
    {
        return gl;
    }
    gmWindow::gmWindow(const gmWindowSpecification &spec) : mSpecification(spec)
    {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        // --------------------
        window = glfwCreateWindow(mSpecification.SCR_WIDTH, mSpecification.SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            throw std::invalid_argument("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window);
        gl = (GladGLContext *)calloc(1, sizeof(GladGLContext));
        if (!gl)
        {
            throw std::invalid_argument("Failed to create context");
        }

        int version = gladLoadGLContext(gl, glfwGetProcAddress);
        std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        // if ()
        // {
        //     std::cout << "Failed to initialize GLAD" << std::endl;
        //     throw std::invalid_argument("Failed to initialize GLAD");
        // }
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }

    gmWindow::~gmWindow()
    {
        free(gl);
    }
}
