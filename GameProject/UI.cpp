#include "UI.h"

/* Core UI Functions */

	/// ///////////////////////////////////////////////////////////
	///
	/// Initialisation function - performs many one-time only
	/// actions, intended to prepare the UI to run.
	/// 
	/// ///////////////////////////////////////////////////////////
	void UI::Init(Resource* resource)
	{
		pointerResource = resource;
		modeChanged = true;
	}

	/// ///////////////////////////////////////////////////////////
	///
	/// Update function - intended to update elements and provide
	/// branches for triggered events.
	/// 
	/// ///////////////////////////////////////////////////////////
	void UI::Update(RenderWindow& window, Event event, const Game::Mode& mode)
	{
		percentBounds = { (float)window.getSize().x / 100.f, (float)window.getSize().y / 100.f };
		if (modeChanged)
		{
			Elements.clear();
			switch (mode) {
			case (Game::Mode::menuRoot):

				//Title TextBox
				title.Init(this);
				title.text.setPosition(percentBounds.x * 50.f, percentBounds.y * 50.f);
				title.text.setString("Game Project");
				title.text.setScale((float)Defaults::fontSize, (float)Defaults::fontSize);
				if (title.visible) Drawables.push_back(&title.text);

				//Play Button
				play.Init(this);
				play.Frame.setPosition(percentBounds.x * 75.f, percentBounds.y * 33.3f);
				play.text.setPosition(percentBounds.x * 75.f, percentBounds.y * 33.3f);
				play.text.setString("Play");
				if (play.visible) { Drawables.push_back(&play.Frame); Drawables.push_back(&play.text); }

				//Options Button
				options.Init(this);
				options.Frame.setPosition(percentBounds.x * 75.f, percentBounds.y * 66.6f);
				options.text.setPosition(percentBounds.x * 75.f, percentBounds.y * 66.6f);
				options.text.setString("Options");
				if (options.visible) Drawables.push_back(&options.Frame);

				//Mute Button
				mute.Init(this);
				mute.Frame.setPosition(percentBounds.x * 90.f, percentBounds.y * 10.f);
				mute.customFrame.setPosition(percentBounds.x * 90.f, percentBounds.y * 10.f);
				mute.customFrame.setTexture(pointerResource->iconMute);
				if (mute.visible) { Drawables.push_back(&mute.Frame); Drawables.push_back(&mute.customFrame); }

				//Exit Button
				exit.Init(this);
				exit.Frame.setPosition(percentBounds.x * 90.f, percentBounds.y * 10.f);
				exit.Frame.setSize(Defaults::iconSize);
				exit.customFrame.setPosition(percentBounds.x * 90.f, percentBounds.y * 10.f);
				exit.customFrame.setTexture(pointerResource->iconExit);
				exit.customFrame.setTextureRect(exit.Frame.getTextureRect());

			case (Game::Mode::menuOptions):
				
				//Title TextBox
				title.Init(this);
				title.text.setPosition(percentBounds.x * 50.f, percentBounds.y * 25.f);
				title.text.setString("Options");
				title.text.setScale(30.f, 30.f);

				//Back Button
				back.Frame.setPosition(percentBounds.x * 10.f, percentBounds.y * 10.f);
				back.customFrame.setTexture(pointerResource->iconBack);
			}
		}
	}

	/// ///////////////////////////////////////////////////////////
	///
	/// Render function - intended to collate all elements visible
	/// and draw them upon the given window.
	/// 
	/// \param window - window to draw to
	/// 
	/// ///////////////////////////////////////////////////////////
	void UI::Render(RenderWindow& window)
	{
		for (Element* element : Elements)
		{
			if (element->visible)
			{
				if (element->type == elementType::button)
				{
					Drawables.push_back(&element->Frame);
					Drawables.push_back(element->pointerDrawMember);
				}
				else if (element->type == elementType::textbox)
				{
					Drawables.push_back(&element->Frame);
					Drawables.push_back(element->pointerDrawMember);
				}
				else if (element->type == elementType::picturebox)
				{
					Drawables.push_back(&element->Frame);
					Drawables.push_back(element->pointerDrawMember);
				}
			}
		}
	}

/* Element Instance Functions */

	/// ///////////////////////////////////////////////////////////
	///
	/// Initialisation function - performs many one-time only
	/// actions, intended to prepare the instance to run. All
	/// UI Elements derrive this function.
	/// 
	/// \param pointerUI_In - pointer parent to UI object
	/// 
	/// ///////////////////////////////////////////////////////////
	void UI::Element::Init(UI* pointerUI_In)
	{
		pointerUI = pointerUI_In;
		pointerUI->Elements.push_back(this);
	}

/* Interactable Instance Functions */

	void UI::Interactable::Update()
	{
		if (customFrame.getTexture())
		{

		}
	}

	/// ///////////////////////////////////////////////////////////
	///
	/// Hover function - intended to perform a task when the cursor
	/// is registered to be hovering over the current instance.
	/// 
	/// ///////////////////////////////////////////////////////////
	void UI::Interactable::Hover()
	{

	}

	/// ///////////////////////////////////////////////////////////
	///
	/// Click event function - intended to perform a task when a
	/// click event is registered on the current instance.
	/// 
	/// ///////////////////////////////////////////////////////////
	void UI::Interactable::Click(sf::Mouse::Button const& mouseButton)
	{
		
	}

	/// ///////////////////////////////////////////////////////////
	///
	/// Hold event function - intended to perform a task when a
	/// mouse down event is registered and is held.
	/// 
	/// ///////////////////////////////////////////////////////////
	void UI::Interactable::Hold(sf::Mouse::Button const& mouseButton)
	{

	}

	/// ///////////////////////////////////////////////////////////
	///
	/// Drag event function - intended to interact with another 
	/// object when a hold event is registered and the mouse is
	/// moving. Should only be triggered when the target object 
	/// is flagged as draggable.
	/// 
	/// ///////////////////////////////////////////////////////////
	void UI::Interactable::Drag(sf::Mouse::Button const& mouseButton)
	{

	}

/* Interactable Triggered Functions*/

	void UI::changeScreen(Game::Mode const& mode)
	{

	}