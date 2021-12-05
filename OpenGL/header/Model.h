#pragma once

#include <vector>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

struct Vertex {
	float position[3];
	float color[3];
	float texture[2];
	float textureType;
};

class Row;
class Column;

class Column
{
	int ratio;
	int rowCount;
	std::vector<Row> rows;
};

class Row
{
	int ratio;
	bool recursive;

	bool texture;
	int columnCount;

	std::vector<Column> columns;
};

class Model
{
public:
	int height;
	int width;
	int depth;
	bool texture;
	int columnCount;

	std::vector<Column> columns;

	void generateModel(std::vector<Vertex>& vertices);
	void generateGUI();

	Model(GLFWwindow* window);
	~Model();

	// Test stuff
	bool show_demo_window = true;
	bool show_another_window = false;
};