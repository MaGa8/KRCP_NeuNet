#include "Neuron.h"

#include <assert.h>

double Neuron::INIT_EPSILON = 0.000000001;

Neuron::Neuron(const unsigned inputs, ActionPotentialFunction* func)
	: theWeights (inputs), theActionPotentialFunc(func), theNumberOfInputs(inputs), theOutput((inputs == 0) ? 1 : 0)
{}

Neuron::Neuron (const Neuron& copy) :
    theWeights (copy.theWeights),
    theActionPotentialFunc (copy.theActionPotentialFunc),
    theNumberOfInputs (copy.theNumberOfInputs),
    theOutput (copy.theOutput)
{

}

Neuron Neuron::operator = (const Neuron& copy)
{
    if (this != &copy)
    {
        theWeights = copy.theWeights;
        theActionPotentialFunc = copy.theActionPotentialFunc;
        theNumberOfInputs = copy.theNumberOfInputs;
        theOutput = copy.theOutput;
    }
    return *this;
}

void Neuron::Initialize()
{
	random_device randDevice;
	std::mt19937 generator(randDevice());
	std::uniform_real_distribution<double> distribution(INIT_EPSILON, 1);

	for (unsigned i = 0; i < getNumberOfInputs(); i++)
    {
        theWeights[i] = distribution(generator);
        assert (theWeights[i] != 0);
    }

}

unsigned Neuron::getNumberOfInputs() const
{
	return theNumberOfInputs;
}

double Neuron::getOutput() const
{
	return theOutput;
}

double& Neuron::operator[](const size_t index)
{
	return theWeights[index];
}
/*
double Neuron::getThreshold()
{
	return theThreshold;
}

void Neuron::setThreshold(double value)
{
	theThreshold = value;
}
*/
double Neuron::Accumulate(vector<double> input)
{
	if (theNumberOfInputs == 0 && theActionPotentialFunc == nullptr)
        return 1;
	else if (input.size() == getNumberOfInputs())
	{
		double sum = 0.0;

		for (unsigned i = 0; i < getNumberOfInputs(); i++)
		{
			sum += theWeights[i] * input[i];
		}
        /*
		sum += theThreshold;
        */

		theOutput = theActionPotentialFunc->Do(sum);

		return theOutput;
	}
	else
        return -1;
}
