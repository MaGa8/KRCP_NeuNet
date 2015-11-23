#ifndef ACTIONPOTENTIALFUNCTION_H
#define ACTIONPOTENTIALFUNCTION_H

class ActionPotentialFunction
{
	public:
	    ActionPotentialFunction (double threshold);

	    double getThreshold();

		virtual double Do(double x) = 0;

    private:
        double mThreshold;
};

#endif // ACTIONPOTENTIALFUNCTION_H
