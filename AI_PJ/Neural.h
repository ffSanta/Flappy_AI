#pragma once
#include <math.h>
#include <stdlib.h>
#include <vector>
class Neural
{
	float sigmoidf(float y);

	void initWeight();
public:

	Neural();
	float float_rand();
	float forward(std::vector<float> input);
	std::vector<float> wInput;
	float bias;
};