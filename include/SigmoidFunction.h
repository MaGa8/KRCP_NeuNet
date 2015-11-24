#include "ActionPotentialFunction.h"

class SigmoidFunction : public ActionPotentialFunction
{
	public:
	    static double euNum;

	    //f(x) = numParam / (denomParam + e^x)
	    SigmoidFunction (double numParam, double denomParam);

		virtual double Do(double x);

    private:
        double mNumParam, mDenomParam;
};
