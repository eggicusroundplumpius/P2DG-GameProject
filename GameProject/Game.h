#pragma once

#include "Utils.h"

namespace Defaults
{
	const sf::VideoMode windowResolution = { 1280, 720 };
	const std::string windowName = "Game Project";
	const unsigned fontSize = 50u;
}

struct Resource
{
	//Texture Objects

	sf::Texture texBackground;
	sf::Texture texGround;
	sf::Texture texShip;
	sf::Texture texEnemy;

	//Font Objects

	FontType DSEG14Classic;
	FontType CondenBitmap;

	//Loading Paths

	const std::vector <sf::Texture*> loadTextures{ &texBackground, &texGround, &texShip, &texEnemy };
	const vector<string> loadTexturePaths =
	{
		"data/tex/backgound.png",
		"data/tex/ground.png"
		"data/tex/ship.png",
		"data/tex/enemy.png"
	};
	const std::vector <FontType*> loadFonts{ &DSEG14Classic, &CondenBitmap };
	const vector<vector<string>> loadFontPaths = {
		{ //DSEG14 Classic
			"data/fonts/DSEG14Classic-Regular.ttf",
			"data/fonts/DSEG14Classic-Italic.ttf",
			"data/fonts/DSEG14Classic-Bold.ttf",
			"data/fonts/DSEG14Classic-BoldItalic.ttf",
			"data/fonts/DSEG14Classic-Light.ttf",
			"data/fonts/DSEG14Classic-LightItalic.ttf"
		},
		{ //CondenBitmap
			"data/fonts/CondenBitmap.otf",
			"",
			"",
			"",
			"",
			""
		}
	};
};

struct Game
{
	void Init(Resource &resource);
	void Update(sf::RenderWindow& window, float elapsed);
	void Render(sf::RenderWindow& window, float elapsed);

	enum class Mode {menuRoot, menuOptions, menuAbout, gamePlay, gamePause}; //Current Display Mode
	enum class Type {Player, Enemy, Static_Environment, Dyn_Environment}; //Object Type

	/////////////////////////
	/// Basic Information
	/////////////////////////

	const float gameVersion = 0.1f;
	int score = 0;
	int lives = 3;
	Mode currentMode = Mode::menuRoot;

	std::vector <Drawable*> Drawables; // Vector of objects to pass into the draw function

	///////////////////////
	/// Object Template
	///////////////////////
	struct Object
	{
		sf::Sprite sprite;		//Sprite Object
		sf::IntRect spriteRect; //Sprite Object bounds, as set by bounds of texture rectangle

		Game *pGame = nullptr;	//Pointer to game

		/// Default Settings ///
							 ///
		bool physicsEnabled; /// Does this object interact with other objects physically?
		bool visible;		 /// Is this object being drawn (passed to the Render function)?
		bool enabled;		 /// Should this object move/update?

		void Init(Game::Type type, sf::Texture& tex, Game* pGameIn);
		void Update();
		bool IsColliding();
		void Destroy();
	};
	
	/////////////////////////////
	/// Object Initialisation ///
	/////////////////////////////

	std::vector <Object*> Physics;

	Object background;
	Object ground;
	Object player;

};
