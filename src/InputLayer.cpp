#include "InputLayer.h"

InputLayer::InputLayer(int numberOfNeurons, ActionPotentialFunction* func) : Layer (numberOfNeurons, 1, func)
{}

vector <double> InputLayer::Accumulate(vector<double> input)
{
    for (int i = 0; i < getNumberOfNeurons(); i++)
		theOutputs[i] = theNeurons[i].Accumulate(vector <double> ({input[i]}));

	return theOutputs;
}

