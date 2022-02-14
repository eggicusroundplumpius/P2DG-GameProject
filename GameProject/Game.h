#pragma once

#include "SFML/Graphics.hpp"
#include "Utils.h"

namespace Textures
{
	sf::Texture backgroundTex;
	sf::Texture shipTex;
}

namespace GameControl
{
	Dim2Di defaultResolution = { 1280, 720 };
	unsigned defaultFontpt = 50u;

}

struct Game
{
	void Init();
	void Update(RenderWindow& window, float elapsed);
	void Render(RenderWindow& window, float elapsed);
};

struct Information
{

};