#include "Game.h"


int main(int argc, char* argv[])
{
	//Para el control de basura
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game* Juego = new Game("Assets\\InitAplication.json");
	Juego->start();

	system("pause");


	return 0;
}

