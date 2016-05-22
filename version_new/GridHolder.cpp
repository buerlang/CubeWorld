#include "IncludeClass.h"
#include "IncludeStd.h"

void GridHolder::start()
{
	object->pickable = true;
	object->addComponent(BoxCollider);
	object->getComponent(BoxCollider)->setBox(vec3(-0.5f, -0.5f, -0.5f), vec3(MAPWIDTH + 0.5f, 0.5f, MAPHEIGHT + 0.5f));
	for (int i = 0; i < MAPWIDTH; i++)
	{
		for (int j = 0; j < MAPHEIGHT; j++)
		{
			genMap();


			terrainObjects[i][j] = (new Object("terrain"))->addComponent(Renderer);
			terrainObjects[i][j]->setIsStatic(true);
			terrainObjects[i][j]->getComponent(Renderer)->setMesh(MeshList::plane);
			terrainObjects[i][j]->getComponent(Renderer)->setMaterial(getMaterialByType(cityMap[i][j].terrainType));
			terrainObjects[i][j]->getTransform()->localPosition = vec3(i, 0, j);
			terrainObjects[i][j]->setParent(object);

			buildingObjects[i][j] = (new Object("building"))->addComponent(Renderer);
			if (cityMap[i][j].buildingType != BUILDING_NONE)
			{
				buildingObjects[i][j]->getComponent(Renderer)->setMesh(getMeshByType(cityMap[i][j].buildingType));
				buildingObjects[i][j]->getComponent(Renderer)->setMaterial(getMaterialByType(cityMap[i][j].buildingType));
			}
			buildingObjects[i][j]->getTransform()->localPosition = vec3(0, 0.01f, 0);
			buildingObjects[i][j]->setParent(terrainObjects[i][j]);
		}
	}

	selection = (new Object("selection"))->addComponent(Renderer);
	selection->getComponent(Renderer)->setMesh(MeshList::tube);
	selection->getComponent(Renderer)->setMaterial(MaterialList::yellowGradientMaterial);
	selection->setParent(object);
	selection->setActive(false);
}

void GridHolder::update()
{
	for (int i = 0; i < MAPWIDTH; i++)
	{
		for (int j = 0; j < MAPHEIGHT; j++)
		{
			if (cityMap[i][j].dirty)
			{
				if (cityMap[i][j].buildingType != BUILDING_NONE)
				{
					buildingObjects[i][j]->getComponent(Renderer)->setMesh(getMeshByType(cityMap[i][j].buildingType));
					buildingObjects[i][j]->getComponent(Renderer)->setMaterial(getMaterialByType(cityMap[i][j].buildingType));
				}
				else
				{
					buildingObjects[i][j]->getComponent(Renderer)->setMesh(nullptr);
					buildingObjects[i][j]->getComponent(Renderer)->setMaterial(nullptr);
				}
				cityMap[i][j].dirty = false;
			}		
		}
	}
}

void GridHolder::onMouseEnter()
{
	selection->setActive(true);
	onMouseOver();
}

void GridHolder::onMouseOver()
{
	vec3 p = PickManager::getInstance()->pickPoint;
	pickX = (int)(p.x + 0.5f);
	pickZ = (int)(p.z + 0.5f);
	selection->getTransform()->localPosition = vec3(pickX, 0, pickZ);

	if (toBuild && InputManager::getInstance()->getMouseButtonDown(MOUSE_LEFT))
	{
		if (canBuildThis(pickX, pickZ, toBuild))
		{
			cityMap[pickX][pickZ].buildingType = toBuild;
			cityMap[pickX][pickZ].dirty = true;
		}
	}
}

void GridHolder::onMouseLeave()
{
	selection->setActive(false);
}

void GridHolder::onMouseClick()
{

}

void GridHolder::genMap()
{
	srand((int)time(0));
	for (int i = 0; i < MAPWIDTH; i++)
	{
		for (int j = 0; j < MAPHEIGHT; j++)
		{
			cityMap[i][j].terrainType = (TerrainEnum)(rand() % TERRAIN_MAX_COUNT);
		}
	}
}

Material* GridHolder::getMaterialByType(TerrainEnum type)
{
	switch(type)
	{
	case TERRAIN_DIRT:
		return MaterialList::dirtMaterial;
	case TERRAIN_LAKE:
		return MaterialList::lakeMaterial;
	case TERRAIN_MINE:
		return MaterialList::mineMaterial;
	case TERRAIN_WOOD:
		return MaterialList::woodMaterial;
	default:
		return MaterialList::redMaterial;
	}
}

Mesh* GridHolder::getMeshByType(BuildingEnum type)
{
	switch (type)
	{
	case BUILDING_GOVERNMENT:
		return MeshList::government;
	case BUILDING_MINE:
		return MeshList::mine;
	case BUILDING_RESIDENCE:
		return MeshList::residence;
	case BUILDING_WOOD:
		return MeshList::wood;
	case BUILDING_ROAD:
	default:
		return MeshList::pyramid;
	}
}

Material* GridHolder::getMaterialByType(BuildingEnum type)
{
	switch (type)
	{
	case BUILDING_GOVERNMENT:
		return MaterialList::mat_build_government;
	case BUILDING_MINE:
		return MaterialList::mat_build_mine;
	case BUILDING_RESIDENCE:
		return MaterialList::mat_build_residence;
	case BUILDING_WOOD:
		return MaterialList::mat_build_wood;
	case BUILDING_ROAD:
	default:
		return MaterialList::redMaterial;
	}
}

bool GridHolder::canBuildThis(int x, int z, BuildingEnum type)
{
	TerrainEnum t = cityMap[x][z].terrainType;
	if (cityMap[x][z].buildingType == BUILDING_NONE)
	{
		if (t == TERRAIN_WOOD && type == BUILDING_WOOD)
			return true;
		if (t == TERRAIN_MINE && type == BUILDING_MINE)
			return true;
		if (t == TERRAIN_DIRT && (type == BUILDING_GOVERNMENT || type == BUILDING_RESIDENCE))
			return true;
	}
	return false;
}