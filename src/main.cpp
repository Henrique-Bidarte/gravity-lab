#include <iostream>
#include <stdexcept>

#include <glad/glad.h>  // loader OpenGL
#include <GLFW/glfw3.h> // janela + contexto

static void glfw_error_callback(int code, const char *desc)
{
    std::cerr << "[GLFW ERROR] (" << code << "): " << desc << "\n";
}

int main()
{
    try
    {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
            throw std::runtime_error("glfwInit() failed");

        // Pedir um contexto OpenGL 4.3 Core (bom p/ compute depois)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow *window = glfwCreateWindow(1280, 720, "gravity-lab", nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("glfwCreateWindow() failed (talvez sua GPU/driver não suporte 4.3?)");
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // vsync

        // Carregar funções OpenGL via GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwDestroyWindow(window);
            glfwTerminate();
            throw std::runtime_error("gladLoadGLLoader() failed");
        }

        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";

        // Loop principal
        while (!glfwWindowShouldClose(window))
        {
            int w, h;
            glfwGetFramebufferSize(window, &w, &h);
            glViewport(0, 0, w, h);
            glClearColor(0.05f, 0.07f, 0.10f, 1.0f); // fundo “noite”
            glClear(GL_COLOR_BUFFER_BIT);

            // ESC para fechar
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                glfwSetWindowShouldClose(window, 1);
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[FATAL] " << e.what() << "\n";
        return 1;
    }
}
