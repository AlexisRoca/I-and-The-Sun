#pragma once

#include <SFML/Graphics.hpp>

#include "Object.h"
#include "Ray.h"

class BurnableObject : public Object
{
	private:
		bool m_burning;
		
		const double m_flameVelocity;
		const double m_maxBurnedDamage;
		
		double m_currentFlameIntensity;
		double m_currentBurnedDamage;

		int m_typeFire; //-1: none, 0: starting, 1: looping, 2: stopping
		unsigned int m_animFrame; //between 0 and 7
		
		sf::Texture * m_fireTexture;

	private:
		/**
		* @brief creates an object
		*
		* @param flameVelocity: velocity of the flame increase (per second)
		* @param maxBurnedDamage: max health
		* @param width: width of the object
		* @param height: height of the object
		* @param offsetX: position X of the top-left corner of this object in the texture
		* @param offsetY: texture offset Y
		* @param x: position x of the tile where to put this object
		* @param y: position y of the tile where to put this object
		* @param texture: texture to use
		*/
		BurnableObject(double flameVelocity, unsigned int maxBurnedDamage, unsigned int width, unsigned int height, unsigned int offsetX, unsigned int offsetY, unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture);


	public:
		virtual ~BurnableObject();

		static BurnableObject * fromID(unsigned char objectID, unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture);

		static BurnableObject * Bed(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture);
		static BurnableObject * Sofa(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture);
		static BurnableObject * Toilet(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture);
		static BurnableObject * Table(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture);
		static BurnableObject * Oven(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture);
		static BurnableObject * Fridge(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture);
		static BurnableObject * KitchenTable(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture);
		static BurnableObject * Tub(unsigned int x, unsigned int y, sf::Texture * objectTexture, sf::Texture * fireTexture);

		virtual void ignite(double fire);
		virtual void stopFire();
		virtual double lifeLost() const;
		virtual double getMaxBurnedDamage() const;

		virtual void draw(sf::RenderWindow * window);
		virtual void update(sf::Clock const& clk);
		virtual void collision(Ray * ray);
};

