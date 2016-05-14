#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

#include <iostream>
#include <map>

class Component;
class Object;

typedef Component*(*CreateFunc)(Object*);
typedef std::pair<char*, CreateFunc> CreateItem;
typedef std::map<char*, CreateFunc> CreateDictionary;

class ComponentFactory
{
public:
	
	~ComponentFactory();

	static ComponentFactory* getInstance();

	void registerComponent(char* type, CreateFunc func);

	Component* createComponent(char* type, Object* object);

private:
	ComponentFactory();
	CreateDictionary componentDictionary;
	static ComponentFactory* instance;
};




#endif // !COMPONENT_FACTORY_H