#pragma once

#include "INEventHandler.h"
#include "INUpdatable.h"
#include "INDrawable.h"
#include "gameStatus.h"

#include "TextureLoader.h"
#include "FontLoader.h"

#include "Button.h"

class Menu
{
    public:
        Menu(sf::Vector2u windowSize, TextureLoader * textures, FontLoader * fonts);

        virtual void draw(sf::RenderWindow * window, game_status const& status) const;
        virtual void update(sf::Clock const& clk, game_status & status);
		virtual void react(sf::Event const& event, game_status & status);

    private:
        TextureLoader * m_textures;
        FontLoader * m_fonts;

        sf::Vector2u m_windowSize;

        Button m_buttonStartGame;
        Button m_buttonQuitGame;
};
