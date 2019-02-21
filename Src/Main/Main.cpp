#include <iostream>
#include "PruebaLib/saluda.h"
#include <OgreRoot.h>
#include "initOgreApplication.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <list>
#include <OgreResourceGroupManager.h>
#include <OgreStringVector.h>
#include <OgreCamera.h>

int main()
{
	Ogre::Root* root;
    #if _DEBUG
		root = new Ogre::Root("plugins_d.cfg");
    #else 	
		root = new Ogre::Root("plugins.cfg");
	#endif

	initOgreApplication* Ogreinit = new initOgreApplication(root);

	Ogre::SceneManager* scnMgr = Ogreinit->getSceneManager();

	scnMgr->createEntity("ogrehead.mesh");

	system("pause");


	return 0;
}
