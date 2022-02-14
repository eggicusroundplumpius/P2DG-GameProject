#include "Utils.h"
#include "Game.h"

using namespace sf;
using namespace std;

void Init();
void Update();
void Render();

int main()
{
	RenderWindow window(Defaults::windowResolution, Defaults::windowName);
	Init();
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

void Init()
{
	UtilityBelt Utils;
	Utils.Load();
}