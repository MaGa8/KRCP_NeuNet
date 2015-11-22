#include "..\include\Layer.h"

Layer::Layer(int numberOfNeurons, int numberOfInputs, ActionPotentialFunction & func)
	: theNumberOfNeurons(numberOfNeurons),
	theNumberOfInputs(numberOfInputs)
{
	for (int i = 0; i < theNumberOfNeurons; i++)
	{
		Neuron neuron(theNumberOfInputs, func);
		theNeurons.push_back(neuron);
	}
}

void Layer::Initialize()
{
	for (auto neuron : theNeurons)
		neuron.Initialize();
}

int Layer::getNumberOfInputs()
{
	return theNumberOfInputs;
}

int Layer::getNumberOfNeurons()
{
	return theNumberOfNeurons;
}

vector<double> Layer::getOutput()
{
	return theOutputs;
}

Neuron& Layer::operator[](const size_t index)
{
	return theNeurons[index];
}

vector<double> Layer::Accumulate(vector<double> input)
{
	for (int i = 0; i < getNumberOfNeurons(); i++)
		theOutputs[i] = theNeurons[i].Accumulate(input);

	return theOutputs;
}
