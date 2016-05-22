#include "IncludeClass.h"

Shader* ShaderList::UI;
Shader* ShaderList::SingleColor;
Shader* ShaderList::Gradient;
Shader* ShaderList::Diffuse;
Shader* ShaderList::DepthMap;
Shader* ShaderList::Diffuse_Lighted_Shadow;

void ShaderList::Initialize()
{
	UI = (new Shader("shaders\\UIVertex.vert", "shaders\\UIFragment.frag"))
		->registerUniform("_Position")
		->registerUniform("_Sink")
		->registerUniform("_Scale")
		->registerUniform("_ScrSize")
		->registerUniform("_Image")
		->registerUniform("_UVFactor")
		->registerUniform("_Emission")
		->registerUniform("_Opaque")
		->setBegin([]() {
		glUniform2f(UI->getUniform("_ScrSize"), Screen::Width, Screen::Height);
		glUniform1i(UI->getUniform("_Image"), 0);
		glUniform3f(UI->getUniform("_Emission"), 0.0f, 0.0f, 0.0f);
		glUniform2f(UI->getUniform("_Sink"), 0.0f, 0.0f);
		glUniform1f(UI->getUniform("_UVFactor"), 0.0f);
		glUniform1f(UI->getUniform("_Opaque"), 1);
		glUniform2f(UI->getUniform("_Scale"), 1.0f, 1.0f);
		glUniform2f(UI->getUniform("_Position"), 0.0f, 0.0f);
	});

	SingleColor = (new Shader("shaders\\SingleColor.vert", "shaders\\SingleColor.frag"))
		->registerUniform("_Model")
		->registerUniform("_View")
		->registerUniform("_Projection")
		->registerUniform("_Color")
		->setBegin([]() {
		glUniform4f(SingleColor->getUniform("_Color"), 0, 0, 0, 1);
	});

	Diffuse = (new Shader("shaders\\Diffuse.vert", "shaders\\Diffuse.frag"))
		->registerUniform("_Model")
		->registerUniform("_View")
		->registerUniform("_Projection")
		->registerUniform("_Image")
		->setBegin([]() {
		glUniform1i(Diffuse->getUniform("_Image"), 0);
	});

	Gradient = (new Shader("shaders\\Gradient.vert", "shaders\\Gradient.frag"))
		->registerUniform("_Model")
		->registerUniform("_View")
		->registerUniform("_Projection")
		->registerUniform("_Color")
		->setBegin([]() {
		glUniform3f(Gradient->getUniform("_Color"), 1.0f, 1.0f, 1.0f);
	});

	DepthMap = (new Shader("shaders\\shadow_mapping_depth.vert", "shaders\\shadow_mapping_depth.frag"))
		->registerUniform("_LightSpaceProjection")
		->registerUniform("_LightSpaceView")
		->registerUniform("_Model");

	Diffuse_Lighted_Shadow = (new Shader("shaders\\shadow_mapping.vert", "shaders\\shadow_mapping.frag"))
		->registerUniform("_LightSpaceMatrix")
		->registerUniform("_Model")
		->registerUniform("_View")
		->registerUniform("_Projection")
		->registerUniform("_DiffuseTexture")
		->registerUniform("_ShadowMap")
		->registerUniform("_LightPos")
		->registerUniform("_ViewPos")
		->registerUniform("_Shadows")
		->setBegin([]() {
		Camera* camera = DirectionalLight::main->object->getComponent(Camera);
		glUniform1i(Diffuse_Lighted_Shadow->getUniform("_DiffuseTexture"), 0);
		glUniform1i(Diffuse_Lighted_Shadow->getUniform("_ShadowMap"), 1);
		glUniformMatrix4fv(Diffuse_Lighted_Shadow->getUniform("_Projection"), 1, GL_FALSE, value_ptr(Camera::mainCamera->getProjectionMatrix()));
		glUniformMatrix4fv(Diffuse_Lighted_Shadow->getUniform("_View"), 1, GL_FALSE, value_ptr(Camera::mainCamera->getViewMatrix()));
		glUniform3fv(Diffuse_Lighted_Shadow->getUniform("_LightPos"), 1, value_ptr(camera->Position));
		glUniform3fv(Diffuse_Lighted_Shadow->getUniform("_ViewPos"), 1, value_ptr(Camera::mainCamera->Position));
		glUniformMatrix4fv(Diffuse_Lighted_Shadow->getUniform("_LightSpaceMatrix"), 1, GL_FALSE, value_ptr(ortho(-10.0f, 10.0f, -10.0f, 10.0f, camera->nearClip, camera->farClip) * camera->getViewMatrix()));
		glUniform1i(Diffuse_Lighted_Shadow->getUniform("_Shadows"), true);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, DirectionalLight::main->shadowMap);
	});
}