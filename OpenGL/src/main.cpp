#include <GL/glew.h> // Must be included first
#include <GLFW/glfw3.h>

#include <iostream>

#include <Renderer.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
        std::cerr << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
        -0.5f,  0.5f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray vao;
    vao.Bind();

    VertexBuffer vbo(positions, 2 * 4 * sizeof(float));
    vbo.Bind();
    
    VertexBufferLayout layout;
    layout.Push<float>(2);
    
    vao.AddBuffer(vbo, layout);
    
    IndexBuffer ibo(indices, 6);    

    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    shader.Bind();

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
