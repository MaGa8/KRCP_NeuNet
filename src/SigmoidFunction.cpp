#include "..\include\SigmoidFunction.h"

#include <stdexcept>

SigmoidFunction::SignoidFuntion (double threshold, double numParam, double denomParam) :
    ActionPotentialFunction (threshold), mNumPara (numParam), mDenomParam (denomParam)
{
    if (denomParam == 0)
        throw invalid_argument ("denomParam is 0!");
}

double SigmoidFunction::Do(double x)
{
    if (x < getThreshold())
        return 0;
    return numParam / (denomParam + pow (euNum, x));
}
