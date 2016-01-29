#include "Button.h"

Button::Button(std::string const& title, float x, float y, sf::Vector2u windowSize, TextureLoader * textures, FontLoader * fonts):
    m_clicked(false),
    m_background(),
    m_title(),
    m_windowSize(windowSize),
    m_x(x),
    m_y(y),
    m_width(200),
    m_height(10),
    m_textures(textures),
    m_fonts(fonts)
{
    m_title.setFont(m_fonts->upheavtt());
    m_title.setString(title);
    m_title.setCharacterSize(50);
    m_title.setColor(sf::Color::White);
    m_title.setPosition(m_x*m_windowSize.x, m_y*m_windowSize.y - m_height/2);

    sf::FloatRect boundingBox = m_title.getGlobalBounds();
    m_title.setOrigin(boundingBox.width/2, boundingBox.height/2);
    
    m_width = (boundingBox.width > m_width)? boundingBox.width : m_width;
    m_height = (boundingBox.height > m_height)? boundingBox.height : m_height;
    m_height *= 3;

    m_background.setFillColor(sf::Color(50, 50, 50));
    m_background.setSize(sf::Vector2f(m_width, m_height));
    m_background.setOrigin(m_width/2, m_height/2);
    m_background.setPosition(m_x*m_windowSize.x, m_y*m_windowSize.y);
}

void Button::draw(sf::RenderWindow * window) const
{
    window->draw(m_background);
    window->draw(m_title);
}

void Button::update(sf::Clock const& clk)
{
    if(m_clicked)
        m_clicked = false;
}

void Button::react(sf::Event const& event)
{
    if(event.type == sf::Event::MouseMoved)
    {
        if(inside(event.mouseMove.x, event.mouseMove.y))
            m_title.setColor(sf::Color(128, 128, 128));
        else
            m_title.setColor(sf::Color::White);
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        if(inside(event.mouseButton.x, event.mouseButton.y))
        {
            if(event.mouseButton.button == sf::Mouse::Left)
                m_clicked = true;
        }
        else
            m_clicked = false;
    }
    else if(event.type == sf::Event::Resized)
    {
        m_windowSize.x = event.size.width;
        m_windowSize.y = event.size.height;
        m_background.setPosition(m_x*m_windowSize.x, m_y*m_windowSize.y);
        m_title.setPosition(m_x*m_windowSize.x, m_y*m_windowSize.y - m_height/3);
    }
}

bool Button::isClicked() const
{
    return m_clicked;
}

bool Button::inside(int x, int y)
{
    return x >= (m_x*m_windowSize.x - m_width/2) && x <= (m_x*m_windowSize.x + m_width/2) && y >= (m_y*m_windowSize.y - m_height/2) && y <= (m_y*m_windowSize.y + m_height/2);
}
