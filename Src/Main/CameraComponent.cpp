#include "CameraComponent.h"



CameraComponent::CameraComponent(Ogre::SceneManager* scnMgn, Ogre::RenderWindow* wind)
{
	camNode_ = scnMgn->getRootSceneNode()->createChildSceneNode();
	camera_ = GestorRecursos::createCamera(scnMgn, "cam", camNode_, 5, 50000, true);
	camNode_->setPosition(1683, 2000, 2116);
	camNode_->lookAt(Ogre::Vector3(1963, 50, 1660), Ogre::Node::TS_WORLD);
	viewport_ = wind->addViewport(camera_);
	viewport_->setClearEveryFrame(true);
}


CameraComponent::~CameraComponent()
{
}

void CameraComponent::update(unsigned int time)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			//EXIT = true;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			//El control 0 estar parado, el 1 izda, el 2 dcha, el 3 arriba y el 4 abajo
			if (event.key.keysym.sym == SDLK_UP)
			{
				std::cout << "Hola! Funciono Desde un componente" << std::endl;
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE)
			{

			}
		}
	}
}
