#include "IncludeClass.h"

Mesh* MeshList::UIQuad;
Mesh* MeshList::pyramid;
Mesh* MeshList::plane;
Mesh* MeshList::tube;
Mesh* MeshList::residence;
Mesh* MeshList::wood;
Mesh* MeshList::mine;
Mesh* MeshList::government;

void MeshList::Initialize()
{
	UIQuad = (new Mesh())
		->addVertex(Vertex(0, 200, 0, 0, 0, 0, 0, 0))
		->addVertex(Vertex(0, 0, 0, 0, 0, 0, 0, 1))
		->addVertex(Vertex(200, 200, 0, 0, 0, 0, 1, 0))
		->addVertex(Vertex(200, 0, 0, 0, 0, 0, 1, 1))
		->addIndex(Index(0, 1, 2))
		->addIndex(Index(2, 1, 3))
		->genBuffer();

	pyramid = (new Mesh())
		->addVertex(Vertex(0.0f, 0.0f, -0.0f))
		->addVertex(Vertex(0.0f, 1.0f, -0.3f))
		->addVertex(Vertex(-0.4f, 1.0f, 0.2f))
		->addVertex(Vertex(0.4f, 1.0f, 0.2f))
		->addIndex(Index(0, 1, 2))
		->addIndex(Index(0, 2, 3))
		->addIndex(Index(0, 3, 1))
		->addIndex(Index(1, 2, 3))
		->genBuffer();
	
	plane = (new Mesh())
		->addVertex(Vertex(-0.5f, 0, 0.5f, 0, 0, 0, 0, 0))
		->addVertex(Vertex(-0.5f, 0, -0.5f, 0, 0, 0, 0, 1))
		->addVertex(Vertex(0.5f, 0, 0.5f, 0, 0, 0, 1, 0))
		->addVertex(Vertex(0.5f, 0, -0.5f, 0, 0, 0, 1, 1))
		->addIndex(Index(0, 1, 2))
		->addIndex(Index(2, 1, 3))
		->genBuffer();

	tube = (new Mesh())
		->addVertex(Vertex(-0.5f, 0, 0.5f, 0, 0, 0, 0, 0))
		->addVertex(Vertex(0.5f, 0, 0.5f, 0, 0, 0, 0, 0))
		->addVertex(Vertex(0.5f, 0, -0.5f, 0, 0, 0, 0, 0))
		->addVertex(Vertex(-0.5f, 0, -0.5f, 0, 0, 0, 0, 0))
		->addVertex(Vertex(-0.5f, 3, 0.5f, 0, 0, 0, 1, 0))
		->addVertex(Vertex(0.5f, 3, 0.5f, 0, 0, 0, 1, 0))
		->addVertex(Vertex(0.5f, 3, -0.5f, 0, 0, 0, 1, 0))
		->addVertex(Vertex(-0.5f, 3, -0.5f, 0, 0, 0, 1, 0))
		->addIndex(Index(0, 1, 4))
		->addIndex(Index(4, 1, 5))
		->addIndex(Index(1, 2, 5))
		->addIndex(Index(5, 2, 6))
		->addIndex(Index(2, 3, 6))
		->addIndex(Index(6, 3, 7))
		->addIndex(Index(3, 0, 7))
		->addIndex(Index(7, 0, 4))
		->genBuffer();

	residence = (new Mesh())
		->loadModel("models\\residence.obj", 0.01f)
		->genBuffer();
	wood = (new Mesh())
		->loadModel("models\\wood.obj", 0.013f)
		->genBuffer();
	mine = (new Mesh())
		->loadModel("models\\mine.obj", 0.06f)
		->genBuffer();
	government = (new Mesh())
		->loadModel("models\\government.obj", 0.018f)
		->genBuffer();
}