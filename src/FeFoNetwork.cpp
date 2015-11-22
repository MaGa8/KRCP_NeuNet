#include "..\include\FeFoNetwork.h"
#include <vector>

using namespace std;

FeFoNetwork::FeFoNetwork(ActionPotentialFunction & func, int numberOfInputs, vector<int> numberOfNeurons)
	: AbstractNetwork(numberOfInputs, numberOfNeurons.size())
{
	for (int i = 0; i < theNumberOfLayers; i++)
		Layer layer(numberOfNeurons[i], (i == 0) ? numberOfInputs : numberOfNeurons[i - 1], func);
}


vector<double>  FeFoNetwork::Accumulate(vector<double> input)
{
	theOutput = input;

	for (auto layer : theLayers)
	{
		theOutput = layer.Accumulate(theOutput);
	}

	return theOutput;
}

void FeFoNetwork::SaveToDisk()
{
	// TODO
}

void FeFoNetwork::LoadFromDisk()
{
	// TODO
}