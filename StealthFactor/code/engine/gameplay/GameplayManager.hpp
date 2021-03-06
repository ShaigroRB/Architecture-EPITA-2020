#pragma once

#include <memory>
#include <set>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/EntityContext.hpp>
#include <engine/gameplay/EntityListener.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			class Player;
		}

		class Manager : public EntityListener
		{
		public:
			Manager(graphics::Manager &graphicsManager, input::Manager &inputManager, physics::Manager &physicsManager);

			void setUp();
			void tearDown();

			void update();

			void loadMap(const std::string &mapName);

			// EntityListener
			void gameOver() override;
			void loadNextMap() override;
			const components::Player &getPlayer() const override;

			static const float CELL_SIZE;

		private:
			using EntityPtr = std::unique_ptr<Entity>;

			EntityContext _context;

			std::set<EntityPtr> _entities;
			components::Player *_playerComponent{};

			// Map
			std::string _currentMapName;
			std::string _nextMapName;
			int _rows{ 0 };
			int _columns{ 0 };

			bool _preventMapCompletion{ false };
			bool _nextMapRequested{ false };

			void removeEntities();
		};
	}
}
