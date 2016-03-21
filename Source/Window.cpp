#include "Window.h"

#define PATH_RESSOURCE "Ressources/"
#define DELAY_BEETWEEN_2_BUTTON 20

Window::Window():
    m_clock(),
	m_musicMenu(new sf::Music()),

    m_window(new sf::RenderWindow(sf::VideoMode(800, 600), "I & the sun")),
	m_textureLoader(new TextureLoader(PATH_RESSOURCE)),
	m_fontLoader(new FontLoader("Ressources/")),
  
    m_menu(new Menu(m_window->getSize(), m_textureLoader, m_fontLoader)),
    m_currentWorld(new World(m_textureLoader)),
    
	m_currentStatus(GAME_MAIN_MENU),
    m_mouseButtonPressed(false),
    m_leftButtonPushed(false),
    m_leftButtonActivated(false),
    m_timeLeftButtonPressed(),
    m_rightButtonPushed(false),
    m_rightButtonActivated(false),
    m_timeRightButtonPressed(),
    m_bothButtonsEnabled(false),

	lifeBar(new sf::RectangleShape())
{
    m_buttonDeadZoneDelay = sf::milliseconds(20);

    m_view = sf::View(sf::FloatRect(0, 0, m_window->getSize().x , m_window->getSize().y));
	
	m_musicMenu->openFromFile("Ressources/Music/Menu.wav");
	m_musicMenu->setLoop(true);
	m_musicMenu->play();
}


Window::~Window()
{
    if(m_window->isOpen())
        m_window->close();

    delete m_currentWorld;
    delete m_window;
	delete m_musicMenu;
}

int Window::run()
{
	//update state of the system
	sf::Clock clk;
	m_musicMenu->stop();

    while(m_currentStatus != GAME_STOPPED)
    {
        //events
        sf::Event event;
        while(m_window->pollEvent(event))
            this->react(event);

		if (clk.getElapsedTime().asMilliseconds() > DELAY_BEETWEEN_2_BUTTON)
		{
			this->update(clk);

			//drawing
			m_window->clear();
			m_window->setView(m_view);
			this->draw();
			m_window->display();
		}
    }

    m_window->close();

    return EXIT_SUCCESS;
}

void Window::draw() const
{
    if(m_currentStatus == GAME_PLAYING)
    {
        m_window->setView(m_view);
        m_currentWorld->draw(m_window);
        this->drawHUD();
    }
    else
        m_menu->draw(m_window, m_currentStatus);
}

void Window::react(sf::Event const& event)
{
    if(event.type == sf::Event::Closed)
    {
        m_currentStatus = GAME_STOPPED;
    }

    if(event.type == sf::Event::Resized)
    {
        m_view = sf::View(sf::FloatRect(0,0, event.size.width, event.size.height));
    }

    if(m_currentStatus == GAME_PLAYING)
    {
        if(event.type == sf::Event::MouseWheelScrolled)
        {
            if(event.mouseWheelScroll.delta < 0)
                m_view.zoom(1.2);
            else
                m_view.zoom(0.8);
        }

        else if(event.type == sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
                m_mouseButtonPressed = true;
        }

        else if(event.type == sf::Event::MouseButtonReleased)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
                m_mouseButtonPressed = false;
        }

        else if(event.type == sf::Event::MouseMoved)
        {
            if(m_mouseButtonPressed)
            {
                int deltaX = m_mouseOldX - event.mouseMove.x;
                int deltaY = m_mouseOldY - event.mouseMove.y;

                m_view.move(deltaX, deltaY);
            }

            m_mouseOldX = event.mouseMove.x;
            m_mouseOldY = event.mouseMove.y;
        }

        else if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Left)
            {
                if(m_rightButtonPushed)
                {
                    if((m_clock.getElapsedTime() - m_timeRightButtonPressed) < m_buttonDeadZoneDelay)
                    {
                        m_bothButtonsEnabled = true;
                        //one-time action for both buttons
                        bothButtons();
                    }

                    else
                    {
                        m_leftButtonPushed = false;
                        m_rightButtonPushed = false;
                    }
                }

                else
                {
                    m_leftButtonPushed = true;
                    m_timeLeftButtonPressed = m_clock.getElapsedTime();
                }
            }

            else if(event.key.code == sf::Keyboard::Right)
            {
                if(m_leftButtonPushed)
                {
                    if((m_clock.getElapsedTime() - m_timeLeftButtonPressed) < m_buttonDeadZoneDelay)
                    {
                        m_bothButtonsEnabled = true;
                        //one-time action for both buttons
                        bothButtons();
                    }

                    else
                    {
                        m_rightButtonPushed = false;
                        m_leftButtonPushed = false;
                    }
                }

                else
                {
                    m_rightButtonPushed = true;
                    m_timeRightButtonPressed = m_clock.getElapsedTime();
                }
            }
        }

        else if(event.type == sf::Event::KeyReleased)
        {
            if(event.key.code == sf::Keyboard::Left)
            {
                if(m_bothButtonsEnabled)
                {
                    m_rightButtonPushed = false;
                    m_bothButtonsEnabled = false;
                }
                else
                    leftButton();
                m_leftButtonPushed = false;
                m_leftButtonActivated = false;
            }
            else if(event.key.code == sf::Keyboard::Right)
            {
                if(m_bothButtonsEnabled)
                {
                    m_leftButtonPushed = false;
                    m_bothButtonsEnabled = false;
                }
                else
                    rightButton();
                m_rightButtonPushed = false;
                m_rightButtonActivated = false;
            }
        }
    }
    else
        m_menu->react(event, m_currentStatus);
}

