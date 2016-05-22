#include "IncludeClass.h"

DirectionalLight* DirectionalLight::main;

void DirectionalLight::start()
{
	if (!main)
	{
		main = this;
	}
	object->addComponent(Camera);

	glGenFramebuffers(1, &FBO);
	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DirectionalLight::update()
{
	Camera* camera = object->getComponent(Camera);
	ShaderList::DepthMap->Use();
	glUniformMatrix4fv(glGetUniformLocation(ShaderList::DepthMap->Program, "_LightSpaceProjection"), 1, GL_FALSE, glm::value_ptr(ortho(-10.0f, 10.0f, -10.0f, 10.0f, camera->nearClip, camera->farClip)));
	glUniformMatrix4fv(glGetUniformLocation(ShaderList::DepthMap->Program, "_LightSpaceView"), 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		RenderManager::getInstance()->renderOpaqueWithShader(camera, ShaderList::DepthMap);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Screen::Width, Screen::Height);
}