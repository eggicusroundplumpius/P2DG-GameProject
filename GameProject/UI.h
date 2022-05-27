#pragma once
#include "Utils.h"
#include "Game.h"

struct UI
{
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

	/// ///////////////////////////////////////////////////////////
	///
	/// Changes the current screen mode when called.
	/// 
	/// \param mode - mode to change to.
	/// 
	/// ///////////////////////////////////////////////////////////
	void changeMode(gameMode const& mode, UtilityBelt* pointerUtils);

	bool modeChanged;			// Indicates whether the current mode has changed to certain functions
	Vector2f percentBounds;		// Represents a single percent of the window's resolution - useful for UI placement
	Resource* pointerResource;	// Pointer to root Resource object
	Game* pointerGame;
	UtilityBelt* pointerUtils;

	enum class windowMode {windowed, borderless, fullscreen};	// Window Mode, indicating the type of window the game should run in
	enum class elementType {button, textbox, picturebox};		// Element type, indicating a derrived type of UI Element

	/// ///////////////////////////////////////////////////////////
	///
	/// Base type for any UI Element, holds all common UI element
	/// values.
	/// 
	/// ///////////////////////////////////////////////////////////
	struct Element
	{
		UI* pointerUI = nullptr;		// Pointer to parent UI object
		sf::RectangleShape Frame;		// Element Frame
		sf::FloatRect globalBounds;
		sf::Vector2i dimensions;		// Element Global Dimensions
		elementType type;				// Type of Element, as initialisd through derrived structs

		Drawable* pointerDrawMember;	// Pointer to drawable member within object

		bool visible, enabled;			// Should this be drawable, and updatable?

		/// ///////////////////////////////////////////////////////////
		///
		/// Initialisation function - performs many one-time only
		/// actions, intended to prepare the instance to run. All
		/// UI Elements derrive this function.
		/// 
		/// \param pointerUI_In - pointer parent to UI object
		/// 
		/// ///////////////////////////////////////////////////////////
		void Init(UI* pointerUI_In, Element* pointerObject_In);
	};

	/// ///////////////////////////////////////////////////////////
	///
	/// Base alt-type for UI Elements, intended for any derrived
	/// type that is interactable (Buttons, etc.)
	/// 
	/// ///////////////////////////////////////////////////////////
	struct Interactable
	{
		bool selected;						// Indicates if the current instance is the selected element
		sf::Sprite customFrame;				// Custom frame to hold a sprite and/or animation, if necessary
		void* functionPointer = nullptr;	// Pointer to function that will trigger as a result of interaction

		void Update();

		/// ///////////////////////////////////////////////////////////
		///
		/// Hover function - intended to perform a task when the cursor
		/// is registered to be hovering over the current instance.
		/// 
		/// ///////////////////////////////////////////////////////////
		void Hover();
		/// ///////////////////////////////////////////////////////////
		///
		/// Click event function - intended to perform a task when a
		/// click event is registered on the current instance.
		/// 
		/// ///////////////////////////////////////////////////////////
		void Click(sf::Mouse::Button const& mouseButton);
		/// ///////////////////////////////////////////////////////////
		///
		/// Hold event function - intended to perform a task when a
		/// mouse down event is registered and is held.
		/// 
		/// ///////////////////////////////////////////////////////////
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
	};

	/// ///////////////////////////////////////////////////////////
	///
	/// Button type, for objects that should behave as buttons.
	/// Derrived Element and Interactable types.
	/// 
	/// ///////////////////////////////////////////////////////////
	struct Button : public Element, Interactable
	{
		sf::Text text;
		//elementType type = elementType::button;
		Drawable* pointerDrawMember = &this->text;
	};

	/// ///////////////////////////////////////////////////////////
	///
	/// TextBox type, for objects that should behave as textboxes.
	/// Not interactable, derrived Element type.
	/// 
	/// ///////////////////////////////////////////////////////////
	struct TextBox : public Element
	{
		sf::Text text;
		//elementType type = elementType::textbox;
		//Drawable* pointerDrawMember = &this->text;
	};

	/// ///////////////////////////////////////////////////////////
	///
	/// PictureBox type, for objects that should behave as
	/// pictureboxes. Not interactable, derrived Element type.
	/// 
	/// ///////////////////////////////////////////////////////////
	struct PictureBox : public Element
	{
		sf::Sprite sprite;
		//elementType type = elementType::picturebox;
		Drawable* pointerDrawMember = &this->sprite;
	};

	TextBox title;		// Title Text
	Button play;		// Play Button
	Button options;		// Options Button
	Button mute;		// Mute Button
	Button exit;		// Exit Button

	Button back;		// Back Button
	Button music;		// Music Toggle Button
	Button fullscreen;	// Fullscreen Toggle Button

	TextBox health;		// Health Text
	TextBox score;		// Score Text
	Button pause;		// Pause Button

	std::vector <Drawable*> Drawables;	// Vector for all visible drawable members of all UI Element instances
	std::vector <Element*> Elements;	// Vector for all UI Element instances
};

class UI_Base
{

};

class UI_Controller
{

};

class UI_Frame : UI_Base, UI_Controller
{

};

