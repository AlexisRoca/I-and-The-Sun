#pragma once

#include <iostream>

#include "Object.h"
#include "BurnableObject.h"
#include "FireSensor.h"

#include "INDrawable.h"
#include "INUpdatable.h"
#include "INCollisionable.h"

class Room : public INDrawable, public INUpdatable, public INCollisionable
{
	private:
		const unsigned char m_id;

		std::vector<FireSensor *> m_fireSensors;
		std::vector<BurnableObject *> m_burnableObjects;

		const double m_maxLife;
		double m_currentLife;

	public:
		Room(unsigned char id, double maxLife);
		~Room();

		void addFurniture(BurnableObject * burnableObject);
		void addFireSensor(FireSensor * object);

		void setDamage(const double damage);
		void stopFire();

		unsigned char getRoomId() const;
		double getLife() const;
		double getMaxLife() const;

		virtual void draw(sf::RenderWindow *window);
		virtual void update(sf::Clock const & clk);
		virtual void collision(Ray * ray);
};

