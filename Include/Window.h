#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "INEventHandler.h"
#include "INUpdatable.h"
#include "INDrawable.h"
#include "gameStatus.h"

#include "TextureLoader.h"
#include "FontLoader.h"
#include "Menu.h"
#include "World.h"
//#include "Character.h"
//#include "Floor.h"

class Window //: public INEventHandler, public INUpdatable
{
	private:
		sf::Clock m_clock;

		sf::Music * m_musicMenu;

		sf::RectangleShape * lifeBar;

		sf::RenderWindow * m_window;
        sf::View m_view;

        TextureLoader * m_textureLoader;
        FontLoader * m_fontLoader;

        Menu * m_menu;
		World * m_currentWorld;

		game_status m_currentStatus;

		bool m_mouseButtonPressed;
		int m_mouseOldX;
		int m_mouseOldY;

		bool m_leftButtonPushed;
        bool m_leftButtonActivated; ///when the button has been pushed for enough time
		sf::Time m_timeLeftButtonPressed;
		bool m_rightButtonPushed;
        bool m_rightButtonActivated;
		sf::Time m_timeRightButtonPressed;
		bool m_bothButtonsEnabled;
		sf::Time m_buttonDeadZoneDelay; ///time max spent waiting for the second button to be pressed before doing the actual action of the button


	public:
		Window();
		virtual ~Window();

		/**
		 * @brief runs the game
		 */
		virtual int run();

		/**
		 * @brief draws the general window
		 *
		 * @param window: the window to be drawn in
		 */
		virtual void draw() const;

		/**
		 * @brief reacts to events
		 *
		 * @param event: the event to react to
		 */
		virtual void react(sf::Event const& event);

		/**
		 * @brief updates the state of the window
		 */
		virtual void update(sf::Clock const & clk);

	private:
		void leftButton() const;
		void rightButton() const;
		void bothButtons() const;

		void drawHUD() const;
};
