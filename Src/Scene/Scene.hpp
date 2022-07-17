#pragma once

#include <iostream>

#include "CommonSFML.hpp"
#include "CommonImGui.hpp"

class Scene
{
public:
	static sf::RenderWindow window;
	static sf::Cursor cursor;
	static bool isFocused;

	static void init();
private:
	static const sf::Vector2u determineResolution();
};

