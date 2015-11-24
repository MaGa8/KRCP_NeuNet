#ifndef LINEARFUNCTION_H
#define LINEARFUNCTION_H

#include <ActionPotentialFunction.h>


class LinearFunction : public ActionPotentialFunction
{
    public:
    LinearFunction();

    double Do(double x);

};

#endif // LINEARFUNCTION_H
