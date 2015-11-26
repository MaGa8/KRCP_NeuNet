#include "Layer.h"

#include <iostream>
#include <algorithm>
#include <assert.h>

bool Layer::debugging = true;

Layer::Layer(int numberOfNeurons, int numberOfInputs, ActionPotentialFunction* func)
	: theOutputs (numberOfNeurons + 1), theNumberOfInputs(numberOfInputs), theNumberOfNeurons (numberOfNeurons)
{
	for (int i = 0; i < theNumberOfNeurons; i++)
	{
		Neuron neuron(theNumberOfInputs, func);
		theNeurons.push_back(neuron);
	}
	++theNumberOfNeurons;
	theNeurons.push_back (Neuron (0, nullptr));
}

void Layer::Initialize()
{
	for (auto& neuron : theNeurons)
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
    if (debugging)
    {
        cout << "Layer input ";
        for_each (input.begin(), input.end(), [] (double out) {cout << out << ", ";});
        cout << endl;
    }
	assert (input.size() == getNumberOfInputs());
	for (int i = 0; i < getNumberOfNeurons(); i++)
		theOutputs[i] = theNeurons[i].Accumulate(input);
    if (debugging)
    {
        cout << "Layer output ";
        for_each (theOutputs.begin(), theOutputs.end(), [] (double out) {cout << out << ", ";});
        cout << endl;
    }

	return theOutputs;
}

void Layer::dbgOut (ostream& str)
{
    for (auto iNeu = theNeurons.begin(); iNeu != theNeurons.end(); ++iNeu)
    {
        str << "Neuron " << distance (theNeurons.begin(), iNeu) << "; weights ";
        for (unsigned cwei = 0; cwei < iNeu->getNumberOfInputs(); ++cwei)
            str << (*iNeu)[cwei] << " ";
        str << " => output " << iNeu->getOutput() << endl;
    }
}
