#include <GL/glew.h> // Must be included first
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

#include <Renderer.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>

//static std::string ParseShader(const std::string& filepath)
//{
//    std::ifstream file(filepath);
//
//    std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
//    
//    return content;
//}
//
//static GLuint CompileShader(GLuint type, const std::string& source)
//{
//    GLuint id = glCreateShader(type);
//    const char* src = source.c_str();
//    glShaderSource(id, 1, &src, nullptr);
//    glCompileShader(id);
//
//    int result;
//    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//    if (result == GL_FALSE)
//    {
//        int length;
//        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//        char* message = new char[length];
//        glGetShaderInfoLog(id, length, NULL, message);
//        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
//        std::cerr << message << std::endl;
//        glDeleteShader(id);
//        return 0;
//    }
//
//    return id;
//}
//
//static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
//{
//    GLuint program =  glCreateProgram();
//    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//    glAttachShader(program, vs);
//    glAttachShader(program, fs);
//    glLinkProgram(program);
//    glValidateProgram(program);
//
//    glDeleteShader(vs);
//    glDeleteShader(fs);
//
//    return program;
//}

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

    /*std::string vertexShader = ParseShader("res/shaders/basic.vert");
    std::string fragmentShader = ParseShader("res/shaders/basic.frag");
    std::cout << vertexShader << std::endl << fragmentShader << std::endl;
    GLuint shader = CreateShader(vertexShader, fragmentShader);*/

    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    shader.Bind();

    // Loading location of uniform
    /*int location = glGetUniformLocation(shader, "u_Color");
    if (location != -1)
    {
        glUniform4f(location, (float)sin(glfwGetTime()), 0.3f, 0.8f, 1.0f);
    }*/


    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor((float)cos(glfwGetTime()), (float)cos(glfwGetTime() / 2), (float)cos(glfwGetTime() / 4), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glUseProgram(shader);

        //vao.Bind();
        //ibo.Bind();

        // Setting uniform
        shader.SetUniform4f("u_Color", (float)sin(glfwGetTime()), (float)sin(glfwGetTime() / 2), (float)sin(glfwGetTime() / 4), 1.0f);
        //glUniform4f(location, (float)sin(glfwGetTime()), (float)sin(glfwGetTime()/2), (float)sin(glfwGetTime()/4), 1.0f);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
