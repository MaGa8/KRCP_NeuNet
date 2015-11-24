#include "Neuron.h"

#include <assert.h>
#include <iostream>
#include <algorithm>

double Neuron::INIT_EPSILON = 0.000000001;
bool Neuron::debugging = true;

Neuron::Neuron(const unsigned inputs, ActionPotentialFunction* func)
	: theWeights (inputs, 1), theActionPotentialFunc(func), theNumberOfInputs(inputs), theOutput((inputs == 0) ? 1 : 0)
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
	if (debugging)
    {
        cout << "Neuron input ";
        for_each (input.begin(), input.end(), [] (double out) {cout << out << ", ";});
        cout << endl;
        cout << "Neuron output ";
    }
	if (theNumberOfInputs == 0 && theActionPotentialFunc == nullptr)
    {
        if (debugging)
            cout << 1 << endl;
        return 1;
    }
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
        if (debugging)
            cout << theOutput << endl;
		return theOutput;
	}
	else
    {
        if (debugging)
            cout << -1 << endl;
        return -1;
    }
}
