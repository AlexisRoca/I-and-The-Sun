#include "Door.h"

Door::Door(unsigned int x, unsigned int y, std::pair<unsigned char, unsigned char> adjacentRooms, sf::Texture const* texture):
	m_x(x),
	m_y(y),
	m_adjacentRooms(adjacentRooms),
	m_texture(texture)
{}

Door::~Door()
{}

std::pair<unsigned char, unsigned char> * Door::getAdjacentRooms()
{
	return &m_adjacentRooms;
}

void Door::collision(Ray * ray)
{
	
}

void Door::draw(sf::RenderWindow *window)
{
	sf::Sprite sprite;
	sprite.setTexture(*m_texture);
	sprite.setTextureRect(sf::IntRect(2*32, 1*32, 32, 32));

	sprite.setPosition(m_x * 32, m_y * 32);
	window->draw(sprite);
}
