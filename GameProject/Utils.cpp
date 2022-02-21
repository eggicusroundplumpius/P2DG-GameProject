
#include <assert.h>
#include <iostream>

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
	int i = 0;
	int missingCount = 0;
	for (vector <string> fontLib : loadPaths)
	{
		//Regular
		if (!fontLib[0].empty())
		{
			std::cout << "Attempting to load " << fontLib[0] << "\n";
			loadObjects[i]->Regular.loadFromFile(fontLib[0]);
		}
		else missingCount++;
		//Italic
		if (!fontLib[1].empty())
		{
			std::cout << "Attempting to load " << fontLib[1] << "\n";
			loadObjects[i]->Italic.loadFromFile(fontLib[1]);
		}
		else missingCount++;
		//Bold
		if (!fontLib[2].empty())
		{
			std::cout << "Attempting to load " << fontLib[2] << "\n";
			loadObjects[i]->Bold.loadFromFile(fontLib[2]);
		}
		else missingCount++;
		//Bold Italic
		if (!fontLib[3].empty())
		{
			std::cout << "Attempting to load " << fontLib[3] << "\n";
			loadObjects[i]->BoldItalic.loadFromFile(fontLib[3]);
		}
		else missingCount++;
		//Light
		if (!fontLib[4].empty())
		{
			std::cout << "Attempting to load " << fontLib[4] << "\n";
			loadObjects[i]->Light.loadFromFile(fontLib[4]);
		}
		else missingCount++;
		//Light Italic
		if (!fontLib[5].empty())
		{
			std::cout << "Attempting to load " << fontLib[5] << "\n";
			loadObjects[i]->LightItalic.loadFromFile(fontLib[5]);
		}
		else missingCount++;

		if (missingCount >= 5) return false;

		missingCount = 0;
		i++;
	}
	return true;
}
bool UtilityBelt::Load(std::vector<sf::Texture*> const& loadObjects, vector<string> const& loadPaths)
{
	if (loadObjects.size() != loadPaths.size()) return false;

	int i = 0;
	for (std::string path : loadPaths)
	{
		if (!path.empty())
		{
			std::cout << "Attempting to Load " << path << "\n";
			loadObjects[i]->loadFromFile(path);
		}
		else return false;

		i++;
	}
	return true;
}