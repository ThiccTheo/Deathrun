#include "StateManager.hpp"
#include "../Scene/Scene.hpp"
#include "GameState/GameState.hpp"
#include "MenuState/MenuState.hpp"
#include "SettingsState/SettingsState.hpp"

std::stack<std::unique_ptr<StateManager>> StateManager::states;

StateManager::StateManager()
	: isPopped{ false }
{
	camera.setSize(sf::Vector2f{ Scene::window.getSize() });
}

StateManager::~StateManager() = default;

void StateManager::run() {}

void StateManager::update(const float deltaTime, const sf::Event& e) {}

void StateManager::draw() {}

const sf::Event StateManager::eventHandler()
{
	sf::Event e;
	while (Scene::window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			Scene::window.close();
			break;
		case sf::Event::LostFocus:
			Scene::isFocused = false;
			break;
		case sf::Event::GainedFocus:
			Scene::isFocused = true;
			break;
		}

		return e;
	}

	return {};
}

void StateManager::addState(const StateType stateType)
{
	switch (stateType)
	{
		case StateType::gameState:
			states.emplace(std::make_unique<GameState>());
			checkState();
			break;	
		case StateType::menuState:
			states.emplace(std::make_unique<MenuState>());
			checkState();
			break;
		case StateType::settingsState:
			states.emplace(std::make_unique<SettingsState>());
			checkState();
			break;
	}
}

bool StateManager::removeState()
{
	if (!states.empty())
	{
		states.pop();
		return true;
	}
	else
	{
		return false;
	}
}

void StateManager::checkState()
{
	if (!states.empty())
	{
		states.top()->run();
	}
}
