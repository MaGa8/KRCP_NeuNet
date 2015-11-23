#include "ActionPotentialFunction.h"

class SigmoidFunction : public ActionPotentialFunction
{
	public:
	    static double euNum = 2.71828;

	    //f(x) = numParam / (denomParam + e^x)
	    SigmoidFunction (double threshold, double numParam, double denomParam);

		virtual double Do(double x);

    private:
        double mNumParam, mDenomParam;
};
