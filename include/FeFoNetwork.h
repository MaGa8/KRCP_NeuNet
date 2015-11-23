#ifndef FEFONETWORK_H
#define FEFONETWORK_H

#include "AbstractNetwork.h"


class FeFoNetwork : public AbstractNetwork
{
    public:

		FeFoNetwork(ActionPotentialFunction & func, int numberOfInputs, vector<int> numberOfNeurons);
		virtual vector<double> Accumulate(vector<double> input);
		virtual double Train(vector<double> input, vector<double> output) = 0;

		virtual void SaveToDisk();
		virtual void LoadFromDisk();
};

#endif // FEFONETWORK_H
