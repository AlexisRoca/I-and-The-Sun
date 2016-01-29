#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "INDrawable.h"
#include "INUpdatable.h"
#include "Ray.h"

#include "TextureLoader.h"
#include "Building.h"
#include "Floor.h"
#include "Character.h"
//#include "Teleporter.h"

class World : public INDrawable, public INUpdatable
{
	private:
		TextureLoader * m_textures;
		Building  * m_building;
		Character * m_character;
		sf::Music * m_musicGame;

	public:
		World(TextureLoader * textures);
		virtual ~World();

		Character * getCharacter() const;
		Building * getBuilding() const;

		virtual void draw(sf::RenderWindow *window);
		virtual void update(sf::Clock const & clk);
};

