#ifndef CW_COMPONENT_H
#define CW_COMPONENT_H

#include "ComponentFactory.h"
#include "IncludeStd.h"

#define Register(name, func) ComponentFactory::getInstance()->registerComponent(name, func)
#define Register_Info(className) \
char* name = #className;\
char* getName()\
{\
	return name;\
}\
static void regist()\
{\
	Register(#className, create);\
}\
static Component* create(Object* object)\
{\
	return new className(object);\
}\
className()\
{\
	\
}\
className(Object* object)\
{\
	this->object = object;\
	start();\
}\
~className()\
{\
	onDestroy();\
}\

class Object;


class Component
{
public:
	Component()
	{
	}
	Component(Object* object)
	{
		this->object = object;
	}

	Object* object = nullptr;

	virtual void start() {}
	virtual void update() {}
	virtual void onDestroy() {}
	virtual void onMouseEnter() {}
	virtual void onMousePress() {}
	virtual void onMouseLeave() {}
	virtual void onMouseClick() {}
	virtual void onMouseOver() {}

	virtual char* getName() { return ""; }
};


#endif // !COMPONENT_H

