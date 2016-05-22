#include "IncludeClass.h"

Object* ObjectsList::mainCamera;
Object* ObjectsList::mainLight;
Object* ObjectsList::cityMap;

Object* ObjectsList::img_coin;
Object* ObjectsList::img_population;
Object* ObjectsList::img_wood;
Object* ObjectsList::img_mine;
Object* ObjectsList::img_day;
Object* ObjectsList::btn_pause;
Object* ObjectsList::btn_build;

Object* ObjectsList::btn_residence;
Object* ObjectsList::btn_wood;
Object* ObjectsList::btn_mine;
Object* ObjectsList::btn_government;

void ObjectsList::Initialize()
{
	mainCamera = (new Object("Main Camera"))->addComponent(Camera)/*->addComponent(CameraControl)*/;
	mainCamera->getTransform()->localPosition = vec3(10, 2, 10);
	mainCamera->getTransform()->localRotation = vec3(-45, 0, 0);
	Camera::mainCamera = mainCamera->getComponent(Camera);

	mainLight = (new Object("main light"))->addComponent(DirectionalLight);
	mainLight->getComponent(Camera)->Position = vec3(10, 10, 10);
	mainLight->getComponent(Camera)->TargetPosition = vec3(25, 0, 0);

	cityMap = (new Object("map"))->addComponent(GridHolder);

	img_coin = (new Object("img_coin"))->addComponent(UIImage);
	img_coin->getComponent(UIImage)->setImage("images\\UI\\img_money.png");
	img_coin->getComponent(UITransform)->setSize(120, 60)->setAlignment(UI_TOP, -240, -20);
	
	img_population = (new Object("img_population"))->addComponent(UIImage);
	img_population->getComponent(UIImage)->setImage("images\\UI\\img_population.png");
	img_population->getComponent(UITransform)->setSize(120, 60)->setAlignment(UI_TOP, -80, -20);
	
	img_wood = (new Object("img_wood"))->addComponent(UIImage);
	img_wood->getComponent(UIImage)->setImage("images\\UI\\img_wood.png");
	img_wood->getComponent(UITransform)->setSize(120, 60)->setAlignment(UI_TOP, 80, -20);
	
	img_mine = (new Object("img_mine"))->addComponent(UIImage);
	img_mine->getComponent(UIImage)->setImage("images\\UI\\img_mine.png");
	img_mine->getComponent(UITransform)->setSize(120, 60)->setAlignment(UI_TOP, 240, -20);
	
	btn_government = (new Object("btn_government"))->addComponent(UIButton);
	btn_government->getComponent(UIImage)->setImage("images\\UI\\btn_government.png");
	btn_government->getComponent(UITransform)->setSize(120, 80)->setAlignment(UI_RIGHT, 0, 150);
	btn_government->getComponent(UIButton)->onClick = []() { ObjectsList::cityMap->getComponent(GridHolder)->toBuild = BUILDING_GOVERNMENT; };

	btn_residence = (new Object("btn_residence"))->addComponent(UIButton);
	btn_residence->getComponent(UIImage)->setImage("images\\UI\\btn_residence.png");
	btn_residence->getComponent(UITransform)->setSize(120, 80)->setAlignment(UI_RIGHT, 0, 50);
	btn_residence->getComponent(UIButton)->onClick = []() { ObjectsList::cityMap->getComponent(GridHolder)->toBuild = BUILDING_RESIDENCE; };

	btn_wood = (new Object("btn_wood"))->addComponent(UIButton);
	btn_wood->getComponent(UIImage)->setImage("images\\UI\\btn_wood.png");
	btn_wood->getComponent(UITransform)->setSize(120, 80)->setAlignment(UI_RIGHT, 0, -50);
	btn_wood->getComponent(UIButton)->onClick = []() { ObjectsList::cityMap->getComponent(GridHolder)->toBuild = BUILDING_WOOD; };

	btn_mine = (new Object("btn_mine"))->addComponent(UIButton);
	btn_mine->getComponent(UIImage)->setImage("images\\UI\\btn_mine.png");
	btn_mine->getComponent(UITransform)->setSize(120, 80)->setAlignment(UI_RIGHT, 0, -150);
	btn_mine->getComponent(UIButton)->onClick = []() { ObjectsList::cityMap->getComponent(GridHolder)->toBuild = BUILDING_MINE; };

	img_day;
	btn_pause;
	btn_build;
}