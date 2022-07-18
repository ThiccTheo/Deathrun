#include "Scene.hpp"
#include "../ResourceManager/ResourceManager.hpp"

sf::RenderWindow Scene::window;
sf::Cursor Scene::cursor;
bool Scene::isFocused;
bool Scene::isVsync;

void Scene::init()
{
	const auto& [width, height] {determineResolution()};
	window.create(sf::VideoMode(width, height), "Deathrun", sf::Style::Default);
	isFocused = true;
	isVsync = true;
	window.setVerticalSyncEnabled(isVsync);
	window.setKeyRepeatEnabled(false);

	cursor.loadFromPixels(ResourceManager::imageMap[ImageId::cursor].getPixelsPtr(), sf::Vector2u(10, 10), sf::Vector2u(0, 0));
	window.setMouseCursor(cursor);

	ImGui::SFML::Init(window);
}

const sf::Vector2u Scene::determineResolution()
{
	const sf::Vector2u desktopResolution{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height };

	if (desktopResolution.x % 16 == 0 && desktopResolution.y % 9 == 0) //16:9
	{
		return sf::Vector2u(1280, 720);
	}
	else if (desktopResolution.x % 16 == 0 && desktopResolution.y % 10 == 0) //16:10
	{
		return sf::Vector2u(1280, 800);
	}
	else if (desktopResolution.x % 4 == 0 && desktopResolution.y % 3 == 0) //4:3
	{
		return sf::Vector2u(1280, 960);
	}
	else if (desktopResolution.x % 5 == 0 && desktopResolution.y % 4 == 0) //5:4
	{
		return sf::Vector2u(1280, 1024);
	}
	else
	{
		return {};
	}
}
