#include <algorithm>
#include <utility>

#include "Particle.hpp"
#include "../../Scene/Scene.hpp"
#include "../../../Tools/RangeRandom/RangeRandom.hpp"
#include "../../../Tools/Logger/Logger.hpp"

std::vector<Particle> Particle::particles;
sf::VertexArray Particle::vertexArray;

Particle::Particle(const sf::Vector2i& indices)
	: Entity{ indices, sf::Vector2f{ 4.f, 4.f } },
	angle{ rangeRandom(-60.f, 60.f) },
	color{ 0, 0, 0, 255 },
	deathColor{ 255, 0, 0, 0 },
	maxLifetime{ sf::seconds(1.5f) }
{
}

Particle::~Particle() = default;

void Particle::update(const float deltaTime)
{
	for (Particle& particle : particles)
	{
		particle.color.r = static_cast<int>(std::lerp(static_cast<float>(particle.color.r), static_cast<float>(particle.deathColor.r),  particle.timer.getElapsedTime().asSeconds() / particle.maxLifetime.asSeconds()));
		particle.color.g = static_cast<int>(std::lerp(static_cast<float>(particle.color.g), static_cast<float>(particle.deathColor.g), particle.timer.getElapsedTime().asSeconds() / particle.maxLifetime.asSeconds()));
		particle.color.b = static_cast<int>(std::lerp(static_cast<float>(particle.color.b), static_cast<float>(particle.deathColor.b), particle.timer.getElapsedTime().asSeconds() / particle.maxLifetime.asSeconds()));
		particle.color.a = static_cast<int>(std::lerp(static_cast<float>(particle.color.a), static_cast<float>(particle.deathColor.a), particle.timer.getElapsedTime().asSeconds() / particle.maxLifetime.asSeconds()));
		//particle.color.a = static_cast<int>(particle.spawnColor.a * (particle.lifetime.asSeconds() / particle.maxLifetime.asSeconds()));
		particle.body.rotate(particle.angle * deltaTime);
		particle.body.setSize(sf::Vector2f{ particle.body.getSize().x + 0.5f, particle.body.getSize().y + 0.5f });
		particle.body.setOrigin(particle.body.getSize().x / 2.f, particle.body.getSize().x / 2.f);
	}

	std::erase_if(particles,
		[](const Particle& particle) -> bool
		{
			return particle.timer.getElapsedTime().asSeconds() >= particle.maxLifetime.asSeconds();
		});
}

void Particle::draw()
{
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(particles.size() * 4);

	int vertexPtr{};

	for (Particle& particle : particles)
	{
		particle.transform = particle.body.getTransform();
		sf::Vertex* quad{ &vertexArray[vertexPtr] };

		for (int i{}; i < 4; ++i)
		{
			particle.mesh[i] = particle.body.getPoint(i);
			quad[i] = particle.transform.transformPoint(particle.mesh[i]);
			quad[i].color = particle.color;
		}

		vertexPtr += 4;
	}

	Scene::window.draw(vertexArray);
}
