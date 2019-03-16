#pragma once
#include "Component.h""
#include "Transform.h"
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "OgreSystem.h"

class MeshRenderer : public Component
{
public:

	//Crea una entidad renderizable a partir del nombre de su malla y una posici�n inicial
	MeshRenderer(std::string meshName);

	~MeshRenderer();

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual bool handleEvent(SDL_Event* e, unsigned int time);
	virtual void receive(Message* msg) {};

	//Devuelve el nodo de Ogre
	virtual Ogre::SceneNode* getNode() { return node_; };

protected:
	Transform * transform_ = nullptr;
	Ogre::SceneNode* node_;

};

