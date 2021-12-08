#include <Model.h>

void Model::generateModel(glm::mat4 &center, std::vector<Vertex>& vertices, std::vector<unsigned int> &indices )
{
    vertices.clear();
    indices.clear();
    offset = 0;
    
    center = glm::mat4(1.0f);
    center = glm::translate(center, glm::vec3( - (width / 2), -(height / 2), -(depth / 2)));

    Vertex tmpVer;

    // Left outter
    generateSquareSide(0.0f, 0.0f, 0.0f, height, depth, texture, vertices, indices);
    // Left inner
    generateSquareSide(thickness, thickness, 0.0f, height - thickness, depth - thickness, texture, vertices, indices);
    // Right outter
    generateSquareSide(width, 0.0f, 0.0f, height, depth, texture, vertices, indices);
    // Right inner
    generateSquareSide(width - thickness, thickness, 0.0f, height - thickness, depth - thickness, texture, vertices, indices);

    // Left front
    generateSquareFront(depth, 0.0f, 0.0f, thickness, height, texture, vertices, indices);
    // Right front
    generateSquareFront(depth, width - thickness, 0.0f, width, height, texture, vertices, indices);
    // Top front
    generateSquareFront(depth, thickness, height - thickness, width - thickness, height, texture, vertices, indices);
    // Botton front
    generateSquareFront(depth, thickness, 0.0f, width - thickness, thickness, texture, vertices, indices);
    // Back
    generateSquareFront(0.0f, 0.0f, 0.0f, width, height, texture, vertices, indices);

    // Top outter
    generateSquareFlat(height, 0.0f, 0.0f, width, depth, texture, vertices, indices);
    // Top inner
    generateSquareFlat(height - thickness, thickness, 0.0f, width - thickness, depth, texture, vertices, indices);
    // Botton outter
    generateSquareFlat(0.0f, 0.0f, 0.0f, width, depth, texture, vertices, indices);
    // Botton inner
    generateSquareFlat(thickness, thickness, 0.0f, width - thickness, depth, texture, vertices, indices);
}

void Model::generateSquareSide(float constant, float y1, float z1, float y2, float z2, int tex, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    Vertex tmpVer;

    tmpVer.color[0] = 0.0f;
    tmpVer.color[1] = 0.0f;
    tmpVer.color[2] = 0.0f;
    tmpVer.position[0] = constant;
    tmpVer.textureType = tex;

    tmpVer.position[1] = y1;
    tmpVer.position[2] = z1;
    tmpVer.texture[0] = 0.0f;
    tmpVer.texture[1] = 0.0f;
    vertices.push_back(tmpVer);

    tmpVer.position[1] = y1;
    tmpVer.position[2] = z2;
    tmpVer.texture[0] = 1.0f;
    tmpVer.texture[1] = 0.0f;
    vertices.push_back(tmpVer);

    tmpVer.position[1] = y2;
    tmpVer.position[2] = z2;
    tmpVer.texture[0] = 1.0f;
    tmpVer.texture[1] = 1.0f;
    vertices.push_back(tmpVer);

    tmpVer.position[1] = y2;
    tmpVer.position[2] = z1;
    tmpVer.texture[0] = 0.0f;
    tmpVer.texture[1] = 1.0f;
    vertices.push_back(tmpVer);

    indices.push_back(offset * 4 + 0);
    indices.push_back(offset * 4 + 1);
    indices.push_back(offset * 4 + 2);
    indices.push_back(offset * 4 + 2);
    indices.push_back(offset * 4 + 3);
    indices.push_back(offset * 4 + 0);
    offset++;
}

void Model::generateSquareFront(float constant, float x1, float y1, float x2, float y2, int tex, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    Vertex tmpVer;

    tmpVer.color[0] = 0.0f;
    tmpVer.color[1] = 0.0f;
    tmpVer.color[2] = 0.0f;
    tmpVer.position[2] = constant;
    tmpVer.textureType = tex;

    tmpVer.position[0] = x1;
    tmpVer.position[1] = y1;
    tmpVer.texture[0] = 0.0f;
    tmpVer.texture[1] = 0.0f;
    vertices.push_back(tmpVer);

    tmpVer.position[0] = x2;
    tmpVer.position[1] = y1;
    tmpVer.texture[0] = 1.0f;
    tmpVer.texture[1] = 0.0f;
    vertices.push_back(tmpVer);

    tmpVer.position[0] = x2;
    tmpVer.position[1] = y2;
    tmpVer.texture[0] = 1.0f;
    tmpVer.texture[1] = 1.0f;
    vertices.push_back(tmpVer);

    tmpVer.position[0] = x1;
    tmpVer.position[1] = y2;
    tmpVer.texture[0] = 0.0f;
    tmpVer.texture[1] = 1.0f;
    vertices.push_back(tmpVer);

    indices.push_back(offset * 4 + 0);
    indices.push_back(offset * 4 + 1);
    indices.push_back(offset * 4 + 2);
    indices.push_back(offset * 4 + 2);
    indices.push_back(offset * 4 + 3);
    indices.push_back(offset * 4 + 0);
    offset++;
}

