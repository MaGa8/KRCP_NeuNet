#include "StepFunction.h"

StepFunction::StepFunction (double threshold) : ActionPotentialFunction (threshold) {}

double StepFunction::Do (double x)
{
    if (x < getThreshold())
        return 0;
    return 1;
}
