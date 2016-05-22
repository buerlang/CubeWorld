#ifndef MATERIAL_LIST_H
#define MATERIAL_LIST_H

class Material;

class MaterialList
{
private:
	MaterialList();
public:
	static Material* uiMaterial;
	static Material* redMaterial;
	static Material* blueMaterial;
	static Material* dirtMaterial;
	static Material* lakeMaterial;
	static Material* woodMaterial;
	static Material* mineMaterial;

	static Material* mat_build_residence;
	static Material* mat_build_wood;
	static Material* mat_build_mine;
	static Material* mat_build_government;

	static Material* yellowGradientMaterial;

	static void Initialize();
};




#endif // !MATERIAL_LIST_H
