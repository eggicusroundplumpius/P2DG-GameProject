#pragma once
#include "Utils.h"

class Object;
class Physics;
class Controllable;
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

	int score = 0;								// Player Score in current game
	int lives = 3;								// Player Lives in current game
	gameMode currentMode = gameMode::gamePlay;	// Current & default screen mode

protected:
	std::vector <Obstacle> obstacles;			// Vector of Obstacle instances for easy creation and destruction
	std::vector <Object*> objects;				// Vector of object pointers to keep track of all instances
	std::vector <Physics*> collidables;			// Vector of physics-enabled object pointers for determining collisions
	std::vector <Controllable*> controllables;	// Vector of controllable object pointers - items within will respond to controls
	std::vector <Drawable*> drawables;			// Vector of drawable pointers to pass into the draw function

	Vector2f windowSize;		// Size of window
	Vector2f percentBounds;		// Represents a single percent of the window's resolution

private:
	void Obstacle_Generation();

	Resource* pointerResource;		// Pointer to root Resource object
	UtilityBelt* pointerUtils;		// Pointer to root Utility object

};


// Bases //

class Object	// Base class for all game objects
{
	friend class Game;
	friend class Controllable;
public:
	virtual void Init(Game* parentGamePointer, Texture& tex);
	virtual void Update(float elapsed);
	void RenderUpdate(std::vector <sf::Drawable*>& drawables);
	virtual void Destroy(Game* parentGamePointer);

	sf::Sprite sprite;			// Sprite to hold main texture
	sf::IntRect spriteRect;		// Bounds of the sprite (set in Object::Init). Used for collisions.
	sf::Vector2f position;		// Position of game object last update
	sf::FloatRect bounds;		// Global bounds relative to world coordinates

	bool visible = true;	// Control of whether or not this instance is added to the Drawables vector
	bool enabled = true;	// Control of move/update capabilities

protected:
	Game* parentGamePointer = nullptr;	//Pointer to parent game object

};
class Physics	// Base class for all physics-enabled game objects
{
public:
	virtual void Init(Game* pointerGame_In, Texture& tex);
	virtual void Destroy(Game* parentGamePointer);

	bool physicsEnabled;			// Control of whether this instance should trigger physics events
	float collisionRadius;			// Collision radius
	sf::CircleShape physicsBounds;	// Circle Indicating Collision

protected:
	Physics* exchangedPointer = nullptr;	// When colliding with another object, this will store the pointer of the last object collided with.

};
class Controllable	// Base class for all game objects that can respond to controls
{
	friend class Game;
public:
	virtual void Init(Game* parentGamePointer, Texture& tex);
	virtual void Update(float elapsed);
	virtual void Destroy(Game* parentGamePointer);

protected:
	Object* controllable_member = nullptr;	// Yes, this is a disgusting, lazy solution for giving ControlUpdate access. I'll fix it later.
	Vector2f velocity = { 0, 0 };			// Velocity value, to preserve momentum (used with the Decay function)
};


// Specials //

class Player : Object, Physics, Controllable
{
public:
	virtual void Init(Game* pointerGame_In, Texture& tex);
	virtual void Update(float elapsed);

};
class Obstacle : public Object, Physics
{
public:
	virtual void Init(Game* pointerGame_In, Texture& tex);
	virtual void Update(float elapsed);
	virtual void Destroy(Game* parentGamePointer);

};


// Generics //

class Static_Environment : Object			// This is used for things like backgrounds and other permenant objects.
{
public:
	virtual void Init(Game* parentGamePointer, Texture& tex);
	virtual void Destroy(Game* parentGamePointer);
};
class Dyn_Environment : Object, Physics		// This is used for things like obstacles, where they might be deleted and recreated often.
{
public:
	virtual void Init(Game* parentGamePointer, Texture& tex);
	virtual void Destroy(Game* parentGamePointer);
};
