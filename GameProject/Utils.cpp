
#include <assert.h>
#include <iostream>

#include "Utils.h"

void draw(std::vector<sf::Drawable*>& uiDrawables, std::vector<sf::Drawable*>& gameDrawables, sf::RenderWindow& window)
{
	std::vector<sf::Drawable*> collatedDrawables;

	for (Drawable* i : uiDrawables) collatedDrawables.push_back(i);
	for (Drawable* i : gameDrawables) collatedDrawables.push_back(i);

	for (Drawable* object : collatedDrawables) window.draw(*object);
}

bool UtilityBelt::Load(std::vector<FontType*> const& loadObjects, vector<vector<string>> const& loadPaths)
{
	int i = 0;
	int missingCount = 0;
	for (vector <string> fontLib : loadPaths)
	{
		
		if (!fontLib[0].empty())
		{
			std::cout << "Attempting to load " << fontLib[0] << "\n";	//Regular
			loadObjects[i]->Regular.loadFromFile(fontLib[0]);
		}
		else missingCount++;
		
		if (!fontLib[1].empty())
		{
			std::cout << "Attempting to load " << fontLib[1] << "\n";	//Italic
			loadObjects[i]->Italic.loadFromFile(fontLib[1]);
		}
		else missingCount++;
		
		if (!fontLib[2].empty())
		{
			std::cout << "Attempting to load " << fontLib[2] << "\n";	//Bold
			loadObjects[i]->Bold.loadFromFile(fontLib[2]);
		}
		else missingCount++;
		
		if (!fontLib[3].empty())
		{
			std::cout << "Attempting to load " << fontLib[3] << "\n";	//Bold Italic
			loadObjects[i]->BoldItalic.loadFromFile(fontLib[3]);
		}
		else missingCount++;
		
		if (!fontLib[4].empty())
		{
			std::cout << "Attempting to load " << fontLib[4] << "\n";	//Light
			loadObjects[i]->Light.loadFromFile(fontLib[4]);
		}
		else missingCount++;
		
		if (!fontLib[5].empty())
		{
			std::cout << "Attempting to load " << fontLib[5] << "\n";	//Light Italic
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