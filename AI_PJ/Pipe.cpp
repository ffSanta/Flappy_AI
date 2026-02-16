#include "Pipe.h"

void Pipe::initPipe(sf::RenderWindow* window,int random)
{

	pipeTop.setSize({ width,height });
	pipeBottom.setSize({ width,height });
	
	pipeTop.setFillColor(sf::Color::Green);
	pipeBottom.setFillColor(sf::Color::Yellow);

	int L = random + 150;
	int pipeBH = 600 - L;
	pipeTop.setSize({ 100.f,static_cast<float>(random) });
	pipeBottom.setSize({ 100.f,static_cast<float>(pipeBH) });
	pipeTop.setPosition({ static_cast<float>(window->getSize().x) - pipeTop.getSize().x,0 });
	pipeBottom.setPosition({ static_cast<float>(window->getSize().x) - pipeTop.getSize().x,static_cast<float>(window->getSize().y) - pipeBottom.getSize().y });
}


Pipe::Pipe(sf::RenderWindow* window,int random) : width(100) , height(250)
{
	initPipe(window,random);
}


void Pipe::pipeMove(sf::RenderWindow* window,const unsigned int gameSpeed)
{
	float rate = 0.5f;
	if (gameSpeed == 3) rate = 0.85f;
	pipeTop.move({ -5.f*(gameSpeed+(rate * gameSpeed)),0.f });
	pipeBottom.move({ -5.f*(gameSpeed+ (rate *gameSpeed)),0.f});

}

bool Pipe::pipeCollision(const sf::CircleShape &shape) const
{
	if (pipeTop.getGlobalBounds().findIntersection(shape.getGlobalBounds()) || pipeBottom.getGlobalBounds().findIntersection(shape.getGlobalBounds())) {
		//std::cout << "collusion !!! " << std::endl;
		return true;
	}
	return false;
}

void Pipe::draw(sf::RenderWindow* window) 
{
	window->draw(pipeTop);
	window->draw(pipeBottom);
}

sf::Vector2f Pipe::getPos()
{
	return pipeTop.getPosition();
}

sf::Vector2f Pipe::getSize()
{
	return pipeTop.getSize();
}
