#pragma once
#include <vector>
#include <typeinfo>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

namespace Defaults
{
	const sf::VideoMode windowResolution = { 1280, 720 };	// Default Window Resolution
	const Uint32 windowMode = sf::Style::Titlebar;			// Default Window Style
	const std::string windowName = "Game Project";			// Default Window Name
	const unsigned fpsLimit = 60u;							// Default Frame Rate Limit

	const unsigned fontSize = 4u;				// Default Font Size
	const Vector2f iconSize = { 32.f, 32.f };	// Default UI Icon Size

	const int playerSpeed = 200;		// Default Player Movement Speed
	const float thrustPercent = 0.1f;	// Default Thrust Percentage
	const int enemySpeed = 20;			// Default Enemy Movement Speed
	const int gravityFactor = 10;		// Default Gravity Factor
	const int progressionFactor = 3;	// Default speed at which the level gets faster (harder)

	const bool physicsVisibleBoundaries = false;		// Whether to draw physics boundaries
}

enum class gameMode { menuRoot, menuOptions, menuAbout, gamePlay, gamePause };		// Available Screens and Menu Configurations
enum class windowMode { windowed, borderless, fullscreen };							// Available Window Display Modes

/// ///////////////////////////////////////////////////////////
///
/// [DEPRECATED] Simple datatype for holding x and y dimensions
/// 
/// ///////////////////////////////////////////////////////////
struct Dim2D
{
	struct integer { int x, y; };	// Integer Type
	struct real { float x, y; };	// Real (float) Type
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

struct Resource
{
	// Texture Objects

	sf::Texture texBackground;
	sf::Texture texGround;
	sf::Texture texPlayer;
	sf::Texture texEnemy;
	sf::Texture iconBack;
	sf::Texture iconPause;
	sf::Texture iconMusic;
	sf::Texture iconMute;
	sf::Texture iconExit;

	// Font Objects

	FontType DSEG14Classic;
	FontType CondenBitmap;

	// Loading Paths

	const std::vector <sf::Texture*> loadTextures{ &texBackground, &texGround, &texPlayer, &texEnemy,
													&iconBack, &iconPause, &iconMusic, &iconMute, &iconExit };
	const vector<string> loadTexturePaths =
	{
		"data/tex/background.png",
		"data/tex/ground.png",
		"data/tex/player.png",
		"data/tex/enemy.png",
		"data/tex/icon/back.png",
		"data/tex/icon/pause.png",
		"data/tex/icon/music.png",
		"data/tex/icon/mute.png",
		"data/tex/icon/exit.png"
	};
	const std::vector <FontType*> loadFonts{ &DSEG14Classic, &CondenBitmap };
	const vector<vector<string>> loadFontPaths = {
		{ // DSEG14 Classic
			"data/fonts/DSEG14Classic-Regular.ttf",
			"data/fonts/DSEG14Classic-Italic.ttf",
			"data/fonts/DSEG14Classic-Bold.ttf",
			"data/fonts/DSEG14Classic-BoldItalic.ttf",
			"data/fonts/DSEG14Classic-Light.ttf",
			"data/fonts/DSEG14Classic-LightItalic.ttf"
		},
		{ // CondenBitmap
			"data/fonts/CondenBitmap.otf",
			"",
			"",
			"",
			"",
			""
		}
	};
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

	bool modeChanged;
};

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


/// ///////////////////////////////////////////////////////////
///
/// Calculates decay on a set of moving coordinates over time.
/// 
/// \param inValue - value to be processed
/// \param percent - percent to decay by over time
/// \param interval - time interval to decay over
/// \param elapsed - time since last update in seconds
/// 
/// ///////////////////////////////////////////////////////////
Vector2f Decay(Vector2f const& inValue, float percent, float interval, float elapsed);


/// ///////////////////////////////////////////////////////////
///
/// Calculates the distance between two sets of coordinates and
/// returns a boolean indicating whether that distance is below
/// the minimum distance.
/// 
/// \param position1 - position of one of the coordinates
/// \param position2 - position of the other coordinates
/// \param minimumDistance - the minimum distance to return
/// false
/// 
/// ///////////////////////////////////////////////////////////
bool distanceCheck(Vector2f const& position1, Vector2f const& position2, float minimumDistance);