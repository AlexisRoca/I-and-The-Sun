#pragma once

#include <SFML/Graphics.hpp>
#include "INDrawable.h"
#include "INEventHandler.h"
#include "INUpdatable.h"
#include "TextureLoader.h"
#include "FontLoader.h"

class Button : public INEventHandler, public INUpdatable
{
    public:
        Button(std::string const& title, float x, float y, sf::Vector2u windowSize, TextureLoader * textures, FontLoader * fonts);

        virtual void draw(sf::RenderWindow * window) const;
        virtual void update(sf::Clock const& clk);
        virtual void react(sf::Event const& event);

        bool isClicked() const;

    private:
        bool inside(int x, int y);

    private:
        bool m_clicked;

        sf::RectangleShape m_background;
        sf::Text m_title;

        sf::Vector2u m_windowSize;

        float m_x;
        float m_y;

        unsigned int m_width;
        unsigned int m_height;

        TextureLoader * m_textures;
        FontLoader * m_fonts;
};
