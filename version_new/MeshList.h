#ifndef MESH_LIST_H
#define MESH_LIST_H

class Mesh;

class MeshList
{
private:
	MeshList();
public:
	static Mesh* UIQuad;
	static Mesh* pyramid;
	static Mesh* plane;
	static Mesh* tube;
	static Mesh* residence;
	static Mesh* wood;
	static Mesh* mine;
	static Mesh* government;
	static void Initialize();
};

#endif // !MESH_LIST_H

