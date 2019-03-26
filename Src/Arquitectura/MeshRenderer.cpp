#include "MeshRenderer.h"

#include "Entity.h"
#include "Transform.h"


#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "OgreSystem.h"
#include <iostream>




MeshRenderer::MeshRenderer(): node_(nullptr), transform_(nullptr)
{
}

MeshRenderer::MeshRenderer(std::string meshName, bool visible)
{
	Ogre::Entity* ogreEntity = OgreSystem::instance()->getSM()->createEntity(meshName);
	node_ = OgreSystem::instance()->getSM()->getRootSceneNode()->createChildSceneNode();
	node_->attachObject(ogreEntity);
	node_->setVisible(visible);
}

void MeshRenderer::load(json file)
{
	std::string meshName = file["mesh"];
	Ogre::Entity* ogreEntity = OgreSystem::instance()->getSM()->createEntity(meshName);
	node_ = OgreSystem::instance()->getSM()->getRootSceneNode()->createChildSceneNode();
	node_->attachObject(ogreEntity);
	node_->setVisible(file["visible"]);
}

MeshRenderer::~MeshRenderer()
{
	
}

void MeshRenderer::start()
{
	transform_ = entity_->getComponent<Transform>();
	if (transform_ == nullptr)
		std::cout << "ERROR: ENTITY " + entity_->getName() + " IS LACKING TRANSFORM COMPONENT" << std::endl;
}

void MeshRenderer::update(unsigned int time)
{
	if(transform_ != nullptr)
	{
		node_->setPosition(transform_->getPosition());
		node_->setOrientation(transform_->getOrientation());
		node_->setScale(transform_->getScale());
	}
}

bool MeshRenderer::handleEvent(unsigned int time)
{
	
	return false;
}
