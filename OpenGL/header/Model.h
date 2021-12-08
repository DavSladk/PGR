#pragma once

#include <vector>
#include <string>
#include <iostream>
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
public:
	Column();
	int ratio;
	int rowCount;
	std::vector<Row> rows;
};

class Row
{
public:
	Row();
	int ratio;
	bool recursive;

	int texture;
	int columnCount;

	std::vector<Column> columns;
};

class Model
{
public:
	float height;
	float width;
	float depth;
	int texture;
	int columnCount;

	unsigned int offset = 0;
	float thickness = 0.02f;

	std::vector<Column> columns;

	void generateModel( std::vector<Vertex>& vertices , std::vector<unsigned int> &indices);
	void generateSquareSide(float constant, float y1, float z1, float y2, float z2, int tex, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	void generateSquareFront(float constant, float x1, float y1, float x2, float y2, int tex, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	void generateSquareFlat(float constant, float x1, float z1, float x2, float z2, int tex, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

	bool generateGUI();
	void generateColumns(int &columnCount, std::vector<Column> &columns, std::string str);
	void generateRows(int &rowCount, std::vector<Row>& columns, std::string str);

	Model(GLFWwindow* window);
	~Model();

	// Test stuff
	bool show_demo_window = true;
	bool show_another_window = false;
};