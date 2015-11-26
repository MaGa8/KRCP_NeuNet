#ifndef INPUTLAYER_H
#define INPUTLAYER_H

#include <Layer.h>
#include "LinearFunction.h"


class InputLayer : public Layer
{
    public:
        InputLayer (int numberOfNeurons, ActionPotentialFunction* func);

        vector <double> Accumulate(vector<double> input);
    protected:
    private:
		LinearFunction theLinearFunction;
};

#endif // INPUTLAYER_H
