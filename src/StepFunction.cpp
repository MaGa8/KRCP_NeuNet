#include "StepFunction.h"

StepFunction::StepFunction () : ActionPotentialFunction () {}

double StepFunction::Do (double x)
{
    return ((x <= 0) ? 0 : 1);
}
