#include "Game.h"
#include <Windows.h>

//Versión para Debug (con consola)
int main(int argc, char* argv[])
{
	Game* Juego = new Game("InitAplication.json");
	Juego->start();
	Juego->run();
	delete Juego;
	return 0;
}

//Versión para Release (solo ventana)
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{
	Game* Juego = new Game("InitAplication.json");
	Juego->start();
	Juego->run();
	delete Juego;
	return 0;
}

