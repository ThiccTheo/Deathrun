#include <iostream>

#include "ResourceManager/ResourceManager.hpp"
#include "StateManager/StateManager.hpp"
#include "Scene/Scene.hpp"
#include "Entity/Entity.hpp"

int main()
{
	if (ResourceManager::load())
	{
		Scene::init();
		Entity::init();
		StateManager::addState(StateType::menuState);
		ImGui::SFML::Shutdown(Scene::window);
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}