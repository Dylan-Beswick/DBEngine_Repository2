#include "DBEngine/Game.h"

int main(int argc, char** argv) {

	Game::GetGameInstance().Start("DBEngine | An OpenGL Engine", false, 1280, 720);

	Game::DestroyGameInstance();

	return 0;
}