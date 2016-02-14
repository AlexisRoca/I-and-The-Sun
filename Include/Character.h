#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Ray.h"
#include "INDrawable.h"
#include "INUpdatable.h"
#include "TextureLoader.h"



class Character : public INDrawable, public INUpdatable
{
	enum StateAnimation{
		Left,
		Midle,
		Right
	};


	private: 
		sf::Sprite m_charaterSprite;
		const sf::Texture * m_texture;

        sf::Vector2f m_position;
		unsigned char m_currentRoom;

		unsigned int m_currentAnimation;
        sf::Time m_lastAnimationUpdate;

		const float m_velocity;
		bool m_jumping;
		double m_angleJump;

		Ray	m_collisionRay;
		bool m_statusCollision;
		double m_distanceToCollision = 0;


	public:
		/**
		* @brief constuctor for Character
		*
		*/
		Character(TextureLoader * textures);

		/**
		* @brief destructor for Character
		*/
		virtual ~Character();

		/**
		* @brief set the angle before jummping
		*
		*/
		void setAngle(double alpha);
		
		/**
		* @brief set the angle before jummping
		*
		*/
		double  getAngle() const ;

		void setDistanceToCollision(double distance);

		/**
		* @brief Get the velocity of the character
		*
		*/
		float getVelocity();

		/**
		* @brief Return the direction which facing the character
		*
		*/
		sf::Vector2f getDirection();

		/**
		* @brief Get the current position of the character
		*
		*/
		sf::Vector2f getPosition();

		/**
		* @brief Get the new position of the character
		*	if he moves
		*
		*/
		sf::Vector2f nextFramePosition();
	
		/**
		* @brief get if the character is in collision actually
		*	
		*
		*/
		bool getStatusCollision();
		
		unsigned char getCurrentRoom();
		void setCurrentRoom(unsigned char assignedRoom);
		
		/**
		* @brief set if the character is in collision or not
		*	
		*
		*/
		void setStatusCollision(bool isInCollision);

		sf::Sprite * getSprite();

		/**
		* @brief Set the position of the character
		*
		* @param position:
		*
		*/
		void setPosition(sf::Vector2f position);

		/**
		* @brief Return the direction which facing the character
		*
		*/
		Ray * jump();

		Ray getJumpRay();

		/**
		* @brief Check if the caracter is moving
		*
		*/
		bool isJumping();

		/**
		* @brief draw the character
		*
		* @param window: 
		*
		*/
		virtual void draw(sf::RenderWindow *window);

		/**
		* @brief update the character
		*
		*
		*/
		virtual void update(sf::Clock const & clk);

		bool collision(sf::Sprite const * sprite);
};

