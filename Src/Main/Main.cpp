#include "Game.h"
#include <Windows.h>

int main(int argc, char* argv[])
{

#if _DEBUG
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);

#else
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

#endif



	Game* Juego = new Game("InitAplication.json");
	Juego->start();
	Juego->run();
	delete Juego;
	return 0;
}