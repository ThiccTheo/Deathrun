#pragma once

#include <iostream>

#include "CommonSFML.hpp"
#include "CommonImGui.hpp"
#include "../Entity.hpp"

class Player : public Entity
{
public:
	static Player player;

	Player();
	Player(const sf::Vector2i& indices);
	~Player() override;
	static void update(const float deltaTime, const sf::Event& e);
	static void draw();
private:
	static sf::VertexArray vertexArray;
	sf::Vector2f velocity;
	static const float friction;
	static const float gravity;
	bool isGrounded;
};

