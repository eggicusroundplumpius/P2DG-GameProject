#include "Render.h"

/* class Render */
void Render::Init(sf::RenderWindow& window)
{
	//drawWindow = window;
}
void Render::Update()
{
	//draw();
}

void Render::draw(std::vector<sf::Drawable*>& uiDrawables, std::vector<sf::Drawable*>& gameDrawables, sf::RenderWindow& window)
{
	std::vector<sf::Drawable*> collatedDrawables;

	for (Drawable* i : gameDrawables) collatedDrawables.push_back(i);
	for (Drawable* i : uiDrawables) collatedDrawables.push_back(i);

	for (Drawable* object : collatedDrawables) window.draw(*object);
}