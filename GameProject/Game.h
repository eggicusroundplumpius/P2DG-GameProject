#pragma once

#include "Utils.h"

struct Resource
{
	//Textures

	sf::Texture texBackground;
	sf::Texture texShip;
	sf::Texture texEnemy;

	//Fonts

	FontType DSEG14Classic;
	FontType CondenBitmap;

	//Objects to Load

	const std::vector <sf::Texture*> loadTextures{ &texBackground, &texShip, &texEnemy };
	const vector<string> loadTexturePaths =
	{
		"/bin/data/tex/backgound.png",
		"/bin/data/tex/ship.png",
		"/bin/data/tex/enemy.png"
	};
	const std::vector <FontType*> loadFonts{ &DSEG14Classic, &CondenBitmap };
	const vector<vector<string>> loadFontPaths = {
		{
			"/bin/data/fonts/DSEG14Classic-Regular.ttf",
			"/bin/data/fonts/DSEG14Classic-Italic.ttf",
			"/bin/data/fonts/DSEG14Classic-Bold.ttf",
			"/bin/data/fonts/DSEG14Classic-BoldItalic.ttf",
			"/bin/data/fonts/DSEG14Classic-Light.ttf",
			"/bin/data/fonts/DSEG14Classic-LightItalic.ttf"
		},
		{
			"/bin/data/fonts/CondenBitmap.otf",
			"",
			"",
			"",
			"",
			""
		}
	};
};

namespace Defaults
{
	const sf::VideoMode windowResolution = { 1280, 720 };
	const std::string windowName = "Game";
	const unsigned fontSize = 50u;
}

struct Game
{
	void Init(Resource &resource);
	void Update(sf::RenderWindow& window, float elapsed);
	void Render(sf::RenderWindow& window, float elapsed);

	enum class Mode {menuRoot, menuOptions, menuAbout, gamePlay, gamePause};

	struct Information	//Contains information regarding the current game - it holds no functions.
	{
		const float gameVersion = 0.1;
		int score = 0;
		int lives = 3;
	};
	struct Object //Contains a template for every object within the world
	{
		sf::Sprite sprite;		//Sprite Object
		sf::IntRect spriteRect; //Sprite Object bounds, as set by bounds of texture rectangle
		enum class Type {Player, Enemy, Environment};

		void Init(Type type, Resource &resource)
		{
			switch (type) {
			case (Type::Player):
				sprite.setTexture(resource.texShip);
			case (Type::Enemy):
				sprite.setTexture(resource.texEnemy);
			case (Type::Environment):
				sprite.setTexture(resource.texBackground);
			}
			
			spriteRect = sprite.getTextureRect();
		}
		void Update()
		{

		}

		bool IsColliding() //Checks for collisions against any object in the world
		{
			return false;
		}
		void Destroy() //Destroys the current instance
		{

		}
	};
};