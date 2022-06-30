#pragma once
#include <assert.h>
#include <string>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits.h>

#include "Utils.h"

class Object;
class Physics;
class Controllable;
class Static_Environment;
class Dyn_Environment;
class Player;
class Obstacle;

// Game World Controller
class Game
{
	friend class Object;
	friend class Physics;
	friend class Controllable;
	friend class Static_Environment;
	friend class Dyn_Environment;
	friend class Player;
	friend class Obstacle;

public:
	// Initialises Game-world controller with a link to the resource object
	void Init(Resource* pointerResource_In, UtilityBelt* pointerUtils_In);
	// Called every game loop, updates the game world
	void Update(sf::RenderWindow& window, Event event, float elapsed);
	// Called every game loop, updates the render information for all game objects
	vector <sf::Drawable*> Render();
	// Checks if two physics-enabled game objects are colliding
	bool isColliding(Physics* object1, Physics* object2);
	// Simple lose trigger. Resets all the relevent things and restarts the game.
	void Lose();

	float score = 0.f;							// Player Score in current game
	gameMode currentMode = gameMode::gamePlay;	// Current & default screen mode

protected:
	std::vector <Obstacle*> obstacles;			// Vector of Obstacle instances for easy creation and destruction
	std::vector <Object*> objects;				// Vector of object pointers to keep track of all instances
	std::vector <Physics*> collidables;			// Vector of physics-enabled object pointers for determining collisions
	std::vector <Controllable*> controllables;	// Vector of controllable object pointers - items within will respond to controls
	std::vector <Drawable*> drawables;			// Vector of drawable pointers to pass into the draw function

	Vector2f windowSize;		// Size of window
	Vector2f percentBounds;		// Represents a single percent of the window's resolution

private:
	void obstacleGeneration();

	Resource* pointerResource;		// Pointer to root Resource object
	UtilityBelt* pointerUtils;		// Pointer to root Utility object

};


// Bases //

class Object	// Base class for all game objects
{
	friend class Game;
	friend class Controllable;
	friend class Physics;
public:
	virtual void Init(Game* parentGamePointer, Texture& tex);
	virtual void Update(float elapsed);
	void RenderUpdate(std::vector <sf::Drawable*>& drawables);
	virtual void Reset();
	virtual void Destroy(Game* parentGamePointer);

	sf::Sprite sprite;					// Sprite to hold main texture
	sf::Vector2f position;				// Position of game object last update
	sf::FloatRect bounds;				// Global bounds relative to world coordinates
	sf:: Vector2f velocity = { 0, 0 };	// Velocity value, to preserve momentum (used with the Decay function)
	int health = Defaults::health;		// Starting health value for any object

	bool visible = true;	// Control of whether or not this instance is added to the Drawables vector
	bool enabled = true;	// Control of move/update capabilities

protected:
	Game* parentGamePointer = nullptr;	//Pointer to parent game object
};
class Physics	// Base class for all physics-enabled game objects
{
	friend class Game;
	friend class Player;
	friend class Obstacle;
public:
	virtual void Init(Game* pointerGame_In, Texture& tex);
	virtual void Update(float elapsed);
	void Collide(Obstacle* origin);
	virtual void Destroy(Game* parentGamePointer);

	bool physicsEnabled = true;		// Control of whether this instance should trigger physics events
	bool gravityResponsive = true;	// Whether this object should respond to gravity
	sf::IntRect spriteRect;			// Bounds of the sprite (set in Physics::Init). Used for collisions.

protected:
	Physics* exchangedPointer = nullptr;	// When colliding with another object, this will store the pointer of the last object collided with.
	Object* derived = nullptr;				// Yes, this is a disgusting, lazy solution for giving base classes access. I'll fix it later.
};
class Controllable	// Base class for all game objects that can respond to controls
{
	friend class Game;
public:
	virtual void Init(Game* parentGamePointer, Texture& tex);
	virtual void Update(float elapsed);
	virtual void Destroy(Game* parentGamePointer);

protected:
	Object* derived = nullptr;	// Yes, this is a disgusting, lazy solution for giving base classes access. I'll fix it later.
};


// Specials //

class Player : public Object, Physics, Controllable
{
	friend class Object;
	friend class Physics;
public:
	virtual void Init(Game* pointerGame_In, Texture& tex);
	virtual void Update(float elapsed);
	virtual void Reset();

};
class Obstacle : public Object, public Physics
{
	friend class Physics;
public:
	virtual void Init(Game* pointerGame_In, Texture& tex);
	virtual void Update(float elapsed);
	virtual void Destroy(Game* parentGamePointer);
};


// Generics //

class Static_Environment : public Object			// This is used for things like backgrounds and other permenant objects.
{
public:
	virtual void Init(Game* parentGamePointer, Texture& tex);
	virtual void Destroy(Game* parentGamePointer);
};
class Dyn_Environment : public Object, Physics		// This is used for things like obstacles, where they might be deleted and recreated often.
{
public:
	virtual void Init(Game* parentGamePointer, Texture& tex);
	virtual void Destroy(Game* parentGamePointer);
};
