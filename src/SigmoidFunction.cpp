#include "SigmoidFunction.h"

#include <stdexcept>
#include <math.h>

using namespace std;

double SigmoidFunction::euNum = 2.71828;

SigmoidFunction::SigmoidFunction (double numParam, double denomParam) :
    ActionPotentialFunction (), mNumParam (numParam), mDenomParam (denomParam)
{
    if (denomParam == 0)
        throw invalid_argument ("denomParam is 0!");
}

// 1 / 1 + e^x => a / b + e ^x, b =! 0
double SigmoidFunction::Do(double x)
{
    return mNumParam / (mDenomParam + pow (euNum, x));
}
