#include <Model.h>

void Model::generateModel( std::vector<Vertex>& vertices, std::vector<unsigned int> &indices )
{
    std::cout << "JEBEJ" << std::endl;
    /*vertices.clear();
    indices.clear();

    Vertex tmpVer;
    
    tmpVer.color[0] = 0.0f;
    tmpVer.color[1] = 0.0f;
    tmpVer.color[2] = 0.0f;
    tmpVer.textureType = 0.0f;

    tmpVer.position[0] = 0.0f;
    tmpVer.position[1] = 0.0f;
    tmpVer.position[2] = 0.0f;
    tmpVer.texture[0] = 0.0f;
    tmpVer.texture[1] = 0.0f;
    vertices.push_back(tmpVer);

    tmpVer.position[0] = (float)width;
    tmpVer.position[1] = 0.0f;
    tmpVer.position[2] = 0.0f;
    tmpVer.texture[0] = 1.0f;
    tmpVer.texture[1] = 0.0f;
    vertices.push_back(tmpVer);

    tmpVer.position[0] = (float)width;
    tmpVer.position[1] = (float)height;
    tmpVer.position[2] = 0.0f;
    tmpVer.texture[0] = 1.0f;
    tmpVer.texture[1] = 1.0f;
    vertices.push_back(tmpVer);

    tmpVer.position[0] = 0.0f;
    tmpVer.position[1] = (float)height;
    tmpVer.position[2] = 0.0f;
    tmpVer.texture[0] = 0.0f;
    tmpVer.texture[1] = 1.0f;
    vertices.push_back(tmpVer);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);*/
}

bool Model::generateGUI()
{
    bool clicked = false;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
        ImGui::Begin("Parametrs");
        ImGui::InputInt("Height", &height);
        ImGui::InputInt("Width", &width);
        ImGui::InputInt("Depth", &depth);
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
