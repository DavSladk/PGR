#include <Model.h>

void Model::generateModel(glm::mat4& center, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	vertices.clear();
	indices.clear();
	offset = 0;

	center = glm::mat4(1.0f);
	center = glm::translate(center, glm::vec3(-(width / 2), -(height / 2), -(depth / 2)));

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

	// Generate columns
	generateColumnsModel(thickness, thickness, width - thickness, height - thickness, columns, vertices, indices);
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

void Model::generateColumnsModel(float x1, float y1, float x2, float y2, std::vector<Column>& columns, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	// Exit if invalid amount of columns
	if (columns.size() < 1)
	{
		return;
	}
	// Generate separators, when theyt make sense
	else if (columns.size() > 1)
	{
		// counter for ration
		float parts = 0;
		// counter for offseting
		float partsOffset = 0;
		// size of single part
		float partSize = 0;

		// count up all rations
		for (auto& column : columns)
		{
			parts += column.ratio;
		}

		// calculate size of single size
		partSize = (x2 - x1) / parts;

		// generate separators
		for (int i = 0; i < columns.size(); i++)
		{
			// except for the last column
			if (i < columns.size() - 1)
			{
				// Separator left side
				generateSquareSide(x1 + columns[i].ratio * partSize - thickness / 2.0f + partsOffset * partSize, y1, 0.0f, y2, depth, texture, vertices, indices);
				// Separator right side
				generateSquareSide(x1 + columns[i].ratio * partSize + thickness / 2.0f + partsOffset * partSize, y1, 0.0f, y2, depth, texture, vertices, indices);
				// Separator front
				generateSquareFront(depth, x1 + columns[i].ratio * partSize - thickness / 2.0f + partsOffset * partSize, y1, x1 + columns[i].ratio * partSize + thickness / 2.0f + partsOffset * partSize, y2, texture, vertices, indices);
			}

			// Generate rows in column
			if (i == 0)
			{
				generateRowsModel(x1, y1, x1 + columns[i].ratio * partSize - thickness / 2.0f, y2, columns[i].rows, vertices, indices);
			}
			else if (i == columns.size() - 1)
			{
				generateRowsModel(x1 + partsOffset * partSize + thickness / 2.0f, y1, x2, y2, columns[i].rows, vertices, indices);
			}
			else
			{
				generateRowsModel(x1 + partsOffset * partSize + thickness / 2.0f, y1, x1 + columns[i].ratio * partSize + partsOffset * partSize - thickness / 2.0f, y2, columns[i].rows, vertices, indices);
			}

			partsOffset += columns[i].ratio;
		}
	}
	// If only one column, do not render any separators.
	else // size == 1
	{
		generateRowsModel(x1, y1, x2, y2, columns[0].rows, vertices, indices);
	}
}

void Model::generateRowsModel(float x1, float y1, float x2, float y2, std::vector<Row>& rows, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	if (rows.size() < 1)
	{
		return;
	}
	else if (rows.size() > 1)
	{
		float parts = 0;
		float partsOffset = 0;
		float partSize = 0;

		for (auto& row : rows)
		{
			parts += row.ratio;
		}

		partSize = (y2 - y1) / (float)parts;

		for (int i = 0; i < rows.size(); i++)
		{
			if (i < rows.size() - 1)
			{
				// Separator upper side
				generateSquareFlat(y1 + rows[i].ratio * partSize + thickness / 2.0f + partsOffset * partSize, x1, 0.0f, x2, depth, texture, vertices, indices);
				// Separator lower side
				generateSquareFlat(y1 + rows[i].ratio * partSize - thickness / 2.0f + partsOffset * partSize, x1, 0.0f, x2, depth, texture, vertices, indices);
				// Separator front 
				generateSquareFront(depth, x1, y1 + rows[i].ratio * partSize - thickness / 2.0f + partsOffset * partSize, x2, y1 + rows[i].ratio * partSize + thickness / 2 + partsOffset * partSize, texture, vertices, indices);
			}

			if (rows[i].recursive)
			{

				if (i == 0)
				{
					generateColumnsModel(x1, y1, x2, y1 + rows[i].ratio * partSize - thickness / 2.0f, rows[i].columns, vertices, indices);
				}
				else if (i == rows.size() - 1)
				{
					generateColumnsModel(x1, y1 + thickness / 2.0f + partsOffset * partSize, x2, y2, rows[i].columns, vertices, indices);
				}
				else
				{
					generateColumnsModel(x1, y1 + thickness / 2.0f + partsOffset * partSize, x2, y1 + rows[i].ratio * partSize - thickness / 2.0f + partsOffset * partSize, rows[i].columns, vertices, indices);
				}
			}
			else
			{
				if (rows[i].type == 0)
				{
					// generate nothing
				}
				else if (rows[i].type == 1)
				{
					if (i == 0)
					{
						generateDoorModel(x1, y1, x2, y1 + rows[i].ratio * partSize - thickness / 2.0f, rows[i], vertices, indices);
					}
					else if (i == rows.size() - 1)
					{
						generateDoorModel(x1, y1 + thickness / 2.0f + partsOffset * partSize, x2, y2, rows[i], vertices, indices);
					}
					else
					{
						generateDoorModel(x1, y1 + thickness / 2.0f + partsOffset * partSize, x2, y1 + rows[i].ratio * partSize - thickness / 2.0f + partsOffset * partSize, rows[i], vertices, indices);
					}
				}
			}

			partsOffset += rows[i].ratio;
		}
	}
	else // size == 1
	{
		if (rows[0].recursive)
		{
			generateColumnsModel(x1, y1, x2, y2, rows[0].columns, vertices, indices);
		}
		else
		{
			if (rows[0].type == 0)
			{
				// generate nothing
			}
			else if (rows[0].type == 1)
			{
				generateDoorModel(x1, y1, x2, y2, rows[0], vertices, indices);

			}
		}
	}
}

void Model::generateDoorModel(float x1, float y1, float x2, float y2, Row& row, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	// Generate top
	generateSquareFlat(y2 + thickness / 3.0f, x1 - thickness / 3.0f, depth, x2 + thickness / 3.0f, depth + thickness, row.texture, vertices, indices);
	// Generate left
	generateSquareSide(x1 - thickness / 3.0f, y1 - thickness / 3.0f, depth, y2 + thickness / 3.0f, depth + thickness, row.texture, vertices, indices);
	// Generate right
	generateSquareSide(x2 + thickness / 3.0f, y1 - thickness / 3.0f, depth, y2 + thickness / 3.0f, depth + thickness, row.texture, vertices, indices);
	// Generate bottom
	generateSquareFlat(y1 - thickness / 3.0f, x1 - thickness / 3.0f, depth, x2 + thickness / 3.0f, depth + thickness, row.texture, vertices, indices);
	// Generate front
	generateSquareFront(depth + thickness, x1 - thickness / 3.0f, y1 - thickness / 3.0f, x2 + thickness / 3.0f, y2 + thickness / 3.0f, row.texture, vertices, indices);
}

void Model::generateHandleModel(float x1, float y1, float x2, float y2, Row& row, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	// TO DO
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

		generateColumnsGui(columnCount, columns, "");

		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	return clicked;
}

void Model::generateColumnsGui(int& columnCount, std::vector<Column>& columns, std::string str)
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
			ImGui::InputFloat(("Ratio##" + number).c_str(), &(columns[i].ratio), 1.0f);
			ImGui::InputInt(("Rows##" + number).c_str(), &(columns[i].rowCount));
			generateRowsGui(columns[i].rowCount, columns[i].rows, number);
			ImGui::TreePop();
		}
	}
}

void Model::generateRowsGui(int& rowCount, std::vector<Row>& rows, std::string str)
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
			ImGui::InputFloat(("Ratio##" + number).c_str(), &(rows[i].ratio), 1.0f);
			ImGui::Checkbox(("Recursive##" + number).c_str(), &(rows[i].recursive));
			if (rows[i].recursive)
			{
				ImGui::InputInt(("Columns##" + number).c_str(), &(rows[i].columnCount));
				generateColumnsGui(rows[i].columnCount, rows[i].columns, number);
			}
			else
			{
				ImGui::InputInt("Texture", &(rows[i].texture));
				ImGui::InputInt("Type", &(rows[i].type));
				if (rows[i].type == 1)
				{
					ImGui::InputInt("Handle Position", &(rows[i].handlePosition));
					ImGui::InputInt("Handle Orientation", &(rows[i].handleOrientation));
				}
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
	ratio(1), recursive(false), texture(0), columnCount(1), type(0), handlePosition(0), handleOrientation(0)
{
}
