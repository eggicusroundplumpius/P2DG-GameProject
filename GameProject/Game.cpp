#include <assert.h>
#include <string>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits.h>

#include "Game.h"

using namespace sf;
using namespace std;

/* Core Game Functions */

	/// ///////////////////////////////////////////////////////////
	///
	/// Initialisation function - performs many one-time only
	/// actions, intended to prepare the game to run.
	/// 
	/// ///////////////////////////////////////////////////////////
	void Game::Init(Resource &resource)
	{
		background.Init(Type::Static_Environment, resource.texBackground, this);
		ground.Init(Type::Static_Environment, resource.texGround, this);
		player.Init(Type::Player, resource.texShip, this);
	
	}

	/// ///////////////////////////////////////////////////////////
	///
	/// Primary render function: contains cases for main screens 
	/// available, handles drawing-related functions.
	/// 
	/// \param window - Main window object to draw to.
	/// \param elapsed - elapsed time in seconds since last update.
	/// 
	/// ///////////////////////////////////////////////////////////
	void Game::Update(RenderWindow& window, float elapsed)
	{

	}

	/// ///////////////////////////////////////////////////////////
	///
	/// Primary render function: contains cases for main screens 
	/// available, handles drawing-related functions.
	/// 
	/// \param window - Main window object to draw to.
	/// \param elapsed - elapsed time in seconds since last update.
	/// 
	/// ///////////////////////////////////////////////////////////
	void Game::Render(RenderWindow& window, float elapsed)
	{

	}

/* Game Object Functions */

	/// ///////////////////////////////////////////////////////////
	///
	/// Initialisation Function - Initialises the current instance,
	/// taking object type to set defaults.
	/// 
	/// \param type - Object type from enum
	/// \param tex - texture object sprite should have
	/// \param pGameIn - pointer to game object
	/// 
	/// ///////////////////////////////////////////////////////////
	void Game::Object::Init(Game::Type type, sf::Texture& tex, Game* pGameIn)
	{
		pGame = pGameIn;

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
		if (visible) pGame->Drawables.push_back(&this->sprite);
	}

	/// ///////////////////////////////////////////////////////////
	///
	/// Update function - updates the current instance.
	/// 
	/// ///////////////////////////////////////////////////////////
	void Game::Object::Update()
	{
		if (!visible)
			for (unsigned i = 0; i < pGame->Drawables.size(); i++)
				if (pGame->Drawables[i] == &this->sprite) pGame->Drawables.erase(pGame->Drawables.begin() + i);
	}

	/// ///////////////////////////////////////////////////////////
	///
	/// Collision detection function - detects if the current 
	/// instance is colliding with another physics-registered
	/// instance.
	/// 
	/// ///////////////////////////////////////////////////////////
	bool Game::Object::IsColliding()
	{
		if (!physicsEnabled) return false;
		else
		{
			return true;
		}
	}

	/// ///////////////////////////////////////////////////////////
	///
	/// Destroy function - destroys the current instance from
	/// within.
	/// 
	/// ///////////////////////////////////////////////////////////
	void Game::Object::Destroy()
	{
		enabled = false;
		visible = false;
		this->Update();
		delete this;
	}