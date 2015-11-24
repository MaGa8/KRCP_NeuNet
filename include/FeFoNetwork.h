#ifndef FEFONETWORK_H
#define FEFONETWORK_H

#include "AbstractNetwork.h"


class FeFoNetwork : public AbstractNetwork
{
    public:
        static bool debugging;


		FeFoNetwork(ActionPotentialFunction* func, int numberOfInputs, vector<int> numberOfNeurons);
		virtual vector<double> Accumulate(vector<double> input);
		virtual double Train(vector<double> input, vector<double> output) = 0;

		virtual void SaveToDisk();
		virtual void LoadFromDisk();

    protected:
		InputLayer inputLayer;

    private:

};

#endif // FEFONETWORK_H
