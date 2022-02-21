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
	struct Information
	{
		const float gameVersion = 0.1;
		int score = 0;
		int lives = 3;
	};

	std::vector <Drawable*> Drawables; // Vector of objects to pass into the draw function

	///////////////////////
	/// Object Template
	///////////////////////
	struct Object
	{
		sf::Sprite sprite;		//Sprite Object
		sf::IntRect spriteRect; //Sprite Object bounds, as set by bounds of texture rectangle

		/// Default Settings ///
							 ///
		bool physicsEnabled; /// Does this object interact with other objects physically?
		bool visible;		 /// Is this object being drawn (passed to the Render function)?
		bool enabled;		 /// Should this object move/update?

		void Init(Type type, sf::Texture &tex)
		{
			sprite.setTexture(tex);
			switch (type) {
			case (Type::Player):
				physicsEnabled = true;
				visible = true;
				enabled = false;

			case (Type::Enemy):
				physicsEnabled = true;
				visible = true;
				enabled = false;

			case (Type::Static_Environment):
				physicsEnabled = false;
				visible = true;
				enabled = true;

			case (Type::Dyn_Environment):
				physicsEnabled = true;
				visible = true;
				enabled = true;

			};
			spriteRect = sprite.getTextureRect();
			if (visible) game.Drawables.push_back(&this->sprite);
		}
		void Update()
		{
			if (!visible) 
				for (unsigned i = 0; i < game.Drawables.size(); i++)
					if (game.Drawables[i] == &this->sprite) game.Drawables.erase(game.Drawables.begin()+i);
		}

		bool IsColliding() //Checks for collisions against any object in the world
		{
			if (!physicsEnabled) return false;
			else
			{
				return true;
			}
		}
		void Destroy() //Destroys the current instance
		{
			enabled = false;
			visible = false;
			this->Update();
			delete this;
		}
	};
	
	/////////////////////////////
	/// Object Initialisation ///
	/////////////////////////////

	std::vector <Object*> Physics;

	Object background;
	Object ground;
	Object player;

};
struct UI
{
	void Init();
	void Update();
	void Render();

	Mouse mouse;
	Keyboard keyboard;

	std::vector <vector<Drawable*>> elements;

	struct Button
	{
		sf::RectangleShape Frame;
		sf::Sprite customFrame;
		sf::Text text;
		Dim2D::integer dimensions;

		void *pFunction;
		
		bool visible, enabled, selected;

		void Hover();
		void Click(sf::Mouse::Button const mouseButton);
		void Hold(sf::Mouse::Button const mouseButton);
		void Drag(sf::Mouse::Button const mouseButton);
		


		void Click(sf::Mouse::Button const mouseButton)
		{
			//pFunction->();
		}
	};

	void Init()
	{

	}
	void Update()
	{
		if (mouse.Right) for (std::vector <Drawable*> element : elements)
		{
			//if (mouse)
		}
		else if (mouse.Left); //Click(mouse.Left);
	}
	void Render()
	{

	}

	
};