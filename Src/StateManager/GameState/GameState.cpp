#include <utility>

#include "GameState.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"
#include "../../../Tools/ScopedTimer/ScopedTimer.hpp"
#include "../../../Tools/Logger/Logger.hpp"
#include "../../Entity/Entity.hpp"
#include "../../Entity/Player/Player.hpp"
#include "../../Entity/Particle/Particle.hpp"
#include "../../Entity/Tile/Tile.hpp"

GameState::GameState()
	: StateManager{},
	level{ 1 },
	levelSize{}
{
	camera.zoom(0.5f);
}

GameState::~GameState() = default;

void GameState::run()
{
	loadLevel();

	sf::Clock deltaClock;
	float deltaTime{};

	while (Scene::window.isOpen() && !isPopped)
	{
		const sf::Event& e{ eventHandler() };

		deltaTime = deltaClock.restart().asSeconds();
		update(deltaTime, e);

		Scene::window.setView(camera);
		Scene::window.clear(sf::Color{ 135, 206, 235 });

		draw();
		Scene::window.display();
	}
}

void GameState::update(const float deltaTime, const sf::Event& e)
{
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Escape)
		{
			addState(StateType::settingsState);
		}
		break;
	}

	Tile::update(deltaTime);
	Particle::update(deltaTime);
	Player::update(deltaTime, e);

	const auto& [playerX, playerY] { Player::player.body.getPosition() };
	const auto& [cameraX, cameraY] { camera.getCenter() };

	camera.setCenter
	(
		std::clamp(std::lerp(cameraX, playerX, 10.f * deltaTime), camera.getSize().x / 2.f - Entity::sizeMap[EntityType::tile].x / 2.f, levelSize.x * Entity::sizeMap[EntityType::tile].x - camera.getSize().x / 2.f - Entity::sizeMap[EntityType::tile].x / 2.f), //test values
		std::clamp(std::lerp(cameraY, playerY, 10.f * deltaTime), 0.f, levelSize.y * Entity::sizeMap[EntityType::tile].y - camera.getSize().y / 2.f - Entity::sizeMap[EntityType::tile].y / 2.f)  //test values
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
	const sf::Image& level{ ResourceManager::imageMap[ImageId::level] };
	levelSize = level.getSize();

	for (unsigned int y{}; y < levelSize.y; ++y)
	{
		for (unsigned int x{}; x < levelSize.x; ++x)
		{
			const sf::Color& color{ level.getPixel(x, y) };

			if (color == sf::Color{ 0, 0, 0 })
			{
				Tile::tiles.emplace_back(sf::Vector2i{ static_cast<int>(x), static_cast<int>(y) }, TileType::grass);
			}
			else if (color == sf::Color{ 255, 0, 0 })
			{
				Player player{ sf::Vector2i{ static_cast<int>(x), static_cast<int>(y) } };
				Player::player = player;
				camera.setCenter(Player::player.body.getPosition());
			}
		}
	}
}