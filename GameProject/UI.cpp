#include "UI.h"

/* Core UI Functions */

	/// ///////////////////////////////////////////////////////////
	///
	/// Initialisation function - performs many one-time only
	/// actions, intended to prepare the UI to run.
	/// 
	/// ///////////////////////////////////////////////////////////
	void UI::Init()
	{
		modeChanged = true;
	}

	/// ///////////////////////////////////////////////////////////
	///
	/// Update function - intended to update elements and provide
	/// branches for triggered events.
	/// 
	/// ///////////////////////////////////////////////////////////
	void UI::Update(RenderWindow& window, const Game::Mode& mode)
	{
		if (modeChanged)
		{
			switch (mode) {
			case (Game::Mode::menuRoot):

				TextBox title;
				title.text.setPosition((float)window.getSize().x / 2.f, (float)window.getSize().y / 3.f);
				Elements.push_back(title);

				Button play;
				play.Frame.setPosition((float)window.getSize().x / 2u, (float)window.getSize().y / 2u);
				Elements.push_back(play);

				Button options;
				Elements.push_back(options);

				Button mute;
				Elements.push_back(mute);

				Button exit;
				Elements.push_back(exit);
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

	}



void UI::Element::Init(UI* pointerUI_In)
{
	pointerUI = pointerUI_In;

	pointerUI->Drawables.push_back(&this->Frame);
}

/* Interactable Instance Functions */

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
	void UI::Interactable::Click(sf::Mouse::Button const mouseButton)
	{
		
	}

	/// ///////////////////////////////////////////////////////////
	///
	/// Hold event function - intended to perform a task when a
	/// mouse down event is registered and is held.
	/// 
	/// ///////////////////////////////////////////////////////////
	void UI::Interactable::Hold(sf::Mouse::Button const mouseButton)
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
	void UI::Interactable::Drag(sf::Mouse::Button const mouseButton)
	{

	}