#include <GL/glew.h> // Must be included first
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <iostream>
#include <vector>

#include <Renderer.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>
#include <Texture.h>

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

    /* Create a windowed mode window and its OpenGL context */
    //window = glfwCreateWindow(640, 480, "PGR - proceduralni generovani nabytku", NULL, NULL);
    window = glfwCreateWindow(960, 540, "PGR - proceduralni generovani nabytku", NULL, NULL);
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

    struct Vertex {
        float position[3];
        float color[3];
        float texture[2];
        float textureType;
    };

    std::vector<Vertex>vertices =
    {
        {100.0f,100.0f, 0.0f,    0.5f, 0.5f, 0.5f,    0.0f, 0.0f,    0.0f},
        {200.0f,100.0f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f,    0.0f},
        {200.0f, 200.0f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 1.0f,    0.0f},
        {100.0f, 200.0f, 0.0f,    0.5f, 0.5f, 0.5f,    0.0f, 1.0f,    0.0f}
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    VertexArray vao;
    vao.Bind();

    VertexBuffer vbo(vertices.data(), vertices.size() * sizeof(Vertex));
    vbo.Bind();
    
    VertexBufferLayout layout;
    layout.Push<float>(3); // position
    layout.Push<float>(3); // color
    layout.Push<float>(2); // texture
    layout.Push<float>(1); // texture type
    
    vao.AddBuffer(/* vbo, */ layout);
    
    IndexBuffer ibo(indices, 6);

    //glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    

    Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
    shader.Bind();

    Texture textureMetal("res/textures/metal.png");
    Texture textureWood("res/textures/wood.png");
    textureMetal.Unbind();
    textureWood.Unbind();
    textureMetal.Bind(0);
    textureWood.Bind(1);
    shader.SetUniform1i("u_Texture_Metal", 0);
    shader.SetUniform1i("u_Texture_Wood", 1);

    vao.Unbind();
    shader.Unbind();
    vbo.Unbind();
    ibo.Unbind();

    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    glm::vec3 translation(200, 200, 0);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);

        glm::mat4 mvp = proj * view * model;

        shader.SetUniformMatrix4f("u_MVP", mvp);
        
        // Draw
        renderer.Draw(vao, ibo, shader);

        {
            static int counter = 0;
            ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
        }

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
