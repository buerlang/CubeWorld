#include "IncludeClass.h"

Material* MaterialList::uiMaterial;
Material* MaterialList::redMaterial;
Material* MaterialList::blueMaterial;
Material* MaterialList::dirtMaterial;
Material* MaterialList::lakeMaterial;
Material* MaterialList::woodMaterial;
Material* MaterialList::mineMaterial;
Material* MaterialList::yellowGradientMaterial;


Material* MaterialList::mat_build_residence;
Material* MaterialList::mat_build_wood;
Material* MaterialList::mat_build_mine;
Material* MaterialList::mat_build_government;

void MaterialList::Initialize()
{
	uiMaterial = Material::create()
		->setShader(ShaderList::UI)
		->setTexture("container.png")
		->setBegin([]() {
		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, uiMaterial->texture);
	})
		->setDraw([](Object* object) {
		UITransform* uiTransform = object->getComponent(UITransform);
		if (uiTransform)
		{
			glUniform2f(uiMaterial->shader->getUniform("_Scale"), uiTransform->scale.x, uiTransform->scale.y);
			glUniform2f(uiMaterial->shader->getUniform("_Position"), uiTransform->getGlobalPosition().x, uiTransform->getGlobalPosition().y);
		}
		UIImage* uiImage = object->getComponent(UIImage);
		if (uiImage)
		{
			glUniform1f(uiMaterial->shader->getUniform("_Opaque"), uiImage->alpha);
		}
	})
		->setHasAlpha(true);

	redMaterial = Material::create()
		->setShader(ShaderList::SingleColor)
		->setBegin([]() {
		glUniform4f(redMaterial->shader->getUniform("_Color"), 1, 0, 0, 1);
	})
		->setDraw([](Object* object) {
		glUniformMatrix4fv(redMaterial->shader->getUniform("_Model"), 1, GL_FALSE, value_ptr(object->getTransform()->getModelMatrix()));
	});

	blueMaterial = Material::create()
		->setShader(ShaderList::SingleColor)
		->setBegin([]() {
		glUniform4f(blueMaterial->shader->getUniform("_Color"), 0, 0, 1, 1);
	})
		->setDraw([](Object* object) {
		glUniformMatrix4fv(blueMaterial->shader->getUniform("_Model"), 1, GL_FALSE, value_ptr(object->getTransform()->getModelMatrix()));
	});

	dirtMaterial = Material::create()
		->setShader(ShaderList::Diffuse)
		->setTexture("terrains\\dirt.png")
		->setBegin([]() {
		glBindTexture(GL_TEXTURE_2D, dirtMaterial->texture);
	});

	lakeMaterial = Material::create()
		->setShader(ShaderList::Diffuse)
		->setTexture("terrains\\lake.png")
		->setBegin([]() {
		glBindTexture(GL_TEXTURE_2D, lakeMaterial->texture);
	});

	woodMaterial = Material::create()
		->setShader(ShaderList::Diffuse)
		->setTexture("terrains\\wood.png")
		->setBegin([]() {
		glBindTexture(GL_TEXTURE_2D, woodMaterial->texture);
	});

	mineMaterial = Material::create()
		->setShader(ShaderList::Diffuse)
		->setTexture("terrains\\mine.png")
		->setBegin([]() {
		glBindTexture(GL_TEXTURE_2D, mineMaterial->texture);
	});

	yellowGradientMaterial = Material::create()
		->setShader(ShaderList::Gradient)
		->setBegin([]() {
		glUniform3f(yellowGradientMaterial->shader->getUniform("_Color"), 1.0f, 1.0f, 0.4f);
	})
		->setDraw([](Object* object) {
		glUniformMatrix4fv(yellowGradientMaterial->shader->getUniform("_Model"), 1, GL_FALSE, value_ptr(object->getTransform()->getModelMatrix()));
	})
		->setHasAlpha(true);

	mat_build_residence = Material::create()
		->setShader(ShaderList::Diffuse_Lighted_Shadow)
		->setTexture("models\\residence.bmp")
		->setBegin([]() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mat_build_residence->texture);
	});

	mat_build_wood = Material::create()
		->setShader(ShaderList::Diffuse_Lighted_Shadow)
		->setTexture("models\\wood.jpg")
		->setBegin([]() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mat_build_wood->texture);
	});

	mat_build_mine = Material::create()
		->setShader(ShaderList::Diffuse_Lighted_Shadow)
		->setTexture("models\\mine.jpg")
		->setBegin([]() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mat_build_mine->texture);
	});

	mat_build_government = Material::create()
		->setShader(ShaderList::Diffuse_Lighted_Shadow)
		->setTexture("models\\government.jpg")
		->setBegin([]() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mat_build_government->texture);
	});

}