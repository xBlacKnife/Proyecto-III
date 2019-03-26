#pragma once
#include "Arquitectura/Component.h"

class NPC : public Component
{
public:
	NPC();
	~NPC();

	void load(json file);
	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time) {};
	virtual bool handleEvent(unsigned int time) { return false; };
	virtual void receive(Message* msg) {};

private:
	int hunger;
	int thirst;
};