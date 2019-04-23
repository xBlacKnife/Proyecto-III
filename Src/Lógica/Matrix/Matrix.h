#pragma once
#include "PARKEngine/Component.h"
#include <vector>

class Entity;

using namespace std;
class Matrix : public Component
{
public:
	Matrix();
	~Matrix();

	virtual void start();

	virtual void load(json file);

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time) {};
	virtual bool handleEvent(unsigned int time) { return false; };
	virtual void receive(Message* msg) {};

	vector<vector<Entity*>> getMatrix();
	Entity* getEntityNode(int i, int j);
	list<Entity*> getAdj(Entity* e, int x, int y);

	//Devuelve adyacentes especificando indice
	Entity* getEntityNode(int index);
	//Pa pillar el tama�o
	int getSize(int i) { if (i == 0) return matrix_.size(); else return matrix_.at(0).size(); };

	Ogre::Vector3 getNodeSize();
	bool limits(int i, int j);

private:
	Ogre::Vector2 mSize_;
	Ogre::Vector3 nSize_;
	vector<vector<Entity*>> matrix_;
	std::list<Component*> comps;
	
	void createMatrix();
	Vector3 getPosIni();

	json matrixFile;
};

REGISTER_TYPE(Matrix)