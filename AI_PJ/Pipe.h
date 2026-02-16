#pragma once
#include <random> 
#include <SFML/Graphics.hpp> 
#include <iostream>
class Pipe
{
	float width, height;
	sf::RectangleShape pipeTop;
	sf::RectangleShape pipeBottom;

	void initPipe(sf::RenderWindow* window, int random);

public :
	Pipe(sf::RenderWindow* window,int random);
	void pipeMove(sf::RenderWindow* window,const unsigned int gameSpeed);
	bool pipeCollision(const sf::CircleShape& shape ) const;
	void draw(sf::RenderWindow* window);
	sf::Vector2f getPos();
	sf::Vector2f getSize();
};