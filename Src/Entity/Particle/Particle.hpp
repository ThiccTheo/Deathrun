#pragma once

#include <iostream>
#include <vector>

#include "CommonSFML.hpp"
#include "../Entity.hpp"

class Particle : public Entity
{
public:
	static std::vector<Particle> particles;

	Particle(const sf::Vector2i& indices);
	~Particle() override;
	static void update(const float deltaTime);
	static void draw();
private:
	static sf::VertexArray vertexArray;
	sf::Clock timer;
	sf::Color color;
	sf::Color deathColor;
	float angle;
	sf::Time maxLifetime;
};

