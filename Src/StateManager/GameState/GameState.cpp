#include "GameState.hpp"
#include "../../Scene/Scene.hpp"
#include "../../Entity/Player/Player.hpp"
#include "../../Entity/Particle/Particle.hpp"
#include "../../Entity/Tile/Tile.hpp"

GameState::GameState()
{
	camera.setSize(sf::Vector2f(Scene::window.getSize()));
	camera.zoom(0.5f);

	Player player(sf::Vector2i(10, 10));
	Player::player = player;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			Tile::tiles.emplace_back(sf::Vector2i(j, i));
		}
	}
}

GameState::~GameState() = default;

void GameState::run()
{
	sf::Clock deltaClock;
	float deltaTime;

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

	camera.setCenter(Player::player.body.getPosition());
}

void GameState::draw()
{
	Tile::draw();
	Particle::draw();
	Player::draw();
}
