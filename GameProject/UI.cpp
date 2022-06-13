#include "UI.h"

/* Core UI Functions */

void UI_Frame::Init(Resource* pointerResource_In, Game* pointerGame_In, UtilityBelt* pointerUtils_In)
{
	pointerResource = pointerResource_In;
	pointerGame = pointerGame_In;
	pointerUtils = pointerUtils_In;
}
void UI_Frame::Update(RenderWindow& window, Event event, gameMode const& mode)
{
	percentBounds = { (float)window.getSize().x / 100.f, (float)window.getSize().y / 100.f }; // Set percentage values for current screen size

	health.text.setString("Health: " + to_string(pointerGame->lives));
	health.globalBounds = health.text.getGlobalBounds();
	health.text.setPosition((percentBounds.x * 2.f), (percentBounds.y * 2.f));

	score.text.setString("Score: " + to_string(pointerGame->score));
	score.globalBounds = score.text.getGlobalBounds();
	score.text.setPosition((percentBounds.x * 2.f), (percentBounds.y * 2.f) + score.globalBounds.height * 1.2);

}
void UI_Frame::Render(RenderWindow& window)
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

/* Element Instance Functions */

void UI_Element::Init(UI_Frame& parentFramePointer)
{
	this->parentFramePointer = &parentFramePointer;
	parentFramePointer.elements.push_back(this);
}

/* Interactable Instance Functions */

void UI_Interactable::Update()
{

}
void UI_Interactable::Click(sf::Mouse::Button const& mouseButton)
{
		
}
void UI_Interactable::Hold(sf::Mouse::Button const& mouseButton)
{

}
void UI_Interactable::Drag(sf::Mouse::Button const& mouseButton)
{

}
