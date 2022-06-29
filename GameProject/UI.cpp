#include "UI.h"

/* UI Frame Functions */

void UI_Frame::Init(Resource* pointerResource_In, Game* pointerGame_In, UtilityBelt* pointerUtils_In)
{
	pointerResource = pointerResource_In;
	pointerGame = pointerGame_In;
	pointerUtils = pointerUtils_In;

	frame.width = (unsigned)Defaults::windowResolution.width - 
					((unsigned)Defaults::windowResolution.width / 50u);		// Calculating a padding of 2% smaller than the window's width
	frame.left = (unsigned)Defaults::windowResolution.width / 50u;			// Offsetting coordinate to centre frame object
	frame.height = (unsigned)Defaults::windowResolution.height - 
					((unsigned)Defaults::windowResolution.height / 50u);	// "		" ... for height
	frame.top = (unsigned)Defaults::windowResolution.height / 50u;			// "		" ... for height

	if (Defaults::debugBoundaries)
	{
		debugBounds.setOutlineColor(Color::Green);
		debugBounds.setOutlineThickness(12.f);
		debugBounds.setFillColor(Color::Transparent);
		debugBounds.setSize(Vector2f{ frame.width - 12.f, frame.height - 12.f });
		debugBounds.setPosition(Vector2f{ frame.left, frame.top });
	}
	std::cout << "[" << this << "]" << " UI Frame Initialised. Size is " << frame.width << ", " << frame.height << "\n";
}
void UI_Frame::Update(RenderWindow& window, Event event)
{
	percentBounds = { (float)window.getSize().x / 100.f, 
					(float)window.getSize().y / 100.f };					// Set percentage values for current screen size

}
std::vector<Drawable*> UI_Frame::Render()
{
	drawables.clear();														// Clear the drawable object list, so it can be rewritten with updated information
	for (UI_Element* element : elements) element->RenderUpdate(drawables);	// Update the render information for each element (visibility, etc.)
	if (Defaults::debugBoundaries) drawables.push_back(&debugBounds);

	return drawables;
}

/* Element Instance Functions */

void UI_Element::Init(UI_Frame& parentFramePointer, Vector2f bounds, bool visible, bool enabled)
{
	this->parentFramePointer = &parentFramePointer;
	parentFramePointer.elements.push_back(this);

	visible = this->visible;
	enabled = this->enabled;

	if (Defaults::debugBoundaries)
	{
		debugBounds.setOutlineColor(Color::Green);
		debugBounds.setFillColor(Color::Transparent);
		debugBounds.setPosition(Vector2f{ globalBounds.width, globalBounds.height });
	}
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
	spacing = bounds / 100.f;

	box.setFillColor(Color::Transparent);
	box.setSize(bounds);
	box.setPosition(0.f, 0.f);

	text.setString("Score: ");
	text.setFont(parentFramePointer.pointerResource->DSEG14Classic.Regular);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(Defaults::fontSize);
	text.setOrigin(bounds - spacing);
	text.setPosition(bounds - spacing);
	
	drawable_Subelements.push_back(&text);
	drawable_Subelements.push_back(&box);

	UI_Element::Init(parentFramePointer, bounds, visible, enabled);
}
bool TextBox::setPosition(Vector2f position)
{
	if (!parentFramePointer->frame.contains(position))
	{
		std::cout << "[" << this << "]" << " TextBox::setPosition ERROR: position is out of bounds.";
		position = { parentFramePointer->frame.top , parentFramePointer->frame.top };
		return false;
	}
	else position -= spacing;

	text.setOrigin(position);
	text.setPosition(position);

	box.setPosition(position + spacing);

	debugBounds.setPosition(position + spacing);

	return true;
}