#include "FireSensor.h"

FireSensor::FireSensor(unsigned int x, unsigned int y, double radius, sf::Texture * texture) :
	Object(32, 32, x,y,texture,0,0),
	
    m_radius(radius),

    m_isActivated(false),
	m_musicFireSensor(new sf::Music())
{
	m_musicFireSensor->openFromFile("Ressources/Music/FireDetect.wav");
}

FireSensor::~FireSensor()
{
	delete m_musicFireSensor;
}


unsigned int FireSensor::getX() const
{
	return m_x;
}

unsigned int FireSensor::getY() const
{
	return m_y;
}

void FireSensor::activate()
{
	m_musicFireSensor->play();
	m_isActivated = true;
}


void FireSensor::draw(sf::RenderWindow * window)
{
	sf::CircleShape shape(m_radius);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(5);
	shape.setOutlineColor(sf::Color(0, 0, 100));
	shape.setOrigin(m_radius, m_radius);
	shape.setPosition((m_x*32),(m_y * 32));
	window->draw(shape);

    sf::Sprite fireDetectorSprite;
	fireDetectorSprite.setTexture(*m_objectTexture);
	fireDetectorSprite.setTextureRect(sf::IntRect((m_isActivated? 32:0),0, 32, 32));
	fireDetectorSprite.setOrigin(16, 16);
	fireDetectorSprite.setPosition(m_x * 32, m_y * 32);
    window->draw(fireDetectorSprite);
}

void FireSensor::update(sf::Clock const& clk)
{
    //TODO
}

//void FireSensor::collision(Ray * ray)
//{
//    if(ray->intersectCircle(sf::Vector2f((m_x*32)+16,(m_y*32)+16), m_radius, false))
//        activate();
//}
