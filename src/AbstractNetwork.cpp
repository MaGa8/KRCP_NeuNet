#include "..\include\AbstractNetwork.h"

/*
Sample::Sample(const vector <int>& inVals, const vector <int>& outVals)
{

}

vector::const_iterator Sample::iterIn() const
{

}

vector::const_iterator Sample::iterOut() const
{

}

AbstractNetwork::AbstractNetwork (const vector <unsigned>& neuronsPerLayer, const vector <abstractActFunctor>& activations) :

//public
int AbstractNetwork::compute(const vector <double>& inVec) const
{

}

void AbstractNetwork::train(const vector <vector <double>> samples)
{

}

//protected
void AbstractNetwork::train_sample(const vector <double>& sample)
{

}

//private
void AbstractNetwork::createInputLayer(const unsigned noNeurons, const abstractActFunctor& actFunctor)
{

}

void AbstractNetwork::createHiddenLayer(const unsigned noNeurons, const abstractActFunctor& actFunctor, const AbstractLayer& prevLayer)
{

}

void AbstractNetwork::createOutputLayer(const unsigned noNeurons, const abstractActFunctor& actFunctor, const AbstractLayer& prevLay)
{

}
*/
AbstractNetwork::AbstractNetwork(int inputsCount, int layersCount)
	: theNumberOfInputs(inputsCount), theNumberOfLayers(layersCount)
{}


void AbstractNetwork::Initialize()
{
	for (auto layer : theLayers)
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
>>>>>>> origin/master
}

vector<double>  AbstractNetwork::getOutput()
{
	return theOutput;
}

Layer&  AbstractNetwork::operator[](const size_t index)
{
	return theLayers[index];
}


