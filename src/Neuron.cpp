#include "..\include\Neuron.h"

Neuron::Neuron(const int inputs, ActionPotentialFunction & func)
	: theNumberOfInputs(inputs), theThreshold(0), theOutput(0), theActionPotentialFunc(&func)
{}

void Neuron::Initialize()
{
	random_device randDevice;
	std::mt19937 generator(randDevice());
	std::uniform_real_distribution<double> distribution(0.0, 1);

	for (int i = 0; i < getNumberOfInputs(); i++)
		theWeights[i] = distribution(generator);
}

int Neuron::getNumberOfInputs()
{
	return theNumberOfInputs;
}

double Neuron::getOutput()
{
	return theOutput;
}

double& Neuron::operator[](const size_t index)
{
	return theWeights[index];
}

double Neuron::getThreshold()
{
	return theThreshold;
}

void Neuron::setThreshold(double value)
{
	theThreshold = value;
}

double Neuron::Accumulate(vector<double> input)
{
	if (input.size() == getNumberOfInputs())
	{
		double sum = 0.0;

		for (int i = 0; i < getNumberOfInputs(); i++)
		{
			sum += theWeights[i] * input[i];
		}

		sum += theThreshold;

		theOutput = theActionPotentialFunc->Do(sum);

		return theOutput;
	}
}