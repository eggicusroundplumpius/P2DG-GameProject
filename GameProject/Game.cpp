#include <assert.h>
#include <string>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits.h>

#include "Game.h"

using namespace sf;
using namespace std;

/// ///////////////////////////////////////////////////////////
///
/// Initialisation function - performs many one-time only
/// actions, intended to prepare the game to run.
/// 
/// ///////////////////////////////////////////////////////////
void Game::Init(Resource &resource)
{
	background.Init(Type::Static_Environment, resource.texBackground);
	ground.Init(Type::Static_Environment, resource.texGround);
	player.Init(Type::Player, resource.texShip);
	
}

/// ///////////////////////////////////////////////////////////
///
/// Primary render function: contains cases for main screens 
/// available, handles drawing-related functions.
/// 
/// \param window - Main window object to draw to.
/// \param elapsed - elapsed time in seconds since last update.
/// 
/// ///////////////////////////////////////////////////////////
void Game::Update(RenderWindow& window, float elapsed)
{

}

/// ///////////////////////////////////////////////////////////
///
/// Primary render function: contains cases for main screens 
/// available, handles drawing-related functions.
/// 
/// \param window - Main window object to draw to.
/// \param elapsed - elapsed time in seconds since last update.
/// 
/// ///////////////////////////////////////////////////////////
void Game::Render(RenderWindow& window, float elapsed)
{

}