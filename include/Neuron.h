#ifndef NEURON_H
#define NEURON_H

#include "ActionPotentialFunction.h"
#include <memory>
#include <random>
#include <vector>

using namespace std;

class Neuron
{
    public:
        static double INIT_EPSILON;

		Neuron (const unsigned inputs, ActionPotentialFunction* func);
		Neuron (const Neuron& copy);

		Neuron operator = (const Neuron& copy);

		void Initialize();
		unsigned getNumberOfInputs() const;
		double getOutput() const;
		double& operator[](const size_t index);
		double Accumulate(vector<double> input);
		/*
		double getThreshold();
		void setThreshold(double value);
        */
    protected:
		vector<double> theWeights;
		ActionPotentialFunction* theActionPotentialFunc;
		unsigned theNumberOfInputs;
		double theOutput;
		//double theThreshold;
};

#endif // NEURON_H
