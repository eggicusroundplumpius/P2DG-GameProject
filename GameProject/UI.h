#pragma once
#include <iostream>
#include "Utils.h"
#include "Game.h"

enum class elementType { textbox, picturebox, button };

class UI_Element;

class UI_Frame
{
	friend struct TextBox;
	friend struct PictureBox;
	friend struct Button;
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
	void Update(RenderWindow& window, Event event);
	/// ///////////////////////////////////////////////////////////
	///
	/// Render function - intended to collate all elements visible
	/// and draw them upon the given window.
	/// 
	/// \param window - window to draw to
	/// 
	/// ///////////////////////////////////////////////////////////
	std::vector<Drawable*> Render();

	std::vector<UI_Element*> elements;		// Vector for all UI Element instances
	Vector2f percentBounds;					// Represents a single percent of the window's resolution - useful for UI placement

	std::vector <Drawable*> drawables;		// Vector for all visible drawable members of all UI Element instances
protected:
	Resource* pointerResource;				// Pointer to root Resource object
	Game* pointerGame;						// Pointer to root Game object
	UtilityBelt* pointerUtils;				// Pointer to root Utility object

private:
	sf::FloatRect frame;					// Size of frame
	sf::RectangleShape debugBounds;			// Debug Outline
	int selectedInteractable;				// Vector index of interactable element currently selected
};

class UI_Element // Analagous to Base UI (see diagram in book)
{
	friend class UI_Frame;
public:
	virtual void Init(
		UI_Frame& parentFramePointer,
		Vector2f bounds = { Defaults::windowResolution.width / 2.f, Defaults::windowResolution.height / 2.f },
		bool visible = true,
		bool enabled = true);
	void RenderUpdate(std::vector<sf::Drawable*>& drawables);

	sf::FloatRect globalBounds;						// Overall Bounds of an element
	sf::RectangleShape debugBounds;					// Debug boundaries
	bool visible, enabled = true;					// Should this be drawable, and updatable?
	elementType type;								// What type is this element? (I know, I'm lazy and this isn't that elegant)
	std::vector<Drawable*> drawable_Subelements;	// Subelements (text, rectangles, compound shapes, etc.) that can be drawn

	UI_Frame* parentFramePointer;				// Pointer to parent UI object
protected:
	Resource* pointerResource;					// Pointer to root Resource object
	Game* pointerGame;							// Pointer to root Game object
	UtilityBelt* pointerUtils;					// Pointer to root Utility object
	

};

class UI_Interactable	// Interactable class for any elements that can trigger events
{
public:
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

struct TextBox : UI_Element
{
	virtual void Init(
		UI_Frame& parentFramePointer,
		Vector2f bounds = { Defaults::windowResolution.width / 2.f, Defaults::windowResolution.height / 2.f },
		bool visible = true,
		bool enabled = true);

	bool setPosition(Vector2f position);

	sf::Text text;
	sf::RectangleShape box;

	Vector2f spacing;
	bool boxVisible;

	elementType type = elementType::textbox;
};
struct Button : UI_Element, UI_Interactable
{
	sf::Text text;
	sf::RectangleShape rectangle;
	sf::Sprite image;

	elementType type = elementType::button;
};
struct PictureBox : UI_Element
{
	sf::Sprite sprite;
	elementType type = elementType::picturebox;
};