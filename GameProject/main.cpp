#include "UI.h"

using namespace sf;
using namespace std;

void Init();
void Update(RenderWindow& window, Event& event, float elapsed);
void Render(RenderWindow& window, float elapsed);

UI ui;
Game game;
Resource resource;
UtilityBelt Utils;

int main()
{
	RenderWindow window(Defaults::windowResolution, Defaults::windowName);
	Init();

	float elapsed;
	Clock mainClock;

	while (window.isOpen())
	{
		elapsed = mainClock.getElapsedTime().asSeconds();
		mainClock.restart();

		Event event;
		Update(window, event, elapsed);
		Render(window, elapsed);
	}

	return 0;
}

void Init()
{
	Utils.Load(resource.loadFonts, resource.loadFontPaths);
	Utils.Load(resource.loadTextures, resource.loadTexturePaths);
	
	ui.Init();
	game.Init(resource);
}
void Update(RenderWindow& window, Event& event, float elapsed)
{
	while (window.pollEvent(event)) if (event.type == Event::Closed) window.close();
	
	ui.Update(window, game.currentMode);
	game.Update(window, elapsed);
}
void Render(RenderWindow& window, float elapsed)
{
	ui.Render(window);
	game.Render(window, elapsed);

	draw(ui.Drawables, game.Drawables, window);
	window.display();
}