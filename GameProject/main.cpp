#include "UI.h"

using namespace sf;
using namespace std;

void Init(Resource* resource, UtilityBelt& utils, Game& game, UI& ui);
void Update(RenderWindow& window, Game& game, UI& ui, Event& event, float elapsed);
void Render(RenderWindow& window, Game& game, UI& ui, float elapsed);

int main()
{
	UI ui;
	Game game;
	Resource resource;
	UtilityBelt utils;
	RenderWindow window(Defaults::windowResolution, Defaults::windowName, Defaults::windowMode);

	Init(&resource, utils, game, ui);

	float elapsed;
	Clock mainClock;

	while (window.isOpen())
	{
		elapsed = mainClock.getElapsedTime().asSeconds();
		mainClock.restart();

		Event event;
		Update(window, game, ui, event, elapsed);
		Render(window, game, ui, elapsed);
	}

	return 0;
}

void Init(Resource* resource, UtilityBelt& utils, Game& game, UI& ui)
{
	utils.Load(resource->loadFonts, resource->loadFontPaths);
	utils.Load(resource->loadTextures, resource->loadTexturePaths);
	
	ui.Init(resource);
	game.Init(resource);
}
void Update(RenderWindow& window, Game& game, UI& ui, Event& event, float elapsed)
{
	while (window.pollEvent(event)) if (event.type == Event::Closed) window.close();
	
	ui.Update(window, event, game.currentMode);
	game.Update(window, event, elapsed);
}
void Render(RenderWindow& window, Game& game, UI& ui, float elapsed)
{
	ui.Render(window);
	game.Render(window, elapsed);

	draw(ui.Drawables, game.Drawables, window);
	window.display();
}