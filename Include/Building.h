#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <iterator>   

#include "INDrawable.h"
#include "INUpdatable.h"

#include "BurnableObject.h"
#include "TextureLoader.h"
//#include "Character.h"
#include "Floor.h"
#include "Room.h"
#include "FireSensor.h"

class Building : public INDrawable, public INUpdatable
{
	private:
		const unsigned int m_maxBurnedDamage;
		const unsigned int m_currentBurnedDamage;

		const TextureLoader * m_textureLoader;

		std::vector<Floor *> m_floors;
		Floor * m_currentFloor;

	public:
		 /**
        	 * @brief constuctor for building
        	 *
        	 * @param textureLoader: the link of the texture file
        	 * @param maxBurnedDamage: Number max of domage for building
		 * @param currentBurnedDamage: actual Number of domage il the building
        	 */
		Building(TextureLoader const * textureLoader, unsigned int maxBurnedDamage = 0, unsigned int currentBurnedDamage = 0);

		/**
         	* @brief destructor for Canape
         	*
         	*/
		virtual ~Building();

		std::vector<Floor * > * getFloors();
		Floor * getCurrentFloor();


		void loadNextFloor();

		/**
		*@brief charge the level from files
		*
		*@param window: window whitch containt the building
		*/
		void loadBuilding(std::string const & path);

		/**
		*@brief show the building
		*
		*@param window: window whitch containt the building
		*/	
		virtual void draw(sf::RenderWindow *window);

        /**
         * @brief updates this
         */
		virtual void update(sf::Clock const & clk);
};