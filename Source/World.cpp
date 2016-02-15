#include "World.h"

World::World(TextureLoader * textures):
	m_textures(textures),
	m_building(new Building(m_textures, 1, 1)),
	m_character(new Character(m_textures)),
	m_musicGame(new sf::Music())
{
	m_building->loadBuilding("Levels/0.lvl");

	if(m_musicGame->openFromFile("Ressources/Music/Game.wav"))
	{
		m_musicGame->setLoop(true);
		m_musicGame->play();
	}
}

World::~World()
{
	delete m_building;
	delete m_character;
	delete m_musicGame;
}

Character * World::getCharacter() const
{
	return m_character;
}

Building * World::getBuilding() const
{
	return m_building;
}

void World::draw(sf::RenderWindow *window)
{
	m_building->draw(window);
	m_character->draw(window);
}


void World::update(sf::Clock const & clk)
{
	m_building->update(clk);
	m_character->update(clk);

	sf::Vector2f characterPositon = m_character->getPosition();
	int x = characterPositon.y / 36;
	int y = characterPositon.x / 36;
	
	if(m_building->getCurrentFloor()->getFloorMap()[x][y] != 'P' && m_building->getCurrentFloor()->getFloorMap()[x][y] != '0')
		m_character->setCurrentRoom(m_building->getCurrentFloor()->getFloorMap()[x][y]);
}
