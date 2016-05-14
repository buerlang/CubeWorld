#ifndef OBJECT_H
#define OBJECT_H

#include "IncludeStd.h"

#include "ComponentFactory.h"

class Component;
class Transform;

#define getComponent(className) getComponentByName<className>(#className)
#define addComponent(className) addComponentByName(#className)
#define NameOf(className) #className

class Object
{
public:
	//=========================================== Constructors & Destructor ===============================================//
	
	Object();
	Object(char* name);
	virtual ~Object();

	//================================================ public variables ======================================================//
	
	//-- The custom name of this Object.
	char* name;
	//-- Whether this object should be updated.
	bool localActive = true;
	//-- Parent object.
	Object* parent = nullptr;
	
	//================================================ public functions ====================================================//

	//-- Get if static or not.
	bool getIsStatic();
	//-- Set if static or not.
	//-- DO NOT do this call after setMaterial().
	void setIsStatic(bool isStatic);
		
	//-- Check if any parent object is inactive.
	//-- Return false if some parent is inactive.
	bool getActiveInParents();
	//-- Active setting.
	void setActive(bool localActive);

	//-- Set Parent Object.
	void setParent(Object* parent);
	//-- Add a child Object.
	void addChild(Object* child);
	//-- Detach the link from parent object.
	void detachParent(Object* child);
	//-- Detach the link from a child object.
	void detachChild(Object* child);

	//-- Transform Component.
	Transform* getTransform();

	//-- Update function.
	//-- Called in every frame.
	void update();

	//-- Start function.
	//-- Called when object instantiated.
	void start();

	//-- OnDestroy function.
	//-- Called when object destroyed.
	void onDestroy();

	//-- onMouseEnter function.
	//-- Called when mouse starts to enter over this object.
	void onMouseEnter();

	//-- onMousePress function.
	//-- Called when mouse starts to press over this object.
	void onMousePress();

	//-- onMouseLeave function.
	//-- Called when mouse starts to leave from this object.
	void onMouseLeave();

	//-- onMouseClick function.
	//-- Called when mouse starts to click over this object.
	void onMouseClick();

	//-- onMouseOver function.
	//-- Called when mouse remain over this object.
	void onMouseOver();
	
	//-- Get a certain type of Component.
	template<typename T> T* getComponentByName(char* type)
	{
		if (!components.empty())
		{
			for each (Component* comp in components)
			{
				//std::cout << type << "||" << comp->getName() << std::endl;
				if (strcmp(type, comp->getName()) == 0)
				{
					return (T*)comp;
				}
			}
		}
		return nullptr;
	}

	//-- Add a certain type of Component.
	Object* addComponentByName(char* type);


protected:
	//================================================= protected variables ===============================================//

	//-- Set of children objects.
	std::set<Object*> children;
	//-- Set of components.
	std::set<Component*> components;
	//-- If static, this object would be auto batched.
	bool isStatic = false;
};


#endif // !OBJECT_H
