#include "IncludeClass.h"

ComponentFactory* ComponentFactory::instance;

ComponentFactory::ComponentFactory()
{
}


ComponentFactory::~ComponentFactory()
{
}

ComponentFactory* ComponentFactory::getInstance()
{
	if (instance == nullptr)
		instance = new ComponentFactory();
	return instance;
}

void ComponentFactory::registerComponent(char* type, CreateFunc func)
{
	//std::cout << "registering" << std::endl;
	CreateDictionary::iterator it = componentDictionary.find(type);
	if (it == componentDictionary.end())
	{
		//std::cout << "register" << std::endl;
		componentDictionary.insert(CreateItem(type, func));
	}
}
Component* ComponentFactory::createComponent(char* type, Object* object)
{
	//std::cout << "creating" << std::endl;
	CreateDictionary::iterator it = componentDictionary.find(type);
	if (it != componentDictionary.end())
	{
		//std::cout << "created" << std::endl;
		return it->second(object);
	}
	return nullptr;
}