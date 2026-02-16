#include "Bots.h"

void Bots::initBots(sf::RenderWindow* window)
{
	flappy.setRadius(_radius);
	flappy.setPosition({ 100.f,static_cast<float>(window->getSize().y / 2) });
	
	collision = false;
}

Bots::Bots(sf::RenderWindow* window) : gravity(0.2f), point(0)
{
	initBots(window);
	flappy.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
}

void Bots::flapyyMove(sf::RenderWindow* window , const unsigned int gameSpeed)
{

	if (flappy.getPosition().y + Bots::_radius*2 >= window->getSize().y) {
		gravity = 0;
		return;
	}
	else if (gravity <= window->getSize().y)
	flappy.move({ 0.f,gravity += (0.4f * gameSpeed)});

}

void Bots::drawFlappy(sf::RenderWindow* window) const
{
	window->draw(flappy);
}

sf::CircleShape Bots::returnShape() const
{
	return flappy;
}

void Bots::flappyCollision()
{
	collision = true;
}

void Bots::flappyReCollision(sf::RenderWindow* window)
{
	initBots(window);
	gravity = 0.0f;
}

float Bots::getPosX() const
{
	return flappy.getPosition().x;
}

void Bots::gainPoint()
{
	point++;
}

unsigned int Bots::getPoint() const
{
	return point;
}

void Bots::getInput(sf::RenderWindow* window,Pipe& pipe,const unsigned int gameSpeed)
{
	float distanceX = (pipe.getPos().x - flappy.getPosition().x) / window->getSize().x;
	float distanceY = ((pipe.getSize().y + 75) - flappy.getPosition().y) / window->getSize().y;
	float iGravity = gravity / window->getSize().y;
	std::vector<float> input = { distanceX,distanceY,iGravity };
	float output = neural.forward(input);
	if (output > 0.5f) gravity = -3.0f * gameSpeed;
	else return;
}

void Bots::transform(Neural& fitness,const unsigned int index)
{
	std::cout << "Flappy " << index+1 << std::endl;
	for (int i = 0 ; i < neural.wInput.size() ; i++)
	{
		neural.wInput[i] = rand() % 10 < 7 ? fitness.wInput[i] : neural.float_rand();
		std::cout  << "w " << i << " : " << neural.wInput[i] << std::endl;
	}
	neural.bias = rand() % 10 < 5 ? fitness.bias : neural.float_rand();
	std::cout << "bias : " << neural.bias << "\n" << "----------------------------------\n";
}

void Bots::resetPoint()
{
	point = 0;
}

void Bots::mutate(float rate)
{
	for (auto& w : neural.wInput)
		if ((rand() % 1000) / 1000.0f < rate)
			w += ((rand() % 2000) / 1000.0f - 1.0f) * 0.1f;
	if ((rand() % 1000) / 1000.0f < rate)
		neural.bias += ((rand() % 2000) / 1000.0f - 1.0f) * 0.1f;
}


