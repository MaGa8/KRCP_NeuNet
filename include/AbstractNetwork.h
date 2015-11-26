#ifndef ABSTRACTNETWORK_H
#define ABSTRACTNETWORK_H

#include "Layer.h"
#include "InputLayer.h"

class AbstractNetwork
{
    public:
		AbstractNetwork(int inputsCount, int layersCount);
		virtual void Initialize();
		int getNumberOfInputs();
		int getNumberOfLayers();
		vector<double> getOutput();
		Layer& operator[](const size_t index);
		virtual void dbgOut (ostream& out);

		virtual vector<double> Accumulate(vector<double> input) = 0;
		virtual double Train(vector<double> input, vector<double> output) = 0;
		virtual void SaveToDisk() = 0;
		virtual void LoadFromDisk() = 0;

	protected:
		vector<Layer> theLayers;
		vector<double> theOutput;
		int theNumberOfInputs;
		int theNumberOfLayers;
};

#endif // ABSTRACTNETWORK_H
