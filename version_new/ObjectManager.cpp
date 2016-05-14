#include "ObjectManager.h"

ObjectManager* ObjectManager::instance;

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

ObjectManager* ObjectManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ObjectManager();
	}
	return instance;
}

//-- Add a new object to the object Manager.
//-- Object must be pre-initialized.
void ObjectManager::add(Object* object)
{
	objects.push_back(object);
}

//-- Remove an object from the list.
void ObjectManager::remove(Object* object)
{
	objects.remove(object);
}

//-- Draw all the objects.
void ObjectManager::update()
{
	for each (Object* obj in objects)
	{
		if (obj->getActiveInParents())
		{
			obj->update();
		}
	}
}