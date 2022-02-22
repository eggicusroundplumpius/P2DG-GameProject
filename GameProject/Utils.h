#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

/// ///////////////////////////////////////////////////////////
///
/// Simple datatype for holding x and y dimensions
/// 
/// ///////////////////////////////////////////////////////////
struct Dim2D
{
	struct integer { int x, y; };	//Integer Type
	struct real { float x, y; };	//Real (float) Type
};

/// ///////////////////////////////////////////////////////////
///
/// Stores SFML Fonts with their variations (regular, bold,
/// italic, etc.)
/// 
/// ///////////////////////////////////////////////////////////
struct FontType
{
	sf::Font Regular;
	sf::Font Bold;
	sf::Font Italic;
	sf::Font BoldItalic;
	sf::Font Light;
	sf::Font LightItalic;
};

/// ///////////////////////////////////////////////////////////
///
/// Holds the utility functions, such as Loading and filesystem
/// interaction. It holds no data, only functions.
/// 
/// ///////////////////////////////////////////////////////////
struct UtilityBelt
{
	bool Load(std::vector<FontType*> const& loadObjects, vector<vector<string>> const& loadPaths);
	bool Load(std::vector<sf::Texture*> const& loadObjects, vector<string> const& loadPaths);
};

void draw(std::vector<sf::Drawable*>& uiDrawables, std::vector<sf::Drawable*>& gameDrawables, sf::RenderWindow& window);
