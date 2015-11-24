#include "LinearFunction.h"
#include <math.h>

LinearFunction::LinearFunction() : ActionPotentialFunction()
{

}

double LinearFunction::Do(double x)
{
    return round (x);
}
