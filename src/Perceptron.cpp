#include "Perceptron.h"
#include <cmath>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <iostream>

Perceptron::Perceptron(ActionPotentialFunction* func, int numberOfInputs, vector<int> numberOfNeurons)
	:FeFoNetwork(func, numberOfInputs, numberOfNeurons)
{
}

double Perceptron::Train(vector<double> input, vector<double> output)
{
	/*
	vector<double> accumulatedOutput = Accumulate(input);
	Layer layer = theLayers[0];

	double error = 0.0;
	const double learningRate = 0.1;

	for (int curNeuron = 0;  curNeuron < layer.getNumberOfNeurons(); curNeuron++)
	{
		double errorDelta = output[curNeuron] - accumulatedOutput[curNeuron];

		if (errorDelta != 0)
		{
			for (unsigned curInput = 0; curInput < layer[curNeuron].getNumberOfInputs(); curInput++)
			{
				const double temp = layer[curNeuron][curInput], changeCheck = learningRate * errorDelta * input[curInput];
				layer[curNeuron][curInput] += learningRate * errorDelta * input[curInput];
				assert (input[curInput] == 0 || temp == 0 || temp != layer[curNeuron][curInput]);
			}


			error += abs(errorDelta);
		}
	}*/

    const double learningRate = 0.1;
	vector <double> actOutput = Accumulate(input);

	cout << "inputs ";
    for_each (input.begin(), input.end(), [] (double err) {cout << err << ", "; });
    cout << endl;

    cout << "outputs ";
    for_each (actOutput.begin(), actOutput.end(), [] (double err) {cout << err << ", "; });
    cout << endl;

	actOutput.erase (actOutput.end() - 1);
	vector <double> errors (actOutput.size());
    for (auto iact = actOutput.begin(), iexp = output.begin(), ierr = errors.begin();
        iact != actOutput.end(); ++iact, ++iexp, ++ierr)
        *ierr = *iact - *iexp;


    cout << "errors ";
    for_each (errors.begin(), errors.end(), [] (double err) {cout << err << ", "; });
    cout << endl;

    cout << "input layer before " << endl;
    theLayers.front().dbgOut (cout);
    Layer& lastLay = theLayers.back();
    for (unsigned cErr = 0; cErr < errors.size(); ++cErr)
    {
        if (errors[cErr] != 0)
        {

            for (unsigned cWeights = 0; cWeights < lastLay.getNumberOfNeurons(); ++cWeights)
            {
                const double temp = lastLay[cErr][cWeights];
                lastLay[cErr][cWeights] += learningRate * errors[cErr] * inputLayer[cWeights].getOutput();
                assert (inputLayer[cWeights].getOutput() == 0 || temp == 0 || temp != lastLay[cErr][cWeights]);
            }
        }
    }
    cout << "input layer after " << endl;
    theLayers.front().dbgOut (cout);

    double error = accumulate (errors.begin(), errors.end(), 0, plus <double>());
	return error;

}
