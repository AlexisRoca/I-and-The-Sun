#include "BurnableObject.h"

BurnableObject::BurnableObject(double flameVelocity, unsigned int maxBurnedDamage, unsigned int width, unsigned int height, unsigned int offsetX, unsigned int offsetY, unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture) :
	Object(width, height, x, y, objectTexture, offsetX, offsetY),

	m_burning(false),
    m_flameVelocity(flameVelocity),
    m_maxBurnedDamage(maxBurnedDamage),
    m_currentFlameIntensity(0),
    m_currentBurnedDamage(0),

    m_typeFire(-1),
    m_animFrame(0),

    m_fireTexture(fireTexture)
{}

BurnableObject::~BurnableObject()
{}

BurnableObject * BurnableObject::fromID(unsigned char objectID, unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture)
{
	switch (objectID)
	{
	case 'a':
		return Bed(x, y, objectTexture, fireTexture);
		break;
	case 'b':
		return Sofa(x, y, objectTexture, fireTexture);
		break;
	case 'c':
		return Toilet(x, y, objectTexture, fireTexture);
		break;
	case 'd':
		return Table(x, y, objectTexture, fireTexture);
		break;
	case 'e':
		return Oven(x, y, objectTexture, fireTexture);
		break;
	case 'f':
		return Fridge(x, y, objectTexture, fireTexture);
		break;
	case 'g':
		return KitchenTable(x, y, objectTexture, fireTexture);
		break;
	case 'h':
		return Tub(x, y, objectTexture, fireTexture);
		break;
	default:
		return new BurnableObject(0, 0, 0, 0, 0, 0, x, y, objectTexture, fireTexture);
		break;
	}
}

BurnableObject * BurnableObject::Bed(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture)
{
	return new BurnableObject(0.6, 15, 2, 3, 0, 0, x, y, objectTexture, fireTexture);
}

BurnableObject * BurnableObject::Sofa(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture)
{
	return new BurnableObject(0.5, 25, 2, 1, 0, 3, x, y, objectTexture, fireTexture);
}

BurnableObject * BurnableObject::Toilet(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture)
{
	return new BurnableObject(0.0, 10, 1, 1, 2, 0, x, y, objectTexture, fireTexture);
}

BurnableObject * BurnableObject::Table(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture)
{
	return new BurnableObject(1.0, 20, 1, 1, 2, 1, x, y, objectTexture, fireTexture);
}

BurnableObject * BurnableObject::Oven(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture)
{
	return new BurnableObject(0.5, 50, 1, 1, 2, 2, x, y, objectTexture, fireTexture);
}

BurnableObject * BurnableObject::Fridge(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture)
{
	return new BurnableObject(0.5, 50, 1, 1, 2, 3, x, y, objectTexture, fireTexture);
}

BurnableObject * BurnableObject::KitchenTable(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture)
{
	return new BurnableObject(0.5, 50, 1, 1, 3, 0, x, y, objectTexture, fireTexture);
}

BurnableObject * BurnableObject::Tub(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture)
{
	return new BurnableObject(0.0, 10, 1, 2, 3, 1, x, y, objectTexture, fireTexture);
}


void BurnableObject::ignite(double fire)
{
	if(!m_burning && m_currentBurnedDamage < m_maxBurnedDamage)
	{
		m_burning = true;
		m_currentFlameIntensity = fire;
		m_typeFire = 0;
		m_animFrame = 0;
	}
}

void BurnableObject::stopFire()
{
	if (m_burning)
	{
		m_burning = false;
		m_currentFlameIntensity = 0;
		m_typeFire = 2;
		m_animFrame = 0;
	}
}

double BurnableObject::lifeLost() const
{
	return m_currentFlameIntensity;
}

double BurnableObject::getMaxBurnedDamage() const
{
	return m_maxBurnedDamage;
}

bool BurnableObject::isBurned() const
{
	return (m_currentBurnedDamage > m_maxBurnedDamage);
}


void BurnableObject::draw(sf::RenderWindow * window)
{
	m_sprite.setTexture(*m_objectTexture);
	unsigned int ndg = 255 - ((float)m_currentBurnedDamage / m_maxBurnedDamage) * 255;
	m_sprite.setColor(sf::Color(ndg, ndg, ndg));
	m_sprite.setTextureRect(sf::IntRect(32 * m_offsetX, 32 * m_offsetY, 32 * m_width, 32 * m_height));
	m_sprite.setPosition(m_x * 32, m_y * 32);
	window->draw(m_sprite);

	if (m_typeFire >= 0)
	{
		sf::Sprite fireSprite;
		fireSprite.setTexture(*m_fireTexture);
		fireSprite.setTextureRect(sf::IntRect(64 * m_animFrame, 4 * 32 * m_typeFire, 64, 4 * 32));
		fireSprite.setOrigin(32, 3 * 32 + 16);
		fireSprite.setPosition(m_x * 32 + m_width * 16, m_y * 32 + m_height * 16);
		window->draw(fireSprite);
	}
}

void BurnableObject::update(sf::Clock const & clk)
{
	sf::Time elapsedTime = clk.getElapsedTime() - m_lastUpdatedTime;
	m_lastUpdatedTime = clk.getElapsedTime();
	if (m_burning)
	{
		m_currentBurnedDamage += m_currentFlameIntensity*elapsedTime.asSeconds();
		if (m_currentBurnedDamage > m_maxBurnedDamage)
		{
			this->stopFire();
		}
	}

	if ((clk.getElapsedTime() - m_lastSpriteChangedTime).asMilliseconds() > 100)
	{
		m_lastSpriteChangedTime = clk.getElapsedTime();
		m_animFrame++;
		if (m_animFrame == 8)
		{
			if (m_typeFire == 0)
				m_typeFire = 1;
			else if (m_typeFire == 2)
				m_typeFire = -1;

			m_animFrame %= 8;
		}
	}
}