void Window::update(sf::Clock const & clk)
{
    if(m_currentStatus == GAME_PLAYING)
    {
        if(m_bothButtonsEnabled)
        {
            //repeated action for both buttons 
        }
        else if(m_leftButtonPushed)
        {
            if(m_leftButtonActivated)
                leftButton();
            else if((m_clock.getElapsedTime() - m_timeLeftButtonPressed) >= m_buttonDeadZoneDelay)
                m_leftButtonActivated = true;
        }
        else if(m_rightButtonPushed)
        {
            if(m_rightButtonActivated)
                rightButton();
            else if((m_clock.getElapsedTime() - m_timeRightButtonPressed) >= m_buttonDeadZoneDelay)
                m_rightButtonActivated = true;
        }

        m_currentWorld->update(clk);
    }
    else
        m_menu->update(clk, m_currentStatus);


	//std::cout << m_currentWorld->getCharacter()->isJumping() << std::endl;

	if(m_currentWorld->getCharacter()->isJumping())
	{
		m_currentWorld->getCharacter()->setPosition(m_currentWorld->getCharacter()->nextFramePosition());

		sf::Sprite * characterSprite = m_currentWorld->getCharacter()->getSprite();
		unsigned char currentRoom = m_currentWorld->getCharacter()->getCurrentRoom();
		

		std::vector<std::vector<unsigned char> > * floorMap = m_currentWorld->getBuilding()->getCurrentFloor()->getFloorMap();
		std::vector<BurnableObject *> * burnableObjects = m_currentWorld->getBuilding()->getCurrentFloor()->getRoom(currentRoom)->getBurnableObjects();

		

		//Collision test
		for(int i=0; i<floorMap->size(); i++)
		{
			for(int j=0; j<(*floorMap).size(); j++)
			{
				if((*floorMap)[i][j] == '0')
				{
					sf::RectangleShape wall(sf::Vector2f(32,32));
					wall.setPosition(sf::Vector2f(i*32,j*32));

					if(wall.getGlobalBounds().intersects(characterSprite->getGlobalBounds()))
						m_currentWorld->getCharacter()->stop();
				}
			}
		}
		
		
		for(int i=0; i<burnableObjects->size(); i++)
		{
			if (!(*burnableObjects)[i]->isBurned())
			{
				if ((*burnableObjects)[i]->getSprite()->getGlobalBounds().intersects(characterSprite->getGlobalBounds()))
				{
					(*burnableObjects)[i]->ignite(10);
					m_currentWorld->getCharacter()->stop();
				}
			}
		}
	}
}

void Window::leftButton() const
{
	m_currentWorld->getCharacter()->setAngle(-0.4);
}

void Window::rightButton() const
{
    m_currentWorld->getCharacter()->setAngle(0.4);
}

void Window::bothButtons() const
{	
	Ray * collisionRay = m_currentWorld->getCharacter()->jump();

	//m_currentWorld->getBuilding()->getCurrentFloor()->collision(collisionRay);
	//m_currentWorld->getCharacter()->setDistanceToCollision(collisionRay->distanceToIntersection());
}

void Window::drawHUD() const
{
	sf::RectangleShape rectangle(sf::Vector2f(30, 10));
	m_window->draw(rectangle);
}
