#include "Floor.h"


Floor::Floor(TextureLoader const * textureLoaders) :
	m_background(),
	m_floorMap(),

    m_rooms(),
 //   m_teleporters(),
	
	m_textureBuilding(textureLoaders->getFloorTexture()),
	m_currentLife(0)
{}

Floor::~Floor()
{
    for(auto it = m_rooms.begin(); it != m_rooms.end(); ++it)
        delete it->second;

    //for(auto it = m_teleporters.begin(); it != m_teleporters.end(); ++it)
    //    delete *it;
}

void Floor::addLineToBackground(std::vector<unsigned char> line)
{
    m_background.push_back(line);
}

void Floor::addLineToRoomsMap(std::vector<unsigned char> line)
{
	m_floorMap.push_back(line);
}


void Floor::addRoom(unsigned char roomId)
{
	m_rooms.insert(std::pair<unsigned char, Room *>(roomId, new Room(roomId,100)));

	m_currentLife += m_rooms[roomId]->getLife();
	m_maxLife += m_rooms[roomId]->getLife();
}

Room * Floor::getRoom(unsigned char roomId)
{
	return m_rooms[roomId];
}

std::map<unsigned char, Room *> * Floor::getRooms()
{
	return & m_rooms;
}

//void Floor::addTeleporter(Teleporter * teleporter)
//{
//    m_teleporters.push_back(teleporter);
//}

//std::vector<Teleporter *> Floor::getTeleporter()
//{
//	return m_teleporters;
//}

std::vector<std::vector<unsigned char> > * Floor::getFloorMap()
{
	return &m_floorMap;
}

void Floor::setLife(double lostLife)
{
	m_currentLife -= lostLife;
}

double Floor::getLife() const
{
	return m_currentLife;
}

double Floor::getMaxLife() const
{
	return m_maxLife;
}

double Floor::lifeStay() const
{
	return m_maxLife - m_currentLife;
}

void Floor::update(sf::Clock const & clk)
{
	for (auto it = m_rooms.begin(); it != m_rooms.end(); ++it)
	{
		(*it).second->update(clk);
		m_currentLife -= ((*it).second->getMaxLife() - (*it).second->getLife());
	}
}

void Floor::draw(sf::RenderWindow * window)
{
    //background
	for (unsigned int i = 0; i < m_background.size(); ++i)
	{
		for (unsigned int j = 0; j < m_background[i].size(); ++j)
		{
			int offsetX(0), offsetY(0);

			if (m_background[i][j] == '0')
			{
				sf::Vector2u ofst = offset(i, j);
				offsetX = ofst.x;
				offsetY = ofst.y;
			}
			else if (m_background[i][j] == '1')
			{
				offsetX = 0;
				offsetY = 4;
			}
		
			sf::Sprite sprite;
			sprite.setTexture(*m_textureBuilding);
			sprite.setTextureRect(sf::IntRect(32 * offsetX, 32 * offsetY, 32, 32));
			sprite.setPosition(j * 32, i * 32);

			window->draw(sprite);
		}
	}

	////teleporter
 //   for(auto it = m_teleporters.cbegin(); it != m_teleporters.cend(); ++it)
 //       (*it)->draw(window);

    //objects
    for(auto it = m_rooms.cbegin(); it != m_rooms.cend(); ++it)
        (*it).second->draw(window);
}

bool Floor::collision(sf::Sprite * sprite)
{
	

}

sf::Vector2u Floor::offset(unsigned int i, unsigned int j) const
{
    unsigned char v = m_background[i][j];
    unsigned int offsetX(0), offsetY(0);

    if(i == 0 || i == m_background.size() - 1 || j == 0 || j == m_background[i].size() - 1)
    {
        offsetX = 1;
        offsetY = 0;
    }

    else
    {
        unsigned char N = m_background[i-1][j];
        unsigned char S = m_background[i+1][j];
        unsigned char W = m_background[i][j-1];
        unsigned char E = m_background[i][j+1];

        if(i-1 == 0)
            N = 0;
        if(i+1 == m_background.size() - 1)
            S = 0;
        if(j-1 == 0)
            W = 0;
        if(j+1 == m_background[i].size() - 1)
            E = 0;

        if(N == v && W == v && S == v && E == v)
        {
            offsetX = 0;
            offsetY = 0;
        }
        else if(W == v && N == v && E == v)
        {
            offsetX = 0;
            offsetY = 1;
        }
        else if(N == v && E == v && S == v)
        {
            offsetX = 1;
            offsetY = 1;
        }
        else if(W == v && S == v && E == v)
        {
            offsetX = 2;
            offsetY = 1;
        }
        else if(N == v && W == v && S && v)
        {
            offsetX = 3;
            offsetY = 1;
        }
        else if(W == v && N == v)
        {
            offsetX = 0;
            offsetY = 2;
        }
        else if(N == v && E == v)
        {
            offsetX = 1;
            offsetY = 2;
        }
        else if(E == v && S == v)
        {
            offsetX = 2;
            offsetY = 2;
        }
        else if(S == v && W == v)
        {
            offsetX = 3;
            offsetY = 2;
        }
        else if(W == v && E == v)
        {
            offsetX = 2;
            offsetY = 0;
        }
        else if(N == v && S == v)
        {
            offsetX = 3;
            offsetY = 0;
        }
        else if(S == v)
        {
            offsetX = 0;
            offsetY = 3;
        }
        else if(N == v)
        {
            offsetX = 1;
            offsetY = 3;
        }
        else if(W == v)
        {
            offsetX = 2;
            offsetY = 3;
        }
        else if(E == v)
        {
            offsetX = 3;
            offsetY = 3;
        }
        else
        {
            offsetX = 1;
            offsetY = 0;
        }
    }

    return sf::Vector2u(offsetX, offsetY);
}
