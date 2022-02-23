#pragma once
#include "Utils.h"
#include "Game.h"

struct UI
{
	void Init(Resource* resource);
	void Update(RenderWindow& window, Event event, const Game::Mode& mode);
	void Render(RenderWindow& window);

	void changeScreen(Game::Mode const& mode);

	Mouse mouse;

	bool modeChanged;
	Vector2f percentBounds;
	Resource* pointerResource;

	enum class windowMode {windowed, borderless, fullscreen};
	enum class elementType {button, textbox, picturebox};

	struct Element
	{
		UI* pointerUI = nullptr;
		sf::RectangleShape Frame;
		Dim2D::integer dimensions;
		elementType type;

		Drawable* pointerDrawMember;

		bool visible, enabled;

		void Init(UI* pointerUI_In);
	};
	struct Interactable
	{
		bool selected;
		sf::Sprite customFrame;
		void* functionPointer = nullptr;

		void Update();
		void Hover();
		void Click(sf::Mouse::Button const& mouseButton);
		void Hold(sf::Mouse::Button const& mouseButton);
		void Drag(sf::Mouse::Button const& mouseButton);
	};

	struct Button : public Element, Interactable
	{
		sf::Text text;
		elementType type = elementType::button;
		Drawable* pointerDrawMember = &this->text;
	};
	struct TextBox : public Element
	{
		sf::Text text;
		elementType type = elementType::textbox;
		Drawable* pointerDrawMember = &this->text;
	};
	struct PictureBox : public Element
	{
		sf::Sprite sprite;
		elementType type = elementType::picturebox;
		Drawable* pointerDrawMember = &this->sprite;
	};

	TextBox title;
	Button play;
	Button options;
	Button mute;
	Button exit;

	Button back;
	Button music;
	Button fullscreen;

	TextBox health;
	TextBox score;
	Button pause;

	std::vector <Drawable*> Drawables;
	std::vector <Element*> Elements;
};