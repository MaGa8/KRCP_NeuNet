#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"
#include <ostream>

class Layer
{
    public:
        static bool debugging;

		Layer (int numberOfNeurons, int numberOfInputs, ActionPotentialFunction* func);
		virtual void Initialize();
		int getNumberOfInputs();
		int getNumberOfNeurons();
		vector<double> getOutput();
		Neuron& operator[](const size_t index);
		vector<double> Accumulate(vector<double> input);

		void dbgOut (ostream& str);

    protected:
		vector<Neuron> theNeurons;
		vector<double> theOutputs;
		int theNumberOfInputs;
		int theNumberOfNeurons;
};

#endif // LAYER_H
