#include "window.hpp"

Window::Window(glm::vec2 size, std::string title)
{
    if (!glfwInit())
    {
        std::cout << "Failed to init glfw" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_windowSize = size;
    m_window = glfwCreateWindow(m_windowSize.x, m_windowSize.y, title.c_str(), NULL, NULL);

    if (m_window == NULL)
    {
        std::cout << "Faild to create window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to init glew" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LESS);

    glfwSwapInterval(0);
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::isWindowOpen()
{
    return glfwWindowShouldClose(m_window);
}

void Window::clear()
{
    glClearColor(0.3f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
}

void Window::swap()
{
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    m_windowSize = glm::vec2(width, height);

    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

glm::mat4 Window::getWindowProjection()
{
    return glm::ortho(0.0f, static_cast<float>(m_windowSize.x), 0.0f, static_cast<float>(m_windowSize.y));
}