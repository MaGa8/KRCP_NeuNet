#include "AbstractNetwork.h"


AbstractNetwork::AbstractNetwork(int inputsCount, int layersCount)
	: theNumberOfInputs(inputsCount), theNumberOfLayers(layersCount)
{}

void AbstractNetwork::Initialize()
{
	for (auto& layer : theLayers)
	{
		layer.Initialize();
	}
}

int  AbstractNetwork::getNumberOfInputs()
{
	return theNumberOfInputs;
}

int  AbstractNetwork::getNumberOfLayers()
{
	return theNumberOfLayers;
}

vector<double>  AbstractNetwork::getOutput()
{
	return theOutput;
}

Layer&  AbstractNetwork::operator[](const size_t index)
{
	return theLayers[index];
}


