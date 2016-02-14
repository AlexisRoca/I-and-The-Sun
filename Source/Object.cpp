#include "..\Include\Object.h"

Object::Object(unsigned int width, unsigned int height, unsigned int x, unsigned int y, sf::Texture * objectTexture, unsigned int offsetX, unsigned int offsetY):
	m_width(width),
	m_height(height),

	m_x(x),
	m_y(y),

	m_sprite(),

	m_objectTexture(objectTexture),
	m_offsetX(offsetX),
	m_offsetY(offsetY),

	m_lastUpdatedTime(),
	m_lastSpriteChangedTime()
{
	m_lastUpdatedTime = sf::seconds(0);
	m_lastSpriteChangedTime = sf::seconds(0);
}

Object::~Object()
{}


int Object::getWidth() const
{
	return m_width;
}

int Object::getHeight() const
{
	return m_height;
}

int Object::getX() const
{
	return m_x;
}

int Object::getY() const
{
	return m_y;
}

sf::Sprite * Object::getSprite()
{
	return & m_sprite;
}
