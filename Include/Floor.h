#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "TextureLoader.h"
#include "Room.h"

#include "INDrawable.h"
#include "INUpdatable.h"

//#include "Teleporter.h

class Floor : public INDrawable, public INUpdatable
{
	private:
		std::vector<std::vector<unsigned char> > m_background;
		std::vector<std::vector<unsigned char> > m_floorMap;

		std::map<unsigned char, Room *> m_rooms;
  //      std::vector<Teleporter *> m_teleporters;

		sf::Texture * m_textureBuilding;

		double m_maxLife;
		double m_currentLife;

	public:
		Floor(TextureLoader const * textureLoaders);
		virtual ~Floor();

		void addLineToBackground(std::vector<unsigned char> line);
		void addLineToRoomsMap(std::vector<unsigned char> line);

		/**
         * @brief adds a room to this floor
         *
         * @param room: the room to add (dynamically-created pointer)
         * @note Floor takes ownership of the Room, and will destroy it when needed
         */
        void addRoom(unsigned char roomId);
		Room * getRoom(unsigned char roomId);
		std::map<unsigned char, Room *> * getRooms();

		
		//void addTeleporter(Teleporter * teleporter);


		//std::vector<Teleporter *> getTeleporter();
		std::vector<std::vector<unsigned char> > * getFloorMap();
		
		
		virtual void setLife(double lostLife);
		virtual double getLife() const;
		virtual double getMaxLife() const;

		virtual double lifeStay() const;


		virtual void update(sf::Clock const & clk);
		virtual void draw(sf::RenderWindow *window);

		bool collision(sf::Sprite * sprite);


	private:
		sf::Vector2u offset(unsigned int i, unsigned int j) const;
};

