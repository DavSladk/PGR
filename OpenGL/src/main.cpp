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
#include <Model.h>

float x = 0;
float y = 0;
float z = 0;
float distance = -5.0f;

float lastTime = 0;
float currentTime = 0;
float deltaTime = 0;

float sensitivity = 50.0f;

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        x -= 1 * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        x += 1 * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        y -= 1 * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        y += 1 * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
    {
        distance += 1 * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
    {
        distance -= 1 * deltaTime;
    }
}

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
    window = glfwCreateWindow(800, 800, "PGR - proceduralni generovani nabytku", NULL, NULL);
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

    std::vector<Vertex>vertices =
    {
        {-0.5f,-0.5f, -0.5f,    0.5f, 0.5f, 0.5f,    0.0f, 0.0f,    0.0f}, // 1
        { 0.5f,-0.5f, -0.5f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f,    0.0f}, // 2
        { 0.5f, 0.5f, -0.5f,    0.5f, 0.5f, 0.5f,    1.0f, 1.0f,    0.0f}, // 3
        {-0.5f, 0.5f, -0.5f,    0.5f, 0.5f, 0.5f,    0.0f, 1.0f,    0.0f}, // 4

        {-0.5f,-0.5f, 0.5f,    0.5f, 0.5f, 0.5f,    0.0f, 0.0f,    1.0f}, // 5
        { 0.5f,-0.5f, 0.5f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f,    1.0f}, // 6
        { 0.5f, 0.5f, 0.5f,    0.5f, 0.5f, 0.5f,    1.0f, 1.0f,    1.0f}, // 7
        {-0.5f, 0.5f, 0.5f,    0.5f, 0.5f, 0.5f,    0.0f, 1.0f,    1.0f}  // 8
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        4, 5, 1,
        1, 0, 4,

        7, 6, 2,
        2, 3, 7,

        1, 5, 6,
        6, 2, 1,

        0, 4, 7,
        7, 3, 0
    };

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

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
    
    IndexBuffer ibo(indices, 36);    

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

    int height = 0;
    int width = 0;
    int depth = 0;
    int doors = 0;
    int drawers = 0;
    int legs = 0;
    int legs_heigh = 0;
    int legs_width = 0;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        lastTime = currentTime;
        currentTime = (float)glfwGetTime();
        deltaTime = currentTime - lastTime;

        processInput(window);

        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, y * glm::radians(sensitivity), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, x * glm::radians(sensitivity), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, distance));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

        shader.SetUniformMatrix4f("model", model);
        shader.SetUniformMatrix4f("view", view);
        shader.SetUniformMatrix4f("projection", projection);
        
        // Draw
        renderer.Draw(vao, ibo, shader);

        {
            static int counter = 0;
            //ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);
            
            //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::InputInt("height", &height );
            ImGui::InputInt("width", &width );
            ImGui::InputInt("depth", &depth );
            ImGui::InputInt("doors", &doors );
            ImGui::InputInt("drawers", &drawers );
            ImGui::InputInt("legs", &legs);
            ImGui::InputInt("legs height", &legs_heigh);
            ImGui::InputInt("legs width", &legs_width);
            if (ImGui::Button("Generate"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                counter++;
            ImGui::Text("Arrow keys to rotate.");
            ImGui::Text("Page up/down for zoom.");
            ImGui::Text("Esc to exit.");
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
