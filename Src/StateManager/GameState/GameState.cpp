#include <utility>

#include "GameState.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
#include "../../../Tools/ScopedTimer/ScopedTimer.hpp"
#include "../../../Tools/Logger/Logger.hpp"
#include "../../Entity/Player/Player.hpp"
#include "../../Entity/Particle/Particle.hpp"
#include "../../Entity/Tile/Tile.hpp"

GameState::GameState()
{
	camera.setSize(sf::Vector2f(Scene::window.getSize()));
	camera.zoom(0.5f);
	level = 1;

	loadLevel();
}

GameState::~GameState() = default;

void GameState::run()
{
	sf::Clock deltaClock;
	float deltaTime;

	Logger::error("get out of here!");

	while (Scene::window.isOpen())
	{
		const sf::Event& e{ eventHandler() };

		deltaTime = deltaClock.restart().asSeconds();
		update(deltaTime, e);

		Scene::window.setView(camera);
		Scene::window.clear(sf::Color(82, 146, 219));

		draw();
		Scene::window.display();
	}
}

void GameState::update(const float deltaTime, const sf::Event& e)
{
	Tile::update(deltaTime);
	Particle::update(deltaTime);
	Player::update(deltaTime, e);

	camera.setCenter
	(
		std::lerp(camera.getCenter().x, Player::player.body.getPosition().x, 5 * deltaTime),
		std::lerp(camera.getCenter().y, Player::player.body.getPosition().y, 5 * deltaTime)
	);
}

void GameState::draw()
{
	Tile::draw();
	Particle::draw();
	Player::draw();
}

void GameState::loadLevel()
{
	const sf::Image& level{ ResourceManager::imageMap[ImageId::level1] };

	for (unsigned int y{ 0 }; y < level.getSize().y; y++)
	{
		for (unsigned int x{ 0 }; x < level.getSize().x; x++)
		{
			const sf::Color& color{ level.getPixel(x, y) };

			if (color == sf::Color(0, 0, 0))
			{
				Tile::tiles.emplace_back(sf::Vector2i(x, y));
			}
			else if (color == sf::Color(255, 0, 0))
			{
				Player player(sf::Vector2i(x, y));
				Player::player = player;
				camera.setCenter(Player::player.body.getPosition());
			}
		}
	}
}