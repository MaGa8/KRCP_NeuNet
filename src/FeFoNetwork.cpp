#include "..\include\FeFoNetwork.h"
#include <vector>
#include <fstream>

using namespace std;

FeFoNetwork::FeFoNetwork(ActionPotentialFunction & func, int numberOfInputs, vector<int> numberOfNeurons)
	: AbstractNetwork(numberOfInputs, numberOfNeurons.size())
{
	for (int i = 0; i < theNumberOfLayers; i++) {
		Layer layer(numberOfNeurons[i], (i == 0) ? numberOfInputs : numberOfNeurons[i - 1], func);
		theLayers.push_back(layer);
	}
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

    //TODO save activation function
}

void FeFoNetwork::LoadFromDisk()
{
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
}
