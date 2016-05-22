#ifndef MESH_H
#define MESH_H

#include "IncludeStd.h"

struct Vertex
{
	vec3 position = vec3(0, 0, 0);
	vec3 normal = vec3(0, 0, 0);
	vec2 texCoord = vec2(0, 0);

	Vertex()
	{
		
	}
	Vertex(float p1, float p2, float p3)
	{
		position = vec3(p1, p2, p3);
	}
	Vertex(float p1, float p2, float p3, float n1, float n2, float n3, float t1, float t2)
	{
		position = vec3(p1, p2, p3);
		normal = vec3(n1, n2, n3);
		texCoord = vec2(t1, t2);
	}
	Vertex(vec3& position)
	{
		this->position = position;
	}
	Vertex(vec3& position, vec3& normal, vec2& texCoord)
	{
		this->position = position;
		this->normal = normal;
		this->texCoord = texCoord;
	}
};

struct Index
{
	unsigned int first;
	unsigned int second;
	unsigned int third;
	Index() 
	{

	}
	Index(unsigned int first, unsigned int second, unsigned int third)
	{
		this->first = first;
		this->second = second;
		this->third = third;
	}
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	GLuint VAO = 0, VBO = 0, EBO = 0;
	int indicesCount = 0;

	vector<Vertex> vertices;
	vector<Index> indices;

	int getIndexCount();
	int getVertexCount();
	Mesh* genBuffer();
	Mesh* genBuffer(float* vertices, int verticesLength, unsigned int* indices, int indicesLength);
	void updateBuffer();
	Mesh* addVertex(Vertex vertex);
	Mesh* addIndex(Index index);

	Mesh* loadModel(string path, float size);
	void processNode(aiNode* node, const aiScene* scene, float size);
	void processMesh(aiMesh* mesh, float size);
};



#endif // !MESH_H
