#include "Player.hpp"
#include "../../Scene/Scene.hpp"
#include "../../ResourceManager/ResourceManager.hpp"

Player Player::player;
sf::VertexArray Player::vertexArray;

Player::Player() = default;

Player::Player(const sf::Vector2i& indices)
	: Entity{ indices, sf::Vector2f(16.f, 16.f) } {};

Player::~Player() = default;

void Player::update(const float deltaTime, const sf::Event& e)
{
	if (Scene::isFocused && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.body.setScale(-1.f, 1.f);
	}
	if (Scene::isFocused && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.body.setScale(1.f, 1.f);
	}
}

void Player::draw()
{
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(4);

	int vertexPtr{ 0 };

	player.transform = player.body.getTransform();
	sf::Vertex* quad{ &vertexArray[vertexPtr] };

	for (int i{ 0 }; i < 4; i++)
	{
		player.mesh[i] = player.body.getPoint(i);
		quad[i] = player.transform.transformPoint(player.mesh[i]);
		quad[i].texCoords = sf::Vector2f(player.mesh[i].x, player.mesh[i].y);
	}

	vertexPtr += 4;

	Scene::window.draw(vertexArray, &ResourceManager::textureMap[TextureId::player]);
}
