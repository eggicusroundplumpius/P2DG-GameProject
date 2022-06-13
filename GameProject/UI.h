#pragma once
#include "Utils.h"
#include "Game.h"

class UI_Frame
{
public:
	/// ///////////////////////////////////////////////////////////
	///
	/// Initialisation function - performs many one-time only
	/// actions, intended to prepare the UI to run.
	/// 
	/// \param pointerResource_In - Pointer to root Resource object
	/// \param pointerGame_In - Pointer to colleuge root Game 
	/// object
	/// 
	/// ///////////////////////////////////////////////////////////
	void Init(Resource* pointerResource_In, Game* pointerGame_In, UtilityBelt* pointerUtils_In);
	/// ///////////////////////////////////////////////////////////
	///
	/// Update function - update the UI, including refreshing
	/// information written to UI elements and handling the 
	/// changing of screens
	/// 
	/// \param window - window to work in
	/// \param event 
	/// \param mode - The current game mode, to decide what screen
	/// to show
	/// 
	/// ///////////////////////////////////////////////////////////
	void Update(RenderWindow& window, Event event, gameMode const& mode);
	/// ///////////////////////////////////////////////////////////
	///
	/// Render function - intended to collate all elements visible
	/// and draw them upon the given window.
	/// 
	/// \param window - window to draw to
	/// 
	/// ///////////////////////////////////////////////////////////
	void Render(RenderWindow& window);

	std::vector <UI_Element*> elements;		// Vector for all UI Element instances
	Vector2f percentBounds;					// Represents a single percent of the window's resolution - useful for UI placement

private:
	sf::FloatRect frame;
	std::vector <Drawable*> drawables;		// Vector for all visible drawable members of all UI Element instances
	Resource* pointerResource;				// Pointer to root Resource object
	Game* pointerGame;						// Pointer to root Game object
	UtilityBelt* pointerUtils;				// Pointer to root Utility object
};

class UI_Element // Analagous to Base UI (see diagram in book)
{
public:
	void Init(UI_Frame& parentFramePointer);

	sf::FloatRect globalBounds;
	sf::Vector2i dimensions;					// Element Global Dimensions
	bool visible, enabled;						// Should this be drawable, and updatable?

private:
	std::vector<Drawable*> drawable_Subelements;	// Subelements (text, rectangles, compound shapes, etc.) that can be drawn
	UI_Frame* parentFramePointer;					// Pointer to parent UI object
};

class UI_Interactable
{
public:
	sf::Sprite customFrame;		// Custom frame to hold a sprite and/or animation, if necessary

	/// <summary>
	/// Update function - should be called every general update
	/// </summary>
	void Update();

	/// <summary>
	/// Click event function - in the event of a click, what should
	/// happen?
	/// </summary>
	void Click(sf::Mouse::Button const& mouseButton);

	/// <summary>
	/// Hold event function - intended to perform a task when a
	/// mouse down event is registered and is held.
	/// </summary>
	void Hold(sf::Mouse::Button const& mouseButton);

	/// ///////////////////////////////////////////////////////////
	///
	/// Drag event function - intended to interact with another 
	/// object when a hold event is registered and the mouse is
	/// moving. Should only be triggered when the target object 
	/// is flagged as draggable.
	/// 
	/// ///////////////////////////////////////////////////////////
	void Drag(sf::Mouse::Button const& mouseButton);
	
private:
	void* functionPointer = nullptr;	// Pointer to function that will trigger as a result of interaction
};

class Button : public UI_Element, UI_Interactable
{
	sf::Text text;
	sf::RectangleShape rectangle;
};

class TextBox : public UI_Element
{
	sf::Text text;
};

class PictureBox : public UI_Element
{
	sf::Sprite sprite;
};