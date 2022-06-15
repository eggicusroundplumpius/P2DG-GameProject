#include "UI.h"
#include "Game.h"

using namespace sf;
using namespace std;
using namespace Defaults;

void Init(Resource& resource, UtilityBelt& utils, Game& game, UI_Frame& ui);
void Update(RenderWindow& window, Game& game, UI_Frame& ui, Event& event, float elapsed);
void Render(RenderWindow& window, Game& game, UI_Frame& ui, float elapsed);

int main()
{
	RenderWindow window(windowResolution, windowName, windowMode);	// Main RenderWindow
	window.setFramerateLimit(fpsLimit);

	UtilityBelt utils;	// Root UtilityBelt Object
	Resource resource;	// Root Resource Object
	Game game;			// Root Game Object
	UI_Frame ui_frame;	// Root UI Object

	TextBox health_text;
	health_text.Init(ui_frame, Vector2f{ windowResolution.width / 10.f, windowResolution.height / 5.f});
	Button pause_button;
	pause_button.Init(ui_frame, Vector2f{ windowResolution.width / 10.f, windowResolution.height / 5.f });

	// Root initialisation
	Init(resource, utils, game, ui_frame);

	float elapsed;		// Time elapsed since last update
	Clock mainClock;	// Main program clock

	/* Main Loop */
	while (window.isOpen())
	{
		elapsed = mainClock.getElapsedTime().asSeconds();
		mainClock.restart();

		Event event;

		Update(window, game, ui_frame, event, elapsed);
		Render(window, game, ui_frame, elapsed);
	}

	return 0;
}

void Init(Resource& resource, UtilityBelt& utils, Game& game, UI_Frame& ui)
{
	//Load resources
	utils.Load(resource.loadFonts, resource.loadFontPaths);
	utils.Load(resource.loadTextures, resource.loadTexturePaths);
	
	//Initialise Major Parent Objects
	ui.Init(&resource, &game, &utils);

	game.Init(&resource);
}
void Update(RenderWindow& window, Game& game, UI_Frame& ui, Event& event, float elapsed)
{
	//If an event to close the window is triggered, close the window
	while (window.pollEvent(event)) if (event.type == Event::Closed) window.close();
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) window.close();
	
	//Update Major Parent Objects
	ui.Update(window, event);
	game.Update(window, event, elapsed);
}
void Render(RenderWindow& window, Game& game, UI_Frame& ui, float elapsed)
{
	//Run Render tasks for Major Parent Objects
	game.Render(window, elapsed);

	//Draw distilled drawables to window
	draw(ui.Render(), game.Drawables, window);
	window.display();
}