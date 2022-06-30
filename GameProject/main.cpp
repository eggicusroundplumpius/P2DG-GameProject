#include "UI.h"
#include "Game.h"

using namespace sf;
using namespace std;
using namespace Defaults;

void Render(RenderWindow& window, Game& game, UI_Frame& ui, float elapsed);

int main()
{
	RenderWindow window(windowResolution, windowName, windowMode);	// Main RenderWindow
	window.setFramerateLimit(fpsLimit);

	UtilityBelt utils;	// Root UtilityBelt Object
	Resource resource;	// Root Resource Object
	Game game;			// Root Game Object
	UI_Frame ui_frame;	// Root UI Object

	// Load Resources (textures, fonts, etc.)
	utils.Load(resource.loadFonts, resource.loadFontPaths);
	utils.Load(resource.loadTextures, resource.loadTexturePaths);

	// Initialise core components
	ui_frame.Init(&resource, &game, &utils);
	game.Init(&resource, &utils);

	TextBox score_text;
	score_text.Init(ui_frame, Vector2f{ windowResolution.width / 10.f, 
										windowResolution.height / 5.f});
	score_text.setPosition(Vector2f{ windowResolution.width - (windowResolution.width / 10.f),
									windowResolution.height - (windowResolution.height / 20.f) });

	Static_Environment background;
	background.Init(&game, resource.texBackground);

	Player player1;
	player1.Init(&game, resource.texPlayer);

	float elapsed;		// Time elapsed since last update
	Clock mainClock;	// Main program clock

	/* Main Loop */
	while (window.isOpen())
	{
		elapsed = mainClock.getElapsedTime().asSeconds();
		game.score += elapsed;
		mainClock.restart();

		Event event;
		while (window.pollEvent(event)) if (event.type == Event::Closed) window.close();
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) window.close();

		ui_frame.Update(window, event);
		game.Update(window, event, elapsed);

		score_text.text.setString("Time: " + to_string(floor(game.score * 100.f) / 100.f));
		Render(window, game, ui_frame, elapsed);
	}

	return 0;
}
void Render(RenderWindow& window, Game& game, UI_Frame& ui, float elapsed)
{
	draw(ui.Render(), game.Render(), window);
	window.display();
}