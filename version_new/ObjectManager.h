#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <list>
#include "Object.h"

class ObjectManager
{
public:
	~ObjectManager();

	static ObjectManager* getInstance();

	//-- Add a new object to the object Manager.
	//-- Object must be pre-initialized.
	void add(Object* object);

	//-- Remove an object from the list.
	void remove(Object* object);

	//-- Draw all the objects.
	virtual void update();

private:
	ObjectManager();
	static ObjectManager* instance;
	//-- List for storing all the objects.
	std::list<Object*> objects;
};



#endif // !OBJECT_MANAGER_H

