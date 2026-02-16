#include "Neural.h"
#include <iostream>
float Neural::sigmoidf(float y)
{
	return 1 / (1 + expf(y));
}

float Neural::float_rand()
{
	return (float)rand() / RAND_MAX; //create between 0 to 1;
}

float Neural::forward(std::vector<float> input)
{
	float sum = 0;
	for (int i = 0; i < input.size(); i++)
	{
		sum += input[i] * wInput[i];
	}
	return sigmoidf(sum);
}

void Neural::initWeight()
{
	wInput.resize(3);
	for (int i = 0 ; i < wInput.size() ; i++)
	{
		wInput[i] = float_rand();
		std::cout << "Random Weight " << i << " : "  << wInput[i] << std::endl;
	}
	bias = float_rand();
	std::cout << "bias : " << bias << "\n" << "----------------------------------\n" ;
}

Neural::Neural()
{
	initWeight();
}
