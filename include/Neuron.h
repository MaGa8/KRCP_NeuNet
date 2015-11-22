#ifndef NEURON_H
#define NEURON_H

#include "..\include\ActionPotentialFunction.h"
#include <memory>
#include <random>
#include <vector>

using namespace std;

class Neuron
{
    public:
		Neuron(const int inputs, ActionPotentialFunction& func);
		void Initialize();
		int getNumberOfInputs();
		double getOutput();
		double& operator[](const size_t index);
		double Accumulate(vector<double> input);
		double getThreshold();
		void setThreshold(double value);

    protected:
		vector<double> theWeights;
		ActionPotentialFunction * theActionPotentialFunc;
		int theNumberOfInputs;
		double theOutput;
		double theThreshold;
};

#endif // NEURON_H
