#include "IncludeStd.h"
#include "Component.h"

class Camera :
	public Component
{
public:
	Register_Info(Camera)

	static Camera* mainCamera;

	float fieldOfView = 45.0f;
	float nearClip = 0.1f;
	float farClip = 100.0f;

	virtual void start() override;
	virtual void update() override;
	virtual void onDestroy() override;

	mat4 getViewMatrix();
	mat4 getProjectionMatrix();
	void setLookAt(vec3 at);
};

