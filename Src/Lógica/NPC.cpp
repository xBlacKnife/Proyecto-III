#include "NPC.h"
#include <iostream>
#include <PARKEngine/PARKEngine.h>
#include "Matrix/Node.h"
#include "Matrix/Matrix.h"
#include <limits>

NPC::NPC():pq(0), hasPath(false), isInBuilding_(false)
{
}

NPC::~NPC()
{
}
void NPC::start()
{
	//Gets matrix
	matrix_ = SceneManager::instance()->currentState()->getEntitiesWithComponent<Matrix>()[0]->getComponent<Matrix>();

	//PRUEBA
	matrix_->getEntityNode(0)->getComponent<Node>()->setType("Road");


	//Get initial node
	Entity* initialNode = matrix_->getEntityNode(0, 0); //EST�N AL REV�S FILAS Y COLUMNAS
	node_ = initialNode->getComponent<Node>();
	//Set position to it
	Vector3 pos = initialNode->getComponent<Transform>()->getPosition();
	getBrotherComponent<Transform>()->setPosition(pos + Vector3(0, 10, 0));
	//Look for buildings
	lookForBuildings();
}

void NPC::update(unsigned int time)
{
	//Bajar las necesidades (solo si no est� en una atracci�n)
	if(!isInBuilding_)
	{
		float delta = ((float)time / 1000) * exigency_;
		changeStat(fun_, -delta);
		changeStat(hunger_, delta);
		changeStat(peepee_, delta);
	}
	//std::cout << entity_->getName() << "\n" << fun_.name_ << ": " << getFun() << "\n " << 
		//hunger_.name_ << ": " << getHunger() << "\n " << peepee_.name_ << ": " << getPeepee() << std::endl;

	//NPC has an avaiable path
	if(hasPath)
	{
		Node* n = movements.top();
		//Not in that node yet
		if(node_ != n)
		{
			//Move towards it
			moveToNode(n, time);
			//Update current node
			if (isInNode(n))
				setNode(n);
		}
		else
		{
			//Pop movement
			movements.pop();

			//If path ended
			if (movements.empty())
				hasPath = false;
		}
	}
}

void NPC::setNode(Node * node)
{
	node_ = node;
}

Node * NPC::getNode()
{
	return node_;
}

void NPC::load(json file)
{
	speed_ = file["speed"];
	exigency_ = file["exigency"];

	json stat = file["stats"];
	fun_ = Stat(stat[0]["name"], stat[0]["value"], stat[0]["maxValue"], stat[0]["decreases"]);
	hunger_ = Stat(stat[1]["name"], stat[1]["value"], stat[1]["maxValue"], stat[1]["decreases"]);
	peepee_ = Stat(stat[2]["name"], stat[2]["value"], stat[2]["maxValue"], stat[2]["decreases"]);
}

void NPC::lookForBuildings()
{
	//Pillamos variables
	int N = matrix_->getSize(0) * matrix_->getSize(1);
	pq = IndexPQ<int>(N);
	distTo = std::vector<int>(N);
	nodeTo = std::vector<int>(N);

	//Inicializamos las distancias a infinito
	for (int v = 0; v < N; v++)
		distTo[v] = numeric_limits<int>::max();

	
	//Metemos el nodo actual con prioridad 0
	Vector2 nodePos = node_->getMatrixPos(); //ESTO TAMBI�N EST� AL REV�S
	int nodeIndex = calculateIndex(nodePos.y, nodePos.x);
	pq.push(nodeIndex, 0);
	distTo[nodeIndex] = 0; //Distancia 0
	nodeTo[nodeIndex] = nodeIndex;

	bool atraccion = false;
	Node* nodoActual = nullptr;
	//Vamos metiendo y sacando elementos de la cola de prioridades variables
	while (!pq.empty() && !atraccion)
	{
		IndexPQ<int>::Par n = pq.top();
		nodoActual = matrix_->getEntityNode(n.elem)->getComponent<Node>();
		pq.pop();
		list<Entity*> ady = matrix_->getAdj(nodoActual->getEntity(), 1, 1); //radio de 1
		//Adyacentes al nodo actual
		for (Entity* e : ady)
		{
			Vector2 srcPos = nodoActual->getMatrixPos();
			Vector2 adyPos = e->getComponent<Node>()->getMatrixPos();
			//Quitamos diagonales y la propia casilla
			if (adyacenteCorrecta(srcPos, adyPos))
			{
				//Amusement found
				if (e->getComponent<Node>()->getType() == "Patitos")
				{
					nodoActual = e->getComponent <Node>();
					relax(n.elem, calculateIndex(adyPos.y, adyPos.x));
					atraccion = true;
					break;
				}
				//Explore other nodes
				else if(e->getComponent<Node>()->getType() == "Road")
					relax(n.elem, calculateIndex(adyPos.y, adyPos.x));
			}
		}
	}

	//Rellenamos la cola de movimientos
	if (atraccion)
	{
		int index = calculateIndex(nodoActual->getMatrixPos().y, nodoActual->getMatrixPos().x); //ESTO TAMBI�N EST� AL REV�S
		while (nodeTo[index] != index)
		{
			//Get node 
			Node* n = matrix_->getEntityNode(index)->getComponent<Node>();
			//Put it in the element list
			movements.push(n);
			//Previous index
			index = nodeTo[index];
		}
		std::cout << "YENDO A LA ATRACCI�N" << std::endl;
		hasPath = true;
	}
	else
		std::cout << "NO HAY ATRACCIONES DISPONIBLES" << std::endl;
}

