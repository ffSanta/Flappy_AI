#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Neural.h"
#include "Pipe.h"
#include <math.h>
class Bots
{
	sf::CircleShape flappy;
	static constexpr float _radius = 15.0f;
	float gravity;
	bool collision;
	unsigned int point;
	void initBots(sf::RenderWindow* window); 
public :
	Neural neural;
	Bots(sf::RenderWindow* window);
	Bots() {};
	void flapyyMove(sf::RenderWindow* window, const unsigned int gameSpeed);
	void drawFlappy(sf::RenderWindow* window) const;
	sf::CircleShape returnShape() const;
	void flappyCollision();
	void flappyReCollision(sf::RenderWindow* window);
	float getPosX() const;
	void gainPoint();
	unsigned int getPoint() const;
	void getInput(sf::RenderWindow* window,Pipe& pipe, const unsigned int gameSpeed);
	void transform(Neural& fitness, const unsigned int index);
	void resetPoint();
	void mutate(float rate);
};