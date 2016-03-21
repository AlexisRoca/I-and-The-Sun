#pragma once

#include <iostream>

#include "Object.h"
#include "BurnableObject.h"
#include "FireSensor.h"

#include "INDrawable.h"
#include "INUpdatable.h"

class Room : public INDrawable, public INUpdatable
{
	private:
		const unsigned char m_id;

		std::vector<BurnableObject *> m_burnableObjects;
		std::vector<FireSensor *> m_fireSensors;

		const double m_maxLife;
		double m_currentLife;

	public:
		Room(unsigned char id, double maxLife);
		~Room();

		void addFurniture(BurnableObject * burnableObject);
		void addFireSensor(FireSensor * object);

		std::vector<BurnableObject *> * getBurnableObjects();
		std::vector<FireSensor *> * getFireSensors();

		void setDamage(const double damage);
		void stopFire();

		unsigned char getRoomId() const;
		double getLife() const;
		double getMaxLife() const;

		virtual void draw(sf::RenderWindow *window);
		virtual void update(sf::Clock const & clk);
};

