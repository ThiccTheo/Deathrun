#include "MenuState.hpp"
#include "../../Scene/Scene.hpp"

MenuState::MenuState()
{
	camera.setSize(sf::Vector2f(Scene::window.getSize()));
}

MenuState::~MenuState() = default;

void MenuState::run()
{
	sf::Clock deltaClock;
	float deltaTime;

	while (Scene::window.isOpen())
	{
		const sf::Event& e{ eventHandler() };

		deltaTime = deltaClock.restart().asSeconds();
		update(deltaTime, e);

		Scene::window.setView(camera);
		Scene::window.clear();

		draw();
		Scene::window.display();
	}
}

void MenuState::update(const float deltaTime, const sf::Event& e)
{
	ImGui::SFML::ProcessEvent(e);

	switch (e.type)
	{
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Escape)
		{
			Scene::window.close();
		}
		break;
	}

	ImGui::SFML::Update(Scene::window, sf::seconds(deltaTime));
}

void MenuState::draw()
{
	ImGui::SetNextWindowSize(ImVec2(300.f, 350.f));
	ImGui::SetNextWindowPos(ImVec2(Scene::window.getSize().x / 2.f - 150.f, Scene::window.getSize().y / 2.f - 175.f));
	ImGui::Begin("Main Menu");
	if (ImGui::Button("Play Game", ImVec2(300.f, 100.f)))
	{
		addState(StateType::gameState);
	}
	if (ImGui::Button("Settings", ImVec2(300.f, 100.f)))
	{

	}
	if (ImGui::Button("Quit", ImVec2(300.f, 100.f)))
	{
		Scene::window.close();
	}
	ImGui::End();
	ImGui::SFML::Render(Scene::window);
}
