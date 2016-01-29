#pragma once
#include <SFML/Audio.hpp>

#include <iostream>

#include "Object.h"

#include "INUpdatable.h"
#include "INDrawable.h"
#include "INCollisionable.h"

#include "Ray.h"

class Room;

class FireSensor : public Object, public INUpdatable, public INDrawable, public INCollisionable
{
    private:
        double const m_radius;
        unsigned char m_assignedRoom;

        bool m_isActivated;

		sf::Music * m_musicFireSensor;

    public:
        /**
         * @brief constuctor for FireSensor
         *
         * @param radius: the range of the FIreDetector 
         * @param parentRoom: the room where the FIreDectector is inside
         */
        FireSensor(unsigned int x, unsigned int y, double radius, sf::Texture * texture);

        virtual ~FireSensor();


		virtual unsigned int getX() const;

		virtual unsigned int getY() const;

		virtual void activate();

        /**
         *@brief send a ray to find a collision with a floor or objects
         *
         *@param ray: the ray who will intersect somethings or not
         */
        /**
         *@brief	draw the FIreDetector
         *
         */
        virtual void draw(sf::RenderWindow * window);
        virtual void update(sf::Clock const& clk);
        virtual void collision(Ray * ray);
};
