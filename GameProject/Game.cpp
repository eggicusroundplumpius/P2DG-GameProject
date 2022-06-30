
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
	for (Object* object : objects)
	{
		object->Update(elapsed);
		if (object->health <= 0)
		{
			Lose();
			break;
		}
	}
	obstacleGeneration();
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
void Game::obstacleGeneration()
{
	for (int i = 0; i < (int)obstacles.size(); i++)
	{
		if (obstacles[i]->position.x < 0.f)
		{
			obstacles[i]->Destroy(this);
			delete obstacles[i];
			obstacles.erase(obstacles.begin() + i);
		}
		if (i == obstacles.size()) break;
	}
	if (obstacles.size() < Defaults::max_obstacleCount)
	{
		obstacles.push_back(new Obstacle);
		obstacles[obstacles.size()-1]->Init(this, pointerResource->texEnemy);
	}
}
void Game::Lose()
{
	for (Object* object : objects) object->Reset();
	score = 0.f;
	for (int i = (int)obstacles.size() - 1; i >= 0; i--)
	{
		obstacles[i]->Destroy(this);
		delete obstacles[i];
		obstacles.erase(obstacles.begin() + i);
		//if (i == obstacles.size()) break;
	}
	std::cout << "[" << this << "]" << " You Lose! \n";
}


// Game Object Functions //

void Object::Init(Game* pointerGame_In, Texture& tex)
{
	parentGamePointer = pointerGame_In;

	sprite.setTexture(tex);
	//spriteRect = sprite.getTextureRect();
	parentGamePointer->objects.push_back(this);
}
void Object::Update(float elapsed)
{
	if (enabled) position = sprite.getPosition();

	if (velocity.y < (Defaults::terminal_velocity * -1.f) && velocity.y < 0.f) velocity.y = (Defaults::terminal_velocity * -1.f);
	else if (velocity.y > Defaults::terminal_velocity && velocity.y > 0.f) velocity.y = Defaults::terminal_velocity;
}
void Object::RenderUpdate(std::vector <sf::Drawable*>& drawables)
{
	if (visible) parentGamePointer->drawables.push_back(&this->sprite);
}
void Object::Reset()
{
	health = Defaults::health;
}
void Object::Destroy(Game* parentGamePointer)
{
	for (int i = 0; i < (int)parentGamePointer->objects.size(); i++)
		if (parentGamePointer->objects[i] == this) 
			parentGamePointer->objects.erase(parentGamePointer->objects.begin() + i);
}

void Physics::Init(Game* pointerGame_In, Texture& tex)
{
	pointerGame_In->collidables.push_back(this);
	spriteRect = derived->sprite.getTextureRect();
	spriteRect.left = (int)derived->position.x;
	spriteRect.top = (int)derived->position.y;
}
void Physics::Update(float elapsed)
{
	spriteRect.left = (int)derived->position.x;
	spriteRect.top = (int)derived->position.y;

	sf::Vector2f& velocity = derived->velocity;
	if (gravityResponsive) velocity.y += Defaults::gravityFactor * pow(elapsed, 0.01f) / 2.f;

	/*for (Physics* peer_collidable : derived->parentGamePointer->collidables)
	{
		if (peer_collidable != this)
		{
			for (Obstacle* obstacle : derived->parentGamePointer->obstacles)
			{
				if (obstacle != peer_collidable->derived)
				{
					if (spriteRect.intersects(peer_collidable->spriteRect)) peer_collidable->Collide(this);
				}
			}
		}
	}*/
}
void Physics::Collide(Obstacle* origin)
{
	origin->derived->health -= 1;
	derived->health -= 1;
	std::cout << "[" << this << "]" << " Collision between '" << this << "' and '" << origin << "'.\n";
}
void Physics::Destroy(Game* parentGamePointer)
{
	for (int i = 0; i < (int)parentGamePointer->collidables.size(); i++)
		if (parentGamePointer->collidables[i] == this)
			parentGamePointer->collidables.erase(parentGamePointer->collidables.begin() + i);
}

void Controllable::Init(Game* pointerGame_In, Texture& tex)
{
	pointerGame_In->controllables.push_back(this);
}
void Controllable::Update(float elapsed)
{
	sf::Vector2f& velocity = derived->velocity;

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

	//std::cout << "[" << this << "]" << " Velocity is (" << velocity.x << ", " << velocity.y << ").\n";
}
void Controllable::Destroy(Game* parentGamePointer)
{
	for (int i = 0; i < (int)parentGamePointer->controllables.size(); i++)
		if (parentGamePointer->controllables[i] == this)
			parentGamePointer->controllables.erase(parentGamePointer->controllables.begin() + i);
}

void Static_Environment::Init(Game* pointerGame_In, Texture& tex)
{
	Object::Init(pointerGame_In, tex);
	sprite.setScale({ 3,3 });

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
	Controllable::derived = this;
	Physics::derived = this;

	sprite.setPosition(pointerGame_In->percentBounds.x * 5.f, pointerGame_In->percentBounds.y * 50.f);
	sprite.setScale({ 3, 3 });

	Object::Init(pointerGame_In, tex);
	Physics::Init(pointerGame_In, tex);
	Controllable::Init(pointerGame_In, tex);

	std::cout << "[" << this << "]" << " Player instance created. Position is (" << position.x << ", " << position.y << "). " 
		<< "Bounds are (" << bounds.width << ", " << bounds.height << ") at (" << bounds.left << ", " << bounds.top << ").\n";

}
void Player::Update(float elapsed)
{
	Object::Update(elapsed);
	Physics::Update(elapsed);
	Controllable::Update(elapsed);

	//velocity = Decay(velocity, 0.1f, 0.1f, elapsed);
	for (Obstacle* obstacle : parentGamePointer->obstacles)
	{
		if (spriteRect.intersects(obstacle->spriteRect)) Collide(obstacle);
	}

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
void Player::Reset()
{
	Object::Reset();
	sprite.setPosition(parentGamePointer->percentBounds.x * 5.f, parentGamePointer->percentBounds.y * 50.f);
	velocity = { 0.f, 0.f };
	std::cout << "[" << this << "]" << " Player Reset.\n";
}
void Obstacle::Init(Game* pointerGame_In, Texture& tex)
{
	Physics::derived = this;

	int randPosition = rand() % (int)pointerGame_In->windowSize.y;
	sprite.setPosition(pointerGame_In->windowSize.x, (float)randPosition);
	position = { pointerGame_In->windowSize.x, (float)randPosition };
	sprite.setScale({ 0.1f, 0.1f });

	Object::Init(pointerGame_In, tex);
	Physics::Init(pointerGame_In, tex);

	gravityResponsive = false;
	health = 1;

	velocity.x = (rand() & (int)Defaults::terminal_velocity) * -1.f;

	std::cout << "[" << this << "]" << " Obstacle instance created. Position is (" << position.x << ", " << position.y << "). "
		<< "Bounds are (" << bounds.width << ", " << bounds.height << ") at (" << bounds.left << ", " << bounds.top << ").\n";
}
void Obstacle::Update(float elapsed)
{
	Object::Update(elapsed);
	Physics::Update(elapsed);

	position += velocity * elapsed;
	sprite.setPosition(position);
}
void Obstacle::Destroy(Game* parentGamePointer)
{
	Object::Destroy(parentGamePointer);
	Physics::Destroy(parentGamePointer);
	std::cout << "[" << this << "]" << " Obstacle Destruction.\n";
}