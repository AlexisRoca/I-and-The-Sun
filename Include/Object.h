#pragma once
#include "INDrawable.h"
#include "INUpdatable.h"

class Object : public INDrawable, public INUpdatable
{
	protected:
		unsigned int m_width;
		unsigned int m_height;

		unsigned int m_x;
		unsigned int m_y;

		sf::Sprite m_sprite;

		sf::Texture * m_objectTexture;
		unsigned int m_offsetX;
		unsigned int m_offsetY;

		sf::Time m_lastUpdatedTime;
		sf::Time m_lastSpriteChangedTime;

	public:
		Object(unsigned int width, unsigned int height, unsigned int x, unsigned int y, sf::Texture * objectTexture, unsigned int offsetX, unsigned int offsetY);
		virtual ~Object();


		int getWidth() const;
		int getHeight() const;

		int getX() const;
		int getY() const;

		sf::Sprite * getSprite();

		virtual void draw(sf::RenderWindow * window) = 0;
		virtual void update(sf::Clock const& clk) = 0;
};

