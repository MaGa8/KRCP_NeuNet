#include "InputLayer.h"
#include <iostream>
#include <algorithm>

InputLayer::InputLayer(int numberOfNeurons, ActionPotentialFunction* func) : Layer (numberOfNeurons, 1, &theLinearFunction)
{}

vector <double> InputLayer::Accumulate(vector<double> input)
{
    if (debugging)
    {
        cout << "Layer input ";
        for_each (input.begin(), input.end(), [] (double out) {cout << out << ", ";});
        cout << endl;
    }

    for (int i = 0; i < getNumberOfNeurons() - 1; i++)
		theOutputs[i] = theNeurons[i].Accumulate(vector <double> ({input[i]}));
    theOutputs.back() = theNeurons.back().Accumulate (vector <double>());

    if (debugging)
    {
        cout << "Layer output ";
        for_each (theOutputs.begin(), theOutputs.end(), [] (double out) {cout << out << ", ";});
        cout << endl;
    }

	return theOutputs;
}

