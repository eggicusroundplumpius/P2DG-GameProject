#include "Game.h"

using namespace sf;
using namespace std;

void Init(Resource &resource);
void Update(RenderWindow& window, float elapsed);
void Render(RenderWindow& window, float elapsed);

Game game;
Resource resource;
UtilityBelt Utils;
UI ui;

int main()
{
	RenderWindow window(Defaults::windowResolution, Defaults::windowName);
	Init(resource);
	
	Clock mainClock;
	float elapsed;

	while (window.isOpen())
	{
		elapsed = mainClock.getElapsedTime().asSeconds();
		Update(window, elapsed);
		Render(window, elapsed);
	}

	return 0;
}

void Init(Resource &resource)
{
	Utils.Load(resource.loadFonts, resource.loadFontPaths);
	Utils.Load(resource.loadTextures, resource.loadTexturePaths);
	
	ui.Init();
	game.Init(resource);
}
void Update(RenderWindow& window, float elapsed)
{
	game.Update(window, elapsed);
}
void Render(RenderWindow& window, float elapsed)
{
	game.Render(window, elapsed);
	ui.Render();
	window.display();
}