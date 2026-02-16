#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include "Pipe.h"
#include <vector>
#include "Bots.h"
#include <sstream>

void death(std::vector<Bots>& flappy ,const unsigned int index , bool& gameStop);

int main()
{
	//random
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution xRan(175, 300);
	int pipeTH = xRan(rng);

	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "FLAPPY AI");
	window.setFramerateLimit(60);
	
	std::vector<Pipe> pipes;
	pipes.emplace_back(&window, pipeTH);
	bool gameStop = false;
	float timer = 0.0f;

	//font
	sf::Font font;
	if (!font.openFromFile("Fonts/ARIALNI.TTF")) std::cout << "cant load font!!" << std::endl;
	sf::Text text(font);
	text.setCharacterSize(24);

	//bots
	srand(time(0));
	Bots flappy(&window);
	Bots flappy2(&window);
	Bots mFlappy(&window);
	std::vector<Bots> flappies = { flappy,mFlappy,flappy2 };
	std::vector<unsigned int> fitness(3);

	std::cout << "Copy Flappy " << std::endl;
	std::vector<Bots> saveWFlappy(1);
	saveWFlappy[0].resetPoint();

	unsigned int index = 0;
	unsigned int gameSpeed = 1;
	unsigned int generation = 1;
	bool getPoint = false;
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			if (auto keyRelease = event->getIf < sf::Event::KeyReleased>())
			{
				//force death
				if (keyRelease->scancode == sf::Keyboard::Scancode::D)
				{
					death(flappies, index, gameStop);
				}

				//increase speed เพิ่มความเร็วเกม
				if (keyRelease->scancode == sf::Keyboard::Scancode::W)
				{
					++gameSpeed;
					if (gameSpeed >= 4) gameSpeed--;
				}

				//ลดความเร็วเกม
				if (keyRelease->scancode == sf::Keyboard::Scancode::S)
				{
					--gameSpeed;
					if (gameSpeed <= 0) gameSpeed++;
				}
			}
		}

		if (!gameStop)
		{
			flappies[index].flapyyMove(&window,gameSpeed);

			if (timer > 6.5f)
			{
				pipeTH = xRan(rng);
				pipes.push_back(Pipe(&window, pipeTH));
				timer = 0;
			}
			else timer += 0.1f * gameSpeed;
			for (int i = 0; i < pipes.size(); i++)
			{
				pipes[i].pipeMove(&window,gameSpeed);
				
				if (pipes[i].pipeCollision(flappies[index].returnShape()))
				{
					death(flappies,index,gameStop);
				}
				if (flappies[index].getPosX() >= pipes[i].getPos().x + pipes[i].getSize().x && !getPoint)
				{
					flappies[index].gainPoint();
					getPoint = true;
				}
				if (pipes[i].getPos().x + pipes[i].getSize().x <= 0)
				{
					pipes.erase(pipes.begin() + i);
					pipes[0].pipeMove(&window,gameSpeed);
					getPoint = false;
				}
			}

			flappies[index].getInput(&window, pipes[0],gameSpeed);

			std::stringstream ss;
			ss << " | " << index+1 << " | " << " Point : " << flappies[index].getPoint() 
				<< "\nGeneration : " << generation << "\nGameSpeed : " << gameSpeed;

			text.setString(ss.str());


			window.clear();
			for (int i = 0; i < pipes.size(); i++)
			{
				pipes[i].draw(&window);
			}
			flappies[index].drawFlappy(&window);
			window.draw(text);
			window.display();

		}

		else {
			gameStop = false;
			fitness[index] = flappies[index].getPoint();
			
			index++;
			if (index >= 3)
			{
				unsigned int max = fitness[0];
				int tactIndex = 0;
				

				for (int i = 1; i < 3; i++)
				{
					if (max < fitness[i]) {
						max = fitness[i];
						tactIndex = i;
					}
				}
				std::cout << "Recent Point : " << flappies[0].getPoint() << std::endl;
				std::cout << "Most Point : " << flappies[tactIndex].getPoint() << std::endl;
				if (saveWFlappy[0].getPoint() < flappies[tactIndex].getPoint())
					saveWFlappy[0] = flappies[tactIndex];

				if (flappies[tactIndex].getPoint() < saveWFlappy[0].getPoint())
				{
					float rate = 0.1f;
					for (int i = 0; i < 3; i++)
					{

					flappies[i].transform(saveWFlappy[0].neural,i);
					flappies[i].mutate(rate);
					flappies[i].resetPoint();
					}
				}
				else 
					for (int i = 0; i < 3; i++)
					{
						
						if (i != tactIndex)
						{
							flappies[i].transform(flappies[tactIndex].neural,i);
						}
						flappies[i].mutate(0.1f);
						flappies[i].resetPoint();
					}

				index=0;
				generation++;
			}

			//reset game-------------------------------
			pipeTH = xRan(rng);
			pipes.clear();
			pipes.emplace_back(&window, pipeTH); 
			timer = 0.0f;
			flappies[index].flappyReCollision(&window);
			//-----------------------------------------

		}
	}
}

void death(std::vector<Bots>& flappy, const unsigned int index, bool& gameStop)
{
	flappy[index].flappyCollision();
	gameStop = true;
}