
#include "Utils.h"

void shapelistDraw(std::vector<sf::Drawable*> &shapes, sf::RenderWindow& window)
{
	for (Drawable* shape : shapes)
	{
		window.draw(*shape);
	}
}

bool UtilityBelt::Load(std::vector<FontType*> const& loadObjects, vector<vector<string>> const& loadPaths)
{
	return false;
}
bool UtilityBelt::Load(std::vector<sf::Texture*> const& loadObjects, vector<string> const& loadPaths)
{
	return false;
}