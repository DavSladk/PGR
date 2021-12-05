#pragma once

#include <vector>

struct Vertex {
	float position[3];
	float color[3];
	float texture[2];
	float textureType;
};

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

	Model();
	~Model();
};