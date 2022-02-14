#pragma once

#include "SFML/Graphics.hpp"
#include "Utils.h"

namespace Resource
{
	//Textures

	sf::Texture texBackground;
	sf::Texture texShip;
	sf::Texture texEnemy;
	

	//Fonts

	FontType DSEG14Classic;
	FontType CondenBitmap;

}

namespace Defaults
{
	//const Dim2D::integer Resolution = { 1280, 720 };
	const VideoMode windowResolution = { 1280, 720 };
	const string windowName = "Game";
	const unsigned fontSize = 50u;
}

struct Game
{
	void Init();
	void Update(sf::RenderWindow& window, float elapsed);
	void Render(sf::RenderWindow& window, float elapsed);

	enum class Mode {menuRoot, menuOptions, menuAbout, gamePlay, gamePause};

	struct Information	//Contains information regarding the current game - it holds no functions.
	{
		const float gameVersion = 0.1;
		int score = 0;
		int lives = 3;
	};
	struct Object
	{
		Sprite sprite;		//Sprite Object
		IntRect spriteRect; //Sprite Object bounds, as set by bounds of texture rectangle
		enum class Type {Player, Enemy, Environment};


		void Init(Type type)
		{
			switch (type) {
			case (Type::Player):
				sprite.setTexture(Resource::texShip);
			case (Type::Enemy):
				sprite.setTexture(Resource::texEnemy);
			case (Type::Environment):
				sprite.setTexture(Resource::texBackground);
			}
			
			spriteRect = sprite.getTextureRect();

		}
	};
};