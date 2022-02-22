#pragma once
#include "Utils.h"
#include "Game.h"

struct UI
{
	void Init();
	void Update(RenderWindow& window, const Game::Mode& mode);
	void Render(RenderWindow& window);

	Mouse mouse;
	Keyboard keyboard;

	bool modeChanged;

	struct Element
	{
		UI* pointerUI = nullptr;
		sf::RectangleShape Frame;
		Dim2D::integer dimensions;

		bool visible, enabled;

		void Init(UI* pointerUI_In);
	};
	struct Interactable
	{
		bool selected;

		void* functionPointer = nullptr;

		void Hover();
		void Click(sf::Mouse::Button const mouseButton);
		void Hold(sf::Mouse::Button const mouseButton);
		void Drag(sf::Mouse::Button const mouseButton);
	};

	struct Button : public Element, Interactable
	{
		sf::Sprite customFrame;
		sf::Text text;
	};
	struct TextBox : public Element
	{
		sf::Text text;
	};
	struct PictureBox : public Element
	{
		sf::Sprite sprite;
	};

	std::vector <Drawable*> Drawables;
	std::vector <Element> Elements;
};