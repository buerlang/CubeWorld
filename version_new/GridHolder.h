#ifndef GRID_HOLDER_H
#define GRID_HOLDER_H


#include "Component.h"

#define MAPWIDTH 50
#define MAPHEIGHT 50

enum TerrainEnum
{
	TERRAIN_DIRT,
	TERRAIN_WOOD,
	TERRAIN_MINE,
	TERRAIN_LAKE,
	TERRAIN_MAX_COUNT,
};

enum BuildingEnum
{
	BUILDING_NONE,
	BUILDING_GOVERNMENT,
	BUILDING_ROAD,
	BUILDING_MINE,
	BUILDING_WOOD,
	BUILDING_RESIDENCE,
	BUILDING_MAX_COUNT
};

struct Grid
{
	TerrainEnum terrainType = TERRAIN_DIRT;
	BuildingEnum buildingType = BUILDING_NONE;
	int metadata = 0;
	bool dirty = false;
};

class GridHolder :
	public Component
{
public:
	Register_Info(GridHolder);

	Object* terrainObjects[MAPWIDTH][MAPHEIGHT];
	Object* buildingObjects[MAPWIDTH][MAPHEIGHT];
	Grid cityMap[MAPWIDTH][MAPHEIGHT];
	Object* selection;
	BuildingEnum toBuild = BUILDING_NONE;
	int pickX = -1, pickZ = -1;

	virtual void start() override;
	virtual void update() override;
	virtual void onMouseEnter() override;
	virtual void onMouseOver() override;
	virtual void onMouseLeave() override;
	virtual void onMouseClick() override;
	void genMap();
	Material* getMaterialByType(TerrainEnum type);
	Mesh* getMeshByType(BuildingEnum type);
	Material* getMaterialByType(BuildingEnum type);
	bool canBuildThis(int x, int z, BuildingEnum type);
};



#endif // !GRID_HOLDER_H
