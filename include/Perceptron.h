#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "FeFoNetwork.h"

#include <array>

class Perceptron : public FeFoNetwork
{
    public:
<<<<<<< HEAD
        Perceptron (const array <unsigned, 2>& neuronsPerLayer, const array <abstractActFunctor, 2>& activations);

        double compute(const vector <double>& inVec);
    protected:
    private:
=======
        Perceptron(ActionPotentialFunction & func, int numberOfInputs, vector<int> numberOfNeurons);
		virtual double Train(vector<double> input, vector<double> output);
>>>>>>> origin/master
};

#endif // PERCEPTRON_H
