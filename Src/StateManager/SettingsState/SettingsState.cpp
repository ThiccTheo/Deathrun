#include "SettingsState.hpp"
#include "../../Scene/Scene.hpp"

SettingsState::SettingsState()
{
	camera.setSize(sf::Vector2f(Scene::window.getSize()));
	isPopped = false;
}

SettingsState::~SettingsState()
{
}

void SettingsState::run()
{
	sf::Clock deltaClock;
	float deltaTime;

	while (Scene::window.isOpen() && !isPopped)
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

void SettingsState::update(const float deltaTime, const sf::Event& e)
{
	ImGui::SFML::ProcessEvent(e);

	switch (e.type)
	{
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Escape)
		{
			isPopped = removeState();
		}
		break;
	}

	ImGui::SFML::Update(Scene::window, sf::seconds(deltaTime));
}

void SettingsState::draw()
{
	ImGui::SetNextWindowSize(ImVec2(300.f, 350.f));
	ImGui::SetNextWindowPos(ImVec2(Scene::window.getSize().x / 2.f - 150.f, Scene::window.getSize().y / 2.f - 175.f));
	ImGui::Begin("Settings");
	if (ImGui::Checkbox("V-Sync", &Scene::isVsync))
	{
		Scene::window.setVerticalSyncEnabled(Scene::isVsync);
	}
	if (ImGui::Button("Back", ImVec2(300.f, 100.f)))
	{
		isPopped = removeState();
	}
	ImGui::End();
	ImGui::SFML::Render(Scene::window);
}
