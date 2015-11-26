#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "FeFoNetwork.h"

#include <array>

typedef pair <vector <double>, vector <double>> Sample;

class Perceptron : public FeFoNetwork
{
    public:


        Perceptron(ActionPotentialFunction* func, int numberOfInputs, vector<int> numberOfNeurons);
		virtual double Train(vector<double> input, vector<double> output);

		void trainAll (vector <Sample> samples);

		void trainFast (vector <Sample> sampes);
};

#endif // PERCEPTRON_H
