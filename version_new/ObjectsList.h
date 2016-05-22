#ifndef OBJECTS_LIST
#define OBJECTS_LIST

class Object;

class ObjectsList
{
private:
	ObjectsList();
public:
	static Object* mainCamera;
	static Object* mainLight;
	static Object* cityMap;

	static Object* img_coin;
	static Object* img_population;
	static Object* img_wood;
	static Object* img_mine;
	static Object* img_day;
	static Object* btn_pause;
	static Object* btn_build;
	static Object* btn_residence;
	static Object* btn_wood;
	static Object* btn_mine;
	static Object* btn_government;
	static void Initialize();
};



#endif // !OBJECTS_LIST
