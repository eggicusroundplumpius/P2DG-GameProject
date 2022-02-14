
#include "Game.h"

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window;
	Game game;
	game.Init();

	Clock mainClock;
	float elapsed;

	while (window.isOpen()) 
	{
		elapsed = mainClock.getElapsedTime().asSeconds();
		game.Update(window, elapsed);
		game.Render(window, elapsed);
	}

	return 0;
}