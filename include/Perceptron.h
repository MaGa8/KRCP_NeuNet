#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "FeFoNetwork.h"


class Perceptron : public FeFoNetwork
{
    public:
        Perceptron(ActionPotentialFunction & func, int numberOfInputs, vector<int> numberOfNeurons);
		virtual double Train(vector<double> input, vector<double> output);
};

#endif // PERCEPTRON_H