void Model::generateSquareFlat(float constant, float x1, float z1, float x2, float z2, int tex, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    Vertex tmpVer;

    tmpVer.color[0] = 0.0f;
    tmpVer.color[1] = 0.0f;
    tmpVer.color[2] = 0.0f;
    tmpVer.position[1] = constant;
    tmpVer.textureType = tex;

    tmpVer.position[0] = x1;
    tmpVer.position[2] = z1;
    tmpVer.texture[0] = 0.0f;
    tmpVer.texture[1] = 0.0f;
    vertices.push_back(tmpVer);

    tmpVer.position[0] = x1;
    tmpVer.position[2] = z2;
    tmpVer.texture[0] = 1.0f;
    tmpVer.texture[1] = 0.0f;
    vertices.push_back(tmpVer);

    tmpVer.position[0] = x2;
    tmpVer.position[2] = z2;
    tmpVer.texture[0] = 1.0f;
    tmpVer.texture[1] = 1.0f;
    vertices.push_back(tmpVer);

    tmpVer.position[0] = x2;
    tmpVer.position[2] = z1;
    tmpVer.texture[0] = 0.0f;
    tmpVer.texture[1] = 1.0f;
    vertices.push_back(tmpVer);

    indices.push_back(offset * 4 + 0);
    indices.push_back(offset * 4 + 1);
    indices.push_back(offset * 4 + 2);
    indices.push_back(offset * 4 + 2);
    indices.push_back(offset * 4 + 3);
    indices.push_back(offset * 4 + 0);
    offset++;
}

bool Model::generateGUI()
{
    bool clicked = false;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
        ImGui::Begin("Parametrs");
        ImGui::InputFloat("Height", &height, 0.1f);
        ImGui::InputFloat("Width", &width, 0.1f);
        ImGui::InputFloat("Depth", &depth, 0.1f);
        ImGui::InputInt("Texture", &texture);
        ImGui::InputInt("Columns", &columnCount);

        if (ImGui::Button("Generate"))
        {
            clicked = true;
        }

        generateColumns(columnCount, columns, "");
                
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return clicked;
}

void Model::generateColumns(int& columnCount, std::vector<Column> &columns, std::string str)
{
    if (columnCount < 0)
    {
        return;
    }

    while (columnCount > columns.size())
    {
        columns.push_back(Column());
    }

    while (columnCount < columns.size())
    {
        columns.pop_back();
    }

    for (int i = 0; i < columns.size(); i++)
    {
        std::string number = str + std::to_string(i + 1) + ".";
        std::string text = number + " Column";
        
        if (ImGui::TreeNode(text.c_str()))
        {
            ImGui::InputInt("Ration", &(columns[i].ratio));
            ImGui::InputInt("Rows", &(columns[i].rowCount));
            generateRows(columns[i].rowCount, columns[i].rows, number);
            ImGui::TreePop();
        }
    }
}

void Model::generateRows(int& rowCount, std::vector<Row>& rows, std::string str)
{
    if (rowCount < 0)
    {
        return;
    }

    while (rowCount > rows.size())
    {
        rows.push_back(Row());
    }

    while (rowCount < rows.size())
    {
        rows.pop_back();
    }

    for (int i = 0; i < rows.size(); i++)
    {
        std::string number = str + std::to_string(i + 1) + ".";
        std::string text = number + " Row";

        if (ImGui::TreeNode(text.c_str()))
        {
            ImGui::InputInt("Ration", &(rows[i].ratio));
            ImGui::Checkbox("Recursive", &(rows[i].recursive));
            if (rows[i].recursive)
            {
                ImGui::InputInt("columns", &(rows[i].columnCount));
                generateColumns(rows[i].columnCount, rows[i].columns, number);
            }
            else
            {
                ImGui::InputInt("Texture", &(rows[i].texture));
            }
            ImGui::TreePop();
        }
    }
}

Model::Model(GLFWwindow* window) :
	height(1), width(1), depth(1), texture(false), columnCount(1)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

Model::~Model()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

Column::Column() :
    ratio(1), rowCount(1)
{
}

Row::Row() :
    ratio(1), recursive(false), texture(0), columnCount(1)
{
}
