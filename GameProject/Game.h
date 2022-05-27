#pragma once

#include "Utils.h"


struct Game
{
	enum class Type {Player, Enemy, Static_Environment, Dyn_Environment}; //Object Type

	/// ///////////////////////////////////////////////////////////
	///
	/// Initialisation function - performs many one-time only
	/// actions, intended to prepare the game to run.
	/// 
	/// ///////////////////////////////////////////////////////////
	void Init(Resource* pointerResource_In);

	/// ///////////////////////////////////////////////////////////
	///
	/// Primary render function: contains cases for main screens 
	/// available, handles drawing-related functions.
	/// 
	/// \param window - Main window object to draw to.
	/// \param elapsed - elapsed time in seconds since last update.
	/// 
	/// ///////////////////////////////////////////////////////////
	void Update(sf::RenderWindow& window, Event event, float elapsed);

	/// ///////////////////////////////////////////////////////////
	///
	/// Primary render function: contains cases for main screens 
	/// available, handles drawing-related functions.
	/// 
	/// \param window - Main window object to draw to.
	/// \param elapsed - elapsed time in seconds since last update.
	/// 
	/// ///////////////////////////////////////////////////////////
	void Render(sf::RenderWindow& window, float elapsed);

	/// ///////////////////////////////////////////////////////////
	///
	/// Updates player object position, speed and takes input.
	/// 
	/// \param windowSize - Main window size
	/// \param elapsed - elapsed time in seconds since last update.
	/// 
	/// ///////////////////////////////////////////////////////////
	void PlayerUpdate(Vector2f const& windowSize, float elapsed);

	/// ///////////////////////////////////////////////////////////
	///
	/// Changes the current mode - exists to be called from UI
	/// side.
	/// 
	/// \param mode - The mode to change to
	/// 
	/// ///////////////////////////////////////////////////////////
	void changeMode(gameMode mode);

	Resource* pointerResource;		// Pointer to root resource object

	/////////////////////////
	/// Basic Information
	/////////////////////////

	const float gameVersion = 0.1f;		// Release Version of the Game
	int score = 0;						// Player Score in current game
	int lives = 3;						// Player Lives in current game
	gameMode currentMode = gameMode::gamePlay;	// Current & default screen mode
	Vector2f windowSize;				// Size of window
	Vector2f percentBounds;				// Represents a single percent of the window's resolution

	///////////////////////
	/// Object Type
	///////////////////////
	struct Object
	{
		sf::Sprite sprite;				//Sprite Object
		sf::IntRect spriteRect;			//Sprite Texture bounds, as set by bounds of texture rectangle
		sf::Vector2f position;			// Current Position of Instance
		sf::FloatRect bounds;			// Global bounds relative to world coordinates
		float collisionRadius;			// Collision radius
		sf::CircleShape physicsBounds;

		Game* pointerGame = nullptr;			//Pointer to parent game object
		Drawable* pointerDrawMember = nullptr;	//Pointer to drawable member of this instance

		/// Default Settings ///

		bool physicsEnabled;			// Control of whether this instance should trigger physics events
		bool visible;					// Control of whether or not this instance is added to the Drawables vector
		bool enabled;					// Control of move/update capabilities
		Game::Type type;				// Type of Game Object


		/// ///////////////////////////////////////////////////////////
		///
		/// Initialisation Function - Initialises the current instance,
		/// taking object type to set defaults.
		/// 
		/// \param type_In - Object type from enum
		/// \param tex - texture object sprite should have
		/// \param pointerGame_In - pointer to game object
		/// 
		/// ///////////////////////////////////////////////////////////
		void Init(Game::Type type_In, sf::Texture& tex, Game* pointerGame_In);

		/// ///////////////////////////////////////////////////////////
		///
		/// Update function - updates the current instance.
		/// 
		/// \param elapsed - Time since last update in seconds
		/// 
		/// ///////////////////////////////////////////////////////////
		void Update(float elapsed);

		/// ///////////////////////////////////////////////////////////
		///
		/// Collision detection function - detects if the current 
		/// instance is colliding with another physics-registered
		/// instance.
		/// 
		/// ///////////////////////////////////////////////////////////
		bool IsColliding();

		/// ///////////////////////////////////////////////////////////
		///
		/// Destroy function - destroys the current instance from
		/// within.
		/// 
		/// ///////////////////////////////////////////////////////////
		void Destroy();
	};
	
	/////////////////////////////
	/// Object Initialisation ///
	/////////////////////////////

	Object background;	// Background Object - Static
	Object ground;		// Ground Object - Dynamic (Paralax)
	Object player;		// Player Object - Active

	std::vector <Object*> Objects;		// Vector of objects to keep track of all instances
	std::vector <Drawable*> Drawables;	// Vector of drawables to pass into the draw function
	std::vector <Drawable*> Debug;		// Vector of Debug Drawables
};
