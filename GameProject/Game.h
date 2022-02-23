#pragma once

#include "Utils.h"

struct Resource
{
	//Texture Objects

	sf::Texture texBackground;
	sf::Texture texGround;
	sf::Texture texShip;
	sf::Texture texEnemy;
	sf::Texture iconBack;
	sf::Texture iconPause;
	sf::Texture iconMusic;
	sf::Texture iconMute;
	sf::Texture iconExit;

	//Font Objects

	FontType DSEG14Classic;
	FontType CondenBitmap;

	//Loading Paths

	const std::vector <sf::Texture*> loadTextures{ &texBackground, &texGround, &texShip, &texEnemy, 
													&iconBack, &iconPause, &iconMusic, &iconMute, &iconExit };
	const vector<string> loadTexturePaths =
	{
		"data/tex/backgound.png",
		"data/tex/ground.png",
		"data/tex/ship.png",
		"data/tex/enemy.png",
		"data/tex/icon/back.png",
		"data/tex/icon/pause.png",
		"data/tex/icon/music.png",
		"data/tex/icon/mute.png",
		"data/tex/icon/exit.png"
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
	void Init(Resource* resource);
	void Update(sf::RenderWindow& window, Event event, float elapsed);
	void Render(sf::RenderWindow& window, float elapsed);

	enum class Mode {menuRoot, menuOptions, menuAbout, gamePlay, gamePause}; //Current Display Mode
	enum class Type {Player, Enemy, Static_Environment, Dyn_Environment}; //Object Type

	Resource* pointerResource;
	Keyboard keyboard;

	/////////////////////////
	/// Basic Information
	/////////////////////////

	const float gameVersion = 0.1f;
	int score = 0;
	int lives = 3;
	Mode currentMode = Mode::menuRoot;
	Vector2f windowSize;

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

		Vector2f position;
		FloatRect bounds;

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
