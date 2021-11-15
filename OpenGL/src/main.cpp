#include <GL/glew.h> // Must be included first
#include <GLFW/glfw3.h>

#include <iostream>

#include <Renderer.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>
#include <Texture.h>

//void APIENTRY openglCallbackFunction(GLenum source,
//    GLenum type,
//    GLuint id,
//    GLenum severity,
//    GLsizei length,
//    const GLchar* message,
//    const void* userParam) {
//
//    std::cout << "---------------------opengl-callback-start------------" << std::endl;
//    std::cout << "message: " << message << std::endl;
//    std::cout << "type: ";
//    switch (type) {
//    case GL_DEBUG_TYPE_ERROR:
//        std::cout << "ERROR";
//        break;
//    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
//        std::cout << "DEPRECATED_BEHAVIOR";
//        break;
//    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
//        std::cout << "UNDEFINED_BEHAVIOR";
//        break;
//    case GL_DEBUG_TYPE_PORTABILITY:
//        std::cout << "PORTABILITY";
//        break;
//    case GL_DEBUG_TYPE_PERFORMANCE:
//        std::cout << "PERFORMANCE";
//        break;
//    case GL_DEBUG_TYPE_OTHER:
//        std::cout << "OTHER";
//        break;
//    }
//    std::cout << std::endl;
//
//    std::cout << "id: " << id << std::endl;
//    std::cout << "severity: ";
//    switch (severity) {
//    case GL_DEBUG_SEVERITY_LOW:
//        std::cout << "LOW";
//        break;
//    case GL_DEBUG_SEVERITY_MEDIUM:
//        std::cout << "MEDIUM";
//        break;
//    case GL_DEBUG_SEVERITY_HIGH:
//        std::cout << "HIGH";
//        break;
//    }
//    std::cout << std::endl;
//    std::cout << "---------------------opengl-callback-end--------------" << std::endl;
//}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "PGR - proceduralni generovani nabytku", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Must be after glfwMakeContextCurrent
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Error!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    //if (glDebugMessageCallback)
    //{
    //    std::cout << "Register OpenGL debug callback " << std::endl;
    //    glEnable(GL_DEBUG_OUTPUT);
    //    //glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    //    glDebugMessageCallback(openglCallbackFunction, nullptr);
    //    GLuint unusedIds = 0;
    //    glDebugMessageControl(GL_DONT_CARE,
    //        GL_DONT_CARE,
    //        GL_DONT_CARE,
    //        0,
    //        &unusedIds,
    //        true);
    //}
    //else
    //{
    //    std::cout << "glDebugMessageCallback not available" << std::endl;
    //}

    float positions[] = {
        -0.5f, -0.5f,  0.0f,  0.0f, // 0
         0.5f, -0.5f,  1.0f,  0.0f, // 1
         0.5f,  0.5f,  1.0f,  1.0f, // 2
        -0.5f,  0.5f,  0.0f,  1.0f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    VertexArray vao;
    vao.Bind();

    VertexBuffer vbo(positions, 4 * 4 * sizeof(float));
    vbo.Bind();
    
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    
    vao.AddBuffer(/* vbo, */ layout);
    
    IndexBuffer ibo(indices, 6);    

    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    shader.Bind();

    Texture texture("res/textures/metal.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    vao.Unbind();
    shader.Unbind();
    vbo.Unbind();
    ibo.Unbind();

    Renderer renderer;

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        // Setting uniform
        shader.SetUniform4f("u_Color", (float)sin(glfwGetTime()), (float)sin(glfwGetTime() / 2), (float)sin(glfwGetTime() / 4), 1.0f);
        
        // Draw
        renderer.Draw(vao, ibo, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
