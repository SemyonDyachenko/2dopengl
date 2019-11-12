#include "Game.h"

#include "Graphics/Texture.h"


int main(void)
{
	Game game;
	game.init("From the Darkness of Night");

	game.update();
	game.render();

	
	return 0;
}
