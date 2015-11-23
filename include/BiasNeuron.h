#ifndef BIASNEURON_H
#define BIASNEURON_H

#include <Neuron.h>


class BiasNeuron : public Neuron
{
    public:
		BiasNeuron();
		void Initialize();
		int getNumberOfInputs();
		double getOutput();
    protected:
    private:
        double& operator[](const size_t index);
		double Accumulate(vector<double> input);
		double getThreshold();
		void setThreshold(double value);
};

#endif // BIASNEURON_H
