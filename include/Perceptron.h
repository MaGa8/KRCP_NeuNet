#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <FeFoNetwork.h>

#include <array>

class Perceptron : public FeFoNetwork
{
    public:
        Perceptron (const array <unsigned, 2>& neuronsPerLayer, const array <abstractActFunctor, 2>& activations);

        double compute(const vector <double>& inVec);
    protected:
    private:
};

#endif // PERCEPTRON_H
