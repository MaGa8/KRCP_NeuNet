#ifndef STEPFUNCTION_H
#define STEPFUNCTION_H

#include <ActionPotentialFunction.h>


class StepFunction : public ActionPotentialFunction
{
    public:
        StepFunction (double threshold);

        double Do (double x);
    protected:
    private:
};

#endif // STEPFUNCTION_H