void NPC::deambulate()
{
	//HACER QUE SE MUEVA AL SIGUIENTE NODO DE FORMA RANDOM, SIN VOLVER AL SUYO


}

void NPC::relax(int srcIndex, int destIndex)
{
	//std::cout << "Relaxing from " << srcIndex << " to" << destIndex << std::endl;
	if (distTo[destIndex] > distTo[srcIndex] + 1)
	{
		//A�adimos el tiempo de espera de la p�gina en si
		distTo[destIndex] = distTo[srcIndex] + 1;
		nodeTo[destIndex] = srcIndex;
		//En la funci�n update se contempla que la clave no estuviera ya
		pq.update(destIndex, distTo[destIndex]);
	}
}

int NPC::calculateIndex(int i, int j)
{
	return i * matrix_->getSize(1) + j;
}

bool NPC::handleEvent(unsigned int time)
{
	if (InputManager::getSingletonPtr()->isKeyDown("NPC") && !hasPath)
	{
		//Get initial node
		Entity* initialNode = matrix_->getEntityNode(0, 0); //EST�N AL REV�S FILAS Y COLUMNAS
		node_ = initialNode->getComponent<Node>();
		//Set position to it
		Vector3 pos = initialNode->getComponent<Transform>()->getPosition();
		getBrotherComponent<Transform>()->setPosition(pos + Vector3(0, 10, 0));

		//Looks for buildings
		lookForBuildings();
	}
	
	return false;
}


bool NPC::adyacenteCorrecta(Vector2 src, Vector2 dst)
{
	//Es una goddamn puerta XOR
	return ((src.x == dst.x || src.y == dst.y) && (src.x != dst.x || src.y != dst.y));
}

bool NPC::isInNode(Node* n)
{
	Vector3 nodeSize = matrix_->getNodeSize();
	Vector3 newNodeMin = n->getBrotherComponent<Transform>()->getPosition() - nodeSize / 4;
	Vector3 newNodeMax = n->getBrotherComponent<Transform>()->getPosition() + nodeSize / 4;

	//Check AABB
	Vector3 actualPos = getBrotherComponent<Transform>()->getPosition();
	if (actualPos.x > newNodeMin.x && actualPos.x < newNodeMax.x && actualPos.z > newNodeMin.z && actualPos.z < newNodeMax.z)
		return true;
	return false;
}
void NPC::moveToNode(Node* n, int deltaTime)
{
	Transform* trans = getBrotherComponent<Transform>();
	Transform* nextTrans = n->getBrotherComponent<Transform>();

	//Vector unitario de la direcci�n
	Vector3 delta = (nextTrans->getPosition() - trans->getPosition());
	delta.normalise();
	//Lo multiplicamos por el deltaTime y la velocidad del NPC
	delta = delta * speed_ * ((float)deltaTime / 10);
	delta.y = 0;//We dont want to move in that axis

	//Lo movemos
	trans->translate(delta);
}

void NPC::changeStat(Stat & stat, float incr)
{
	//Para ajustarlo a la stat en cuesti�n
	incr /= stat.MAX_VALUE;

	//Le quitamos el icremento y comprobamos l�mites
	stat.value_ += incr;
	if (stat.decreases_ && stat.value_ < 0)
		stat.value_ = 0;
	else if (!stat.decreases_ && stat.value_ > stat.MAX_VALUE)
		stat.value_ = stat.MAX_VALUE;
}
