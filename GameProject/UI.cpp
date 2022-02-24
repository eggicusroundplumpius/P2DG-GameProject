#include "UI.h"

/* Core UI Functions */

	void UI::Init(Resource* pointerResource_In, Game* pointerGame_In)
	{
		pointerResource = pointerResource_In;
		pointerGame = pointerGame_In;
		modeChanged = true;
	}
	void UI::Update(RenderWindow& window, Event event, Game::Mode const& mode)
	{
		percentBounds = { (float)window.getSize().x / 100.f, (float)window.getSize().y / 100.f }; // Set percentage values for current screen size
		if (modeChanged)	// If the screen mode has changed..
		{
			Elements.clear();	// Clear the UI elements on screen
			switch (mode) {
			case (Game::Mode::menuRoot):	// If the screen has changed to the root menu..

				//Title TextBox
				title.Init(this, &title);													//Initialise the title (add to elements)
				title.type = elementType::textbox;											//Set the title element type
				title.visible = true;														//Make it visible

				title.text.setString("Game Project");										//Set the text to the main title
				title.text.setFillColor(sf::Color::Green);									//and set the colour to green
				title.text.setFont(UI::pointerResource->DSEG14Classic.Light);				//Set the font
				title.text.scale((float)Defaults::fontSize, (float)Defaults::fontSize);		//and scale the text to the default size
				title.globalBounds = title.text.getGlobalBounds();							//Get the overall boundaries of the element
				title.text.setPosition((percentBounds.x * 2.f), (percentBounds.y * 2.f));	//and set the position based on percentage values of the window's size
				title.pointerDrawMember = &title.text;										//Set the drawable member of this instance

				//Play Button
				play.Init(this, &play);
				play.Frame.setPosition(percentBounds.x * 75.f, percentBounds.y * 33.3f);
				play.text.setPosition(percentBounds.x * 75.f, percentBounds.y * 33.3f);
				play.text.setString("Play");

				//Options Button
				options.Init(this, &options);
				options.Frame.setPosition(percentBounds.x * 75.f, percentBounds.y * 66.6f);
				options.text.setPosition(percentBounds.x * 75.f, percentBounds.y * 66.6f);
				options.text.setString("Options");

				//Mute Button
				mute.Init(this, &mute);
				mute.Frame.setPosition(percentBounds.x * 90.f, percentBounds.y * 10.f);
				mute.customFrame.setPosition(percentBounds.x * 90.f, percentBounds.y * 10.f);
				mute.customFrame.setTexture(pointerResource->iconMute);

				//Exit Button
				exit.Init(this, &exit);
				exit.Frame.setPosition(percentBounds.x * 90.f, percentBounds.y * 10.f);
				exit.Frame.setSize(Defaults::iconSize);
				exit.customFrame.setPosition(percentBounds.x * 90.f, percentBounds.y * 10.f);
				exit.customFrame.setTexture(pointerResource->iconExit);
				exit.customFrame.setTextureRect(exit.Frame.getTextureRect());

				modeChanged = false;
				break;

			case (Game::Mode::menuOptions):
				
				//Title TextBox
				title.Init(this, &title);
				title.text.setPosition(percentBounds.x * 50.f, percentBounds.y * 25.f);
				title.text.setString("Options");
				title.text.setScale(30.f, 30.f);

				//Back Button
				back.Frame.setPosition(percentBounds.x * 10.f, percentBounds.y * 10.f);
				back.customFrame.setTexture(pointerResource->iconBack);

				break;

			case (Game::Mode::gamePlay):	// If the screen has changed to gameplay...

				//Health Text
				health.Init(this, &health);			//Initialise health text (add it to elements)
				health.type = elementType::textbox;	//Set the type to textbox
				health.visible = true;				//Make it visible
				health.enabled = true;				//and updatable
				
				health.text.setString("Health: ");														//Set the base string
				health.text.setFillColor(sf::Color::Green);												//Make it green
				health.text.setFont(UI::pointerResource->DSEG14Classic.Light);							//Set the font
				health.text.scale((float)Defaults::fontSize - 2.f, (float)Defaults::fontSize - 2.f);	//Set the scale based on defaults
				health.globalBounds = health.text.getGlobalBounds();									//Get the overall bounds of the element
				health.text.setPosition((percentBounds.x * 2.f), (percentBounds.y * 2.f));				//Set the position as a percentage value of the window size
				health.pointerDrawMember = &health.text;												//Set the drawable member of this instance

				//Score Text
				score.Init(this, &score);			//Initialise health text (add it to elements)
				score.type = elementType::textbox;	//Set the type to textbox
				score.visible = true;				//Make it visible
				score.enabled = true;				//and updatable

				score.text.setString("Score: ");																			//Set the base string
				score.text.setFillColor(sf::Color::Green);																	//Make it green
				score.text.setFont(UI::pointerResource->DSEG14Classic.Light);												//Set the font
				score.text.scale((float)Defaults::fontSize - 2.f, (float)Defaults::fontSize - 2.f);							//Set the scale based on defaults
				score.globalBounds = score.text.getGlobalBounds();															//Get the overall bounds of the element
				score.text.setPosition((percentBounds.x * 2.f), (percentBounds.y * 2.f)+score.globalBounds.height * 1.2);
				score.pointerDrawMember = &score.text;

				modeChanged = false;
				break;
			}
			pointerGame->changeMode(pointerGame->currentMode);
		}

		health.text.setString("Health: " + to_string(pointerGame->lives));
		health.globalBounds = health.text.getGlobalBounds();
		health.text.setPosition((percentBounds.x * 2.f), (percentBounds.y * 2.f));

		score.text.setString("Score: " + to_string(pointerGame->score));
		score.globalBounds = score.text.getGlobalBounds();
		score.text.setPosition((percentBounds.x * 2.f), (percentBounds.y * 2.f) + score.globalBounds.height * 1.2);

	}
	void UI::Render(RenderWindow& window)
	{
		Drawables.clear();
		for (Element* element : Elements)
		{
			if (element->visible)
			{
				switch (element->type) 
				{
				case (elementType::button):
					Drawables.push_back(&element->Frame);
					Drawables.push_back(element->pointerDrawMember);
					break;
				
				case (elementType::textbox):
					Drawables.push_back(&element->Frame);
					Drawables.push_back(element->pointerDrawMember);
					break;
				
				case (elementType::picturebox):
					Drawables.push_back(&element->Frame);
					Drawables.push_back(element->pointerDrawMember);
					break;
				}
			}
		}
	}
	void UI::changeMode(Game::Mode const& mode)
	{
		modeChanged = true;
		pointerGame->changeMode(mode);
	}

/* Element Instance Functions */

	void UI::Element::Init(UI* pointerUI_In, Element* pointerObject_In)
	{
		pointerUI = pointerUI_In;
		pointerUI->Elements.push_back(pointerObject_In);
	}

/* Interactable Instance Functions */

	void UI::Interactable::Update()
	{
		if (customFrame.getTexture())
		{

		}
	}
	void UI::Interactable::Hover()
	{

	}
	void UI::Interactable::Click(sf::Mouse::Button const& mouseButton)
	{
		
	}
	void UI::Interactable::Hold(sf::Mouse::Button const& mouseButton)
	{

	}
	void UI::Interactable::Drag(sf::Mouse::Button const& mouseButton)
	{

	}
