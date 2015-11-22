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
			Neuron perceptron = layer[curNeuron];

			for (int curInput = 0; curInput < perceptron.getNumberOfInputs(); curInput++)
			{
				perceptron[curInput] += learningRate * errorDelta * input[curInput];
			}

			double threshold = perceptron.getThreshold();
			threshold += learningRate * errorDelta;
			perceptron.setThreshold(threshold);

			error += abs(errorDelta);
		}
	}

	return error;

}