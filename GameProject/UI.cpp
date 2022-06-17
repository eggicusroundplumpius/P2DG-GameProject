#include "UI.h"

/* UI Frame Functions */

void UI_Frame::Init(Resource* pointerResource_In, Game* pointerGame_In, UtilityBelt* pointerUtils_In)
{
	pointerResource = pointerResource_In;
	pointerGame = pointerGame_In;
	pointerUtils = pointerUtils_In;
}
void UI_Frame::Update(RenderWindow& window, Event event)
{
	percentBounds = { (float)window.getSize().x / 100.f, 
					(float)window.getSize().y / 100.f };					// Set percentage values for current screen size

	/*health.text.setString("Health: " + to_string(pointerGame->lives));
	health.globalBounds = health.text.getGlobalBounds();
	health.text.setPosition((percentBounds.x * 2.f), (percentBounds.y * 2.f));

	score.text.setString("Score: " + to_string(pointerGame->score));
	score.globalBounds = score.text.getGlobalBounds();
	score.text.setPosition((percentBounds.x * 2.f), (percentBounds.y * 2.f) + score.globalBounds.height * 1.2);*/
}
std::vector<Drawable*> UI_Frame::Render()
{
	drawables.clear();														// Clear the drawable object list, so it can be rewritten with updated information
	for (UI_Element* element : elements) element->RenderUpdate(drawables);	// Update the render information for each element (visibility, etc.)

	return drawables;
}

/* Element Instance Functions */

void UI_Element::Init(UI_Frame& parentFramePointer, Vector2f bounds, bool visible, bool enabled)
{
	this->parentFramePointer = &parentFramePointer;
	parentFramePointer.elements.push_back(this);

	visible = this->visible;
	enabled = this->enabled;
}

void UI_Element::RenderUpdate(std::vector<sf::Drawable*>& drawables)
{
	if (visible)
	{
		for (Drawable* subelement : drawable_Subelements) drawables.push_back(subelement);
	}
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

void TextBox::Init(UI_Frame& parentFramePointer, Vector2f bounds, bool visible, bool enabled) 
{
	text.setString("test");
	text.setFont(pointerResource->DSEG14Classic.Regular);
	text.setFillColor(sf::Color::White);
	text.setPosition(0.f, 0.f);
	
	drawable_Subelements.push_back(&text);
	drawable_Subelements.push_back(&box);

	UI_Element::Init(parentFramePointer, bounds, visible, enabled);
}