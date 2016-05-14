#include "IncludeClass.h"

Object::Object()
{
	new(this) Object("New Object");
}

Object::Object(char* name)
{
	this->name = name;
	this->addComponent(Transform);
	ObjectManager::getInstance()->add(this);
}

Object::~Object()
{
	ObjectManager::getInstance()->remove(this);
}

//-- Check if any parent object is inactive.
//-- Return false if some parent is inactive.
bool Object::getActiveInParents()
{
	if (!localActive)
		return false;
	for (Object* i = this; i->parent != nullptr; i = i->parent)
	{
		if (!i->parent->localActive)
			return false;
	}
	return true;
}
//-- Active setting.
void Object::setActive(bool localActive)
{
	this->localActive = localActive;
}

//-- Get if static or not.
bool Object::getIsStatic()
{
	return isStatic;
}
//-- Set if static or not.
void Object::setIsStatic(bool isStatic)
{
	this->isStatic = isStatic;
}

//-- Set Parent Object.
void Object::setParent(Object* parent)
{
	this->parent = parent;
}
//-- Add a child Object.
void Object::addChild(Object* child)
{
	this->children.insert(child);
}
//-- Detach the link from parent object.
void Object::detachParent(Object* child)
{
	if (parent != nullptr)
	{
		parent->detachChild(this);
	}
}
//-- Detach the link from a child object.
void Object::detachChild(Object* child)
{
	if (children.find(child) != children.end())
	{
		child->parent = nullptr;
		children.erase(child);
	}
}

//-- Transform Component.
Transform* Object::getTransform()
{
	return getComponent(Transform);
}

//-- Update function.
//-- Called in every frame.
void Object::update()
{
	if (!components.empty())
	{
		for each (Component* comp in components)
		{
			comp->update();
		}
	}
}

//-- Start function.
//-- Called when object instantiated.
void Object::start()
{
	if (!components.empty())
	{
		for each (Component* comp in components)
		{
			comp->start();
		}
	}
}

//-- OnDestroy function.
//-- Called when object destroyed.
void Object::onDestroy()
{
	if (!components.empty())
	{
		for each (Component* comp in components)
		{
			delete comp;
		}
	}
}

//-- onMouseEnter function.
//-- Called when mouse starts to enter over this object.
void Object::onMouseEnter()
{
	if (!components.empty())
	{
		for each (Component* comp in components)
		{
			comp->onMouseEnter();
		}
	}
}

//-- onMousePress function.
//-- Called when mouse starts to press over this object.
void Object::onMousePress()
{
	if (!components.empty())
	{
		for each (Component* comp in components)
		{
			comp->onMousePress();
		}
	}
}

//-- onMouseLeave function.
//-- Called when mouse starts to leave from this object.
void Object::onMouseLeave()
{
	if (!components.empty())
	{
		for each (Component* comp in components)
		{
			comp->onMouseLeave();
		}
	}
}

//-- onMouseClick function.
//-- Called when mouse starts to click over this object.
void Object::onMouseClick()
{
	if (!components.empty())
	{
		for each (Component* comp in components)
		{
			comp->onMouseClick();
		}
	}
}

//-- onMouseOver function.
//-- Called when mouse remains over this object.
void Object::onMouseOver()
{
	if (!components.empty())
	{
		for each (Component* comp in components)
		{
			comp->onMouseOver();
		}
	}
}

//-- Add a certain type of Component.
Object* Object::addComponentByName(char* type)
{
	Component* comp = ComponentFactory::getInstance()->createComponent(type, this);
	if (comp)
	{
		components.insert(comp);
	}
	return this;
}