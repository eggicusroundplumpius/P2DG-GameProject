
#include "Utils.h"

void shapelistDraw(std::vector <sf::Drawable*> &shapes, sf::RenderWindow& window)
{
	for (Drawable* shape : shapes)
	{
		window.draw(*shape);
	}
}

bool UtilityBelt::Load(vector<sf::Font*>& loadObjects, const vector<string>& loadPaths)
{
	return false;
}
