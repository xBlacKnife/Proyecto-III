#include "NPCManager.h"
#include <PARKEngine/PARKEngine.h>
#include "NPC.h"
#include "PARKMessages.h"

NPCManager::NPCManager(): actualTime_(0)
{

}

NPCManager::~NPCManager()
{
	std::cout << "Destructora de NPCManager" << std::endl;
}

void NPCManager::load(json file)
{
	addParameter(enterTime_, file["enterTime"]); 
	enterTime_ *= 1000; //ms
}


void NPCManager::update(unsigned int time)
{
	actualTime_ += time;
	if(actualTime_>=enterTime_)
	{
		//Spams NPC
		Entity* npc = EntityFactory::Instance()->createEntityFromBlueprint("NPC");
		SceneManager::instance()->currentState()->addEntity(npc);
		npc->start();

		//Puts it in PARK
		npcList_.push_back(npc->getComponent<NPC>());
		send(&Message(NPC_IN));

		actualTime_ = 0;
	}
}

bool NPCManager::handleEvent(unsigned int time)
{

	if (InputManager::instance()->isKeyDown("SelectNPC"))
	{

		pair<Entity*, Ogre::Vector3> nodeAndPos = OgreManager::instance()->raycastToMouse();
		Entity* selected = nodeAndPos.first;
		if (selected != nullptr && selected->getComponent<NPC>() != nullptr)
			send(&NPCSelected(NPC_SELECTED, selected->getComponent<NPC>()));		
	}
	return false;
}


void NPCManager::receive(Message * msg)
{

}



