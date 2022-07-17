#include "GameState.hpp"
#include "../../Scene/Scene.hpp"
#include "../../Entity/Player/Player.hpp"
#include "../../Entity/Particle/Particle.hpp"

GameState::GameState()
{
	camera.setSize(sf::Vector2f(Scene::window.getSize()));
	camera.zoom(0.5f);

	Player player(sf::Vector2i(10, 10));
	Player::player = player;
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
	Particle::update(deltaTime);
	Player::update(deltaTime, e);

	camera.setCenter(Player::player.body.getPosition());
}

void GameState::draw()
{
	Particle::draw();
	Player::draw();
}
