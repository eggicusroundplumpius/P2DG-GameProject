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

	void Game::Init(Resource* pointerResource_In)
	{
		pointerResource = pointerResource_In;
		background.Init(Type::Static_Environment, pointerResource->texBackground, this);

		ground.Init(Type::Dyn_Environment, pointerResource->texGround, this);
		ground.sprite.setPosition(percentBounds.x * 50.f, percentBounds.y * 90.f);

		player.Init(Type::Player, pointerResource->texShip, this);
	}
	void Game::Update(RenderWindow& window, Event event, float elapsed)
	{
		for (Object* object : Objects) object->Update(elapsed);
		percentBounds = { (float)window.getSize().x / 100.f, (float)window.getSize().y / 100.f };
	}
	void Game::Render(RenderWindow& window, float elapsed)
	{
		windowSize = { (float)window.getSize().x, (float)window.getSize().y };

		if (Defaults::physicsVisibleBoundaries) for (Object* object : Objects)
		{
			if (object->physicsEnabled)
			{
				bool found = false;
				object->physicsBounds.setRadius(object->collisionRadius);
				object->physicsBounds.setOrigin(object->collisionRadius, object->collisionRadius);
				object->physicsBounds.setOutlineColor(sf::Color::Blue);
				object->physicsBounds.setOutlineThickness(2.f);
				object->physicsBounds.setPosition(object->sprite.getPosition());
				for (Drawable* objectSelected : Drawables)
					if (&object->physicsBounds == objectSelected) found = true; 
				if (!found) Drawables.push_back(&object->physicsBounds);
			}
		}
	}
	void Game::PlayerUpdate(Vector2f const& windowSize, float elapsed)
	{
		player.position = player.sprite.getPosition();
		player.bounds = player.sprite.getGlobalBounds();

		static Vector2f thrust{ 0,0 };

		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down))
		{
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				thrust.y = -Defaults::playerSpeed;
				std::cout << "up arrow\n";
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				std::cout << "down arrow\n";
				thrust.y = Defaults::playerSpeed;
			}
		}

		player.position += thrust * elapsed;
		thrust = Decay(thrust, 0.1f, 0.02f, elapsed);

		if (player.position.y < (player.bounds.height * 0.1f))
			player.position.y = player.bounds.height * 0.1f;
		if (player.position.y > (windowSize.y - player.bounds.height * 1.1f))
			player.position.y = windowSize.y - player.bounds.height * 1.1f;

		player.sprite.setPosition(player.position);
	}
	void Game::changeMode(Game::Mode mode)
	{
		switch (mode)
		{
		case (Game::Mode::menuRoot):
			player.physicsEnabled = false;
			player.visible = false;
			player.enabled = false;

			for (Game::Object* object : Objects)
			{
				if (object->type == Game::Type::Dyn_Environment)
				{
					object->physicsEnabled = false;
					object->visible = false;
					object->enabled = false;
				}
				if (object->type == Game::Type::Enemy)
				{
					object->physicsEnabled = false;
					object->visible = false;
					object->enabled = false;
				}
				if (object->type == Game::Type::Static_Environment)
				{
					object->physicsEnabled = false;
					object->visible = true;
					object->enabled = true;
				}
			}
			break;
		case (Game::Mode::gamePlay):
			player.physicsEnabled = true;
			player.visible = true;
			player.enabled = true;

			for (Game::Object* object : Objects)
			{
				if (object->type == Game::Type::Dyn_Environment)
				{
					object->physicsEnabled = true;
					object->visible = true;
					object->enabled = true;
				}
				if (object->type == Game::Type::Enemy)
				{
					object->physicsEnabled = true;
					object->visible = true;
					object->enabled = true;
				}
				if (object->type == Game::Type::Static_Environment)
				{
					object->physicsEnabled = false;
					object->visible = true;
					object->enabled = true;
				}
			}
			break;
		}
	}

/* Game Object Functions */

	void Game::Object::Init(Game::Type type_In, sf::Texture& tex, Game* pointerGame_In)
	{
		pointerGame = pointerGame_In;
		type = type_In;

		sprite.setTexture(tex);
		switch (type) {
		case (Type::Player):
			physicsEnabled = false;
			visible = false;
			enabled = false;

			sprite.setPosition(pointerGame->percentBounds.x * 5.f, pointerGame->percentBounds.y * 50.f);
			std::cout << "Player instance created\n";
			break;

		case (Type::Enemy):
			physicsEnabled = false;
			visible = false;
			enabled = false;

			std::cout << "Enemy instance created\n";
			break;

		case (Type::Static_Environment):
			physicsEnabled = false;
			visible = true;
			enabled = true;

			std::cout << "Static Environment instance created\n";
			break;

		case (Type::Dyn_Environment):
			physicsEnabled = false;
			visible = false;
			enabled = false;

			std::cout << "Dynamic Environment instance created\n";
			break;

		};
		spriteRect = sprite.getTextureRect();
		if (visible) pointerGame->Drawables.push_back(&this->sprite);
		pointerGame->Objects.push_back(this);
	}
	void Game::Object::Update(float elapsed)
	{
		if (visible)
		{
			bool notFound = true;
			for (Drawable* object : pointerGame->Drawables)
			{
				if (object == &this->sprite) {
					notFound = false; break; }
			}
			if (notFound) pointerGame->Drawables.push_back(&this->sprite);
		}
		else
			for (unsigned i = 0; i < pointerGame->Drawables.size(); i++)
				if (pointerGame->Drawables[i] == &this->sprite) pointerGame->Drawables.erase(pointerGame->Drawables.begin() + i);

		if (enabled)
		{
			position = sprite.getPosition();
			if (type == Game::Type::Player) pointerGame->PlayerUpdate(pointerGame->windowSize, elapsed);
		}
	}
	bool Game::Object::IsColliding()
	{
		if (!physicsEnabled) return false;
		else
		{
			for (Object* object : pointerGame->Objects)
				if (distanceCheck(this->position, object->position, collisionRadius))
				{
					std::cout << "Colliding...\n";
					return true;
				};
			return false;
		}
	}
	void Game::Object::Destroy()
	{
		enabled = false;
		visible = false;
		delete this;
	}