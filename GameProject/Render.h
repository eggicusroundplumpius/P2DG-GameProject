#pragma once
#include "Utils.h"

class Render
{
public:
	void Init(sf::RenderWindow& window);
	void Update();

	sf::RenderWindow& drawWindow;

private:
	/// ///////////////////////////////////////////////////////////
	///
	/// Takes vectors from major function groups (game and ui),
	/// collates them and draws them with UI being drawn last
	/// (on top).
	/// 
	/// \param uiDrawables - vector of UI element drawable
	/// members
	/// \param gameDrawables - vector of game object drawable
	/// members
	/// \param window - window to draw to
	/// 
	/// ///////////////////////////////////////////////////////////
	void draw(std::vector<sf::Drawable*>& uiDrawables, std::vector<sf::Drawable*>& gameDrawables, sf::RenderWindow& window);
};