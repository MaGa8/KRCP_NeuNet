#include "FeFoNetwork.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

bool FeFoNetwork::debugging = true;

FeFoNetwork::FeFoNetwork(ActionPotentialFunction* func, int numberOfInputs, vector<int> numberOfNeurons)
	: AbstractNetwork(numberOfInputs, numberOfNeurons.size()), inputLayer (numberOfNeurons[0], func)
{
	for (int i = 1; i < theNumberOfLayers; i++) {
        unsigned passedNumberConnections = (theLayers.empty() ? inputLayer.getNumberOfNeurons() : theLayers.back().getNumberOfNeurons());
		Layer layer (numberOfNeurons[i], (theLayers.empty()) ? inputLayer.getNumberOfNeurons() : theLayers.back().getNumberOfNeurons(), func);
		//Layer layer(numberOfNeurons[i], (i == 0) ? numberOfInputs : numberOfNeurons[i - 1], func);
		theLayers.push_back(layer);
	}
}


vector<double>  FeFoNetwork::Accumulate(vector<double> input)
{
	if (debugging)
    {
        cout << "Network input ";
        for_each (input.begin(), input.end(), [] (double out) {cout << out << ", ";});
        cout << endl;
        cout << "Network accumulate - input level" << endl;
    }
	theOutput = inputLayer.Accumulate(input);
    if (debugging)
        cout << "Network accumulate - rest" << endl;
	for (auto& layer : theLayers)
	{
		theOutput = layer.Accumulate(theOutput);
	}
	if (debugging)
    {
        cout << "Network output ";
        for_each (theOutput.begin(), theOutput.end(), [] (double out) {cout << out << ", ";});
        cout << endl;
    }
    return theOutput;
}

void FeFoNetwork::SaveToDisk()
{
    /*
	string somePath = "blablabla.txt";
	ofstream writer (somePath.c_str());

	for (Layer singleLayer : theLayers)
    {

        for (unsigned cNeuron = 0; cNeuron < singleLayer.getNumberOfNeurons(); ++cNeuron)
        {

            const Neuron& singleNeuron = singleLayer[cNeuron];
            for (unsigned cWeight = 0; cWeight < singleNeuron.getNumberOfInputs(); ++cWeight)
                writer << singleNeuron[cWeight] << " ";
            writer << "END_NEURON ";
        }
        writer << "END_LAYER" << endl;
    }
    writer.close();
    */
    //TODO save activation function
}

void FeFoNetwork::LoadFromDisk()
{
	/*
	String somePath = "blablabla.txt";
	ifstrem reader (somePath.c_str());

	vector <Layer> layers;
	vector <Neuron> neurons;
	vector <double> connectVals;
	while (reader.good())
    {
        string in << reader;
        if (in == "END_LAYER")
        {
            layers.push_back (Layer (neurons));
            neurons.clear();
        }
        else if (in == "END_NEURON")
        {
            neurons.push_back (Neuron (connectVals));
            connectVals.clear();
        }
        else
            connectVals.push_back (stod (in));
    }
    FeFoNetwork (layers);
    */
}
