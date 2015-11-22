#include "../include/Perceptron.h"
#include <cmath>

Perceptron::Perceptron(ActionPotentialFunction & func, int numberOfInputs, vector<int> numberOfNeurons)
	:FeFoNetwork(func, numberOfInputs, numberOfNeurons)
{
}

double Perceptron::Train(vector<double> input, vector<double> output)
{
	vector<double> accumulatedOutput = Accumulate(input);
	Layer layer = theLayers[0];


	double error = 0.0;
	const double learningRate = 0.1;

	for (int curNeuron = 0;  curNeuron < layer.getNumberOfNeurons(); curNeuron++)
	{
		double errorDelta = output[curNeuron] - accumulatedOutput[curNeuron];

		if (errorDelta != 0)
		{
			for (int curInput = 0; curInput < layer[curNeuron].getNumberOfInputs(); curInput++)
			{
				layer[curNeuron][curInput] += learningRate * errorDelta * input[curInput];
			}

			double threshold = layer[curNeuron].getThreshold();
			threshold += learningRate * errorDelta;
			layer[curNeuron].setThreshold(threshold);

			error += abs(errorDelta);
		}
	}

	return error;

}