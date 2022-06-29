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

/* Game Controller Functions */

void Game::Init(Resource* pointerResource_In, UtilityBelt* pointerUtils_In)
{
	pointerResource = pointerResource_In;
	pointerUtils = pointerUtils_In;
}
void Game::Update(RenderWindow& window, Event event, float elapsed)
{
	windowSize = { (float)window.getSize().x, (float)window.getSize().y };
	percentBounds = { (float)window.getSize().x / 100.f, (float)window.getSize().y / 100.f };
	for (Object* object : objects) object->Update(elapsed);
	//Obstacle_Generation();
}
std::vector<Drawable*> Game::Render()
{
	drawables.clear();													// Clear the drawable object list, so it can be rewritten with updated information
	for (Object* object : objects) object->RenderUpdate(drawables);		// Update the render information for each object (visibility, etc.)
	return drawables;
}
bool Game::isColliding(Physics* object1, Physics* object2)
{
	for (Physics* phy_object : collidables);
	//unfinished..
	return false;
}
void Game::Obstacle_Generation()
{
	for (int i = 0; i < obstacles.size(); i++)
	{
		if (obstacles[i].position.x < windowSize.x)
		{
			obstacles[i].Destroy(this);
			obstacles.erase(obstacles.begin() + i);
		}
	}
	if (obstacles.size() < Defaults::max_obstacleCount)
	{
		//obstacles.emplace_back(new Obstacle);
		obstacles.back().Init(this, pointerResource->texEnemy);
	}
}


// Game Object Functions //

void Object::Init(Game* pointerGame_In, Texture& tex)
{
	parentGamePointer = pointerGame_In;

	sprite.setTexture(tex);
	spriteRect = sprite.getTextureRect();
	parentGamePointer->objects.push_back(this);
}
void Object::Update(float elapsed)
{
	if (enabled) position = sprite.getPosition();
}
void Object::RenderUpdate(std::vector <sf::Drawable*>& drawables)
{
	if (visible) parentGamePointer->drawables.push_back(&this->sprite);
}
void Object::Destroy(Game* parentGamePointer)
{
	for (int i = 0; i < parentGamePointer->objects.size(); i++)
		if (parentGamePointer->objects[i] == this) 
			parentGamePointer->objects.erase(parentGamePointer->objects.begin() + i);
}

void Physics::Init(Game* pointerGame_In, Texture& tex)
{
	pointerGame_In->collidables.push_back(this);
}
void Physics::Destroy(Game* parentGamePointer)
{
	for (int i = 0; i < parentGamePointer->collidables.size(); i++)
		if (parentGamePointer->collidables[i] == this)
			parentGamePointer->collidables.erase(parentGamePointer->collidables.begin() + i);
}

void Controllable::Init(Game* pointerGame_In, Texture& tex)
{
	pointerGame_In->controllables.push_back(this);
}
void Controllable::Update(float elapsed)
{
	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down))
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			velocity.y -= Defaults::player_movementPower * pow(elapsed, 0.1f) / 2.f;
			std::cout << "[" << this << "]" << " Control Update: Up Arrow \n";
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			velocity.y += Defaults::player_movementPower * pow(elapsed, 0.1f) / 2.f;
			std::cout << "[" << this << "]" << " Control Update: Down Arrow \n";
		}
	}

	//velocity = Decay(velocity, 0.1f, 0.1f, elapsed);

	velocity.y += Defaults::gravityFactor * pow(elapsed, 0.1f) / 2.f;

	if (velocity.y < (Defaults::terminal_velocity * -1.f) && velocity.y < 0.f) velocity.y = (Defaults::terminal_velocity * -1.f);
	else if (velocity.y > Defaults::terminal_velocity && velocity.y > 0.f) velocity.y = Defaults::terminal_velocity;

	std::cout << "[" << this << "]" << " Velocity is (" << velocity.x << ", " << velocity.y << ").\n";
}
void Controllable::Destroy(Game* parentGamePointer)
{
	for (int i = 0; i < parentGamePointer->controllables.size(); i++)
		if (parentGamePointer->controllables[i] == this)
			parentGamePointer->controllables.erase(parentGamePointer->controllables.begin() + i);
}

void Static_Environment::Init(Game* pointerGame_In, Texture& tex)
{
	Object::Init(pointerGame_In, tex);

	std::cout << "[" << this << "]" << " Static Environment instance created\n";
}
void Static_Environment::Destroy(Game* parentGamePointer)
{
	Object::Destroy(parentGamePointer);
}

void Dyn_Environment::Init(Game* pointerGame_In, Texture& tex)
{
	Object::Init(pointerGame_In, tex);
	Physics::Init(pointerGame_In, tex);
	std::cout << "[" << this << "]" << " Dynamic Environment instance created\n";
}
void Dyn_Environment::Destroy(Game* parentGamePointer)
{
	Object::Destroy(parentGamePointer);
	Physics::Destroy(parentGamePointer);
}

void Player::Init(Game* pointerGame_In, Texture& tex)
{
	Object::Init(pointerGame_In, tex);
	Physics::Init(pointerGame_In, tex);
	Controllable::Init(pointerGame_In, tex);

	sprite.setPosition(parentGamePointer->percentBounds.x * 50.f, parentGamePointer->percentBounds.y * 50.f);
	sprite.setScale({ 3, 3 });

	controllable_member = this;

	std::cout << "[" << this << "]" << " Player instance created. Position is (" << position.x << ", " << position.y << "). " 
		<< "Bounds are (" << bounds.width << ", " << bounds.height << ") at (" << bounds.left << ", " << bounds.top << ").\n";

}
void Player::Update(float elapsed)
{
	Object::Update(elapsed);

	Controllable::Update(elapsed);
	position += velocity * elapsed;
	if (position.y < (bounds.height * 0.1f))
	{
		position.y = bounds.height * 0.1f;
		velocity.y = 0.1f;
	}
	if (position.y > (parentGamePointer->windowSize.y - bounds.height * 1.1f))
	{
		position.y = parentGamePointer->windowSize.y - bounds.height * 1.1f;
		velocity.y = -50.f;
	}
	sprite.setPosition(position);
}
void Obstacle::Init(Game* pointerGame_In, Texture& tex)
{
	Object::Init(pointerGame_In, tex);
	Physics::Init(pointerGame_In, tex);

	sprite.setPosition(parentGamePointer->percentBounds.x * 50.f, parentGamePointer->percentBounds.y * 50.f);
	sprite.setScale({ 3, 3 });
}
void Obstacle::Update(float elapsed)
{
	Object::Update(elapsed);

}
void Obstacle::Destroy(Game* parentGamePointer)
{
	Object::Destroy(parentGamePointer);
	Physics::Destroy(parentGamePointer);
}