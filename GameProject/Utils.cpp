
#include <assert.h>
#include <iostream>

#include "Utils.h"

void draw(std::vector<sf::Drawable*> uiDrawables, std::vector<sf::Drawable*>& gameDrawables, sf::RenderWindow& window)
{
	for (Drawable* gameDrawable : gameDrawables) window.draw(*gameDrawable);
	for (Drawable* uiDrawable : uiDrawables) window.draw(*uiDrawable);
}
Vector2f Decay(Vector2f const& inValue, float percent, float interval, float elapsed) 
{
	float mod = 1.0f - percent * (elapsed / interval);
	Vector2f outValue(inValue.x * mod, inValue.y * mod);
	return outValue;
}
bool distanceCheck(Vector2f const& position1, Vector2f const& position2, float minimumDistance) 
{
	float distance = (position1.x - position2.x) * (position1.x - position2.x) + 
				(position1.y - position2.y) * (position1.y - position2.y);
	distance = sqrtf(distance);
	return distance <= minimumDistance;
}

bool UtilityBelt::Load(std::vector<FontType*> const& loadObjects, vector<vector<string>> const& loadPaths)
{
	int i = 0;
	int missingCount = 0;
	for (vector <string> fontLib : loadPaths)
	{
		
		if (!fontLib[0].empty())
		{
			std::cout << "[" << this << "]" << " Attempting to load " << fontLib[0] << "... ";	//Regular
			loadObjects[i]->Regular.loadFromFile(fontLib[0]);
			if (loadObjects[i]) cout << "Success!" << "\n";
		}
		else missingCount++;
		
		if (!fontLib[1].empty())
		{
			std::cout << "[" << this << "]" << " Attempting to load " << fontLib[1] << "... ";	//Italic
			loadObjects[i]->Italic.loadFromFile(fontLib[1]);
			if (loadObjects[i]) cout << "Success!" << "\n";
		}
		else missingCount++;
		
		if (!fontLib[2].empty())
		{
			std::cout << "[" << this << "]" << " Attempting to load " << fontLib[2] << "... ";	//Bold
			loadObjects[i]->Bold.loadFromFile(fontLib[2]);
			if (loadObjects[i]) cout << "Success!" << "\n";
		}
		else missingCount++;
		
		if (!fontLib[3].empty())
		{
			std::cout << "[" << this << "]" << " Attempting to load " << fontLib[3] << "... ";	//Bold Italic
			loadObjects[i]->BoldItalic.loadFromFile(fontLib[3]);
			if (loadObjects[i]) cout << "Success!" << "\n";
		}
		else missingCount++;
		
		if (!fontLib[4].empty())
		{
			std::cout << "[" << this << "]" << " Attempting to load " << fontLib[4] << "... ";	//Light
			loadObjects[i]->Light.loadFromFile(fontLib[4]);
			if (loadObjects[i]) cout << "Success!" << "\n";
		}
		else missingCount++;
		
		if (!fontLib[5].empty())
		{
			std::cout << "[" << this << "]" << " Attempting to load " << fontLib[5] << "... ";	//Light Italic
			loadObjects[i]->LightItalic.loadFromFile(fontLib[5]);
			if (loadObjects[i]) cout << "Success!" << "\n";
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
	if (loadObjects.size() != loadPaths.size())
	{
		cout << "[" << this << "]" << " Error reading path list: mismatching entries. Textures not loaded." << "\n";
		return false;
	}

	int i = 0;
	for (std::string path : loadPaths)
	{
		if (!path.empty())
		{
			std::cout << "[" << this << "]" << " Attempting to Load " << path << "... ";
			if (loadObjects[i]->loadFromFile(path)) cout << "Success!" << "\n";
		}
		else std::cout << "[" << this << "]" << " Failed to Load " << path << "\n";

		i++;
	}
	return true;
}

