#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include "Component.h"

class TestComponent: public Component
{
public:
	Register_Info(TestComponent)



	virtual void start() override
	{
		
	}
	virtual void update() override
	{
		std::cout << "[TestComponent Update Info]: " << "hhhh" << std::endl;
	}
	virtual void onDestroy() override
	{

	}
};



#endif // !TEST_COMPONENT_H
