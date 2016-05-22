#include "UIImage.h"
#include "IncludeClass.h"

void UIImage::start()
{
	Mesh* UIQuad = new Mesh();
	UIQuad->vertices.push_back(Vertex(0, 200, 0, 0, 0, 0, 0, 0));
	UIQuad->vertices.push_back(Vertex(0, 0, 0, 0, 0, 0, 0, 1));
	UIQuad->vertices.push_back(Vertex(200, 200, 0, 0, 0, 0, 1, 0));
	UIQuad->vertices.push_back(Vertex(200, 0, 0, 0, 0, 0, 1, 1));
	UIQuad->indices.push_back(Index(0, 1, 2));
	UIQuad->indices.push_back(Index(2, 1, 3));
	UIQuad->genBuffer();
	object->addComponent(UITransform)->addComponent(Renderer);
	object->getComponent(Renderer)->setMesh(UIQuad);
	object->getComponent(Renderer)->setMaterial(MaterialList::uiMaterial);
}

UIImage* UIImage::setImage(char* file)
{
	Material* mat = Material::create()
		->setShader(ShaderList::UI)
		->setTexture(file)
		->setBegin([=]() {
		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, object->getComponent(Renderer)->material->texture);
	})
		->setDraw([=](Object* object) {
		UITransform* uiTransform = object->getComponent(UITransform);
		if (uiTransform)
		{
			glUniform2f(object->getComponent(Renderer)->material->shader->getUniform("_Scale"), uiTransform->scale.x, uiTransform->scale.y);
			glUniform2f(object->getComponent(Renderer)->material->shader->getUniform("_Position"), uiTransform->getGlobalPosition().x, uiTransform->getGlobalPosition().y);
		}
		UIImage* uiImage = object->getComponent(UIImage);
		if (uiImage)
		{
			glUniform1f(object->getComponent(Renderer)->material->shader->getUniform("_Opaque"), uiImage->alpha);
		}
	})
		->setHasAlpha(true);
	object->getComponent(Renderer)->setMaterial(mat);
	return this;
}