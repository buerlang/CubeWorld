#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

int Mesh::getIndexCount()
{
	return indices.size();
}
int Mesh::getVertexCount()
{
	return vertices.size();
}

void Mesh::genBuffer()
{
	genBuffer(
		&vertices[0].position.x,
		vertices.size() * sizeof(Vertex),
		&indices[0].first,
		indices.size() * sizeof(Index));
}

void Mesh::genBuffer(float* verteces, int vertecesLength, unsigned int* indeces, int indecesLength)
{
	indicesCount = indecesLength / sizeof(unsigned int);

	// Bind VAO
	GLuint EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertecesLength, verteces, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indecesLength, indeces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}