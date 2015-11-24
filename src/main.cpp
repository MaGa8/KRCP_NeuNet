
#include <iostream>
#include <algorithm>

#include "Perceptron.h"
#include "Neuron.h"
#include "Layer.h"
#include "StepFunction.h"
#include "SigmoidFunction.h"

using namespace std;

Perceptron logicOrTest ()
{
    StepFunction* pfunc = new StepFunction ();
    Perceptron orNN (pfunc, 2, vector <int> ({2, 1}));
    orNN.Initialize();

    vector <pair <vector <double>, vector <double>>> samples;
    samples.push_back (make_pair (vector <double> ({0, 0}), vector <double> ({0}) ));
    samples.push_back (make_pair (vector <double> ({1, 0}), vector <double> ({1}) ));
    samples.push_back (make_pair (vector <double> ({0, 1}), vector <double> ({1}) ));
    samples.push_back (make_pair (vector <double> ({1, 1}), vector <double> ({1}) ));

    auto iTrainSample = samples.begin();
    while (iTrainSample != samples.end())
    {
        double error = 0;
        bool immediateMatch = true;
        do
        {
            cout << "Train sample " << distance (samples.begin(), iTrainSample) << endl;
            error = orNN.Train (iTrainSample->first, iTrainSample->second);
            if (error != 0)
                immediateMatch = false;
        }while (error != 0);

        if (!immediateMatch)
            samples.insert (samples.end(), samples.begin(), iTrainSample);
        else
            ++iTrainSample;
    }

    vector <double> testResult = orNN.Accumulate(samples[1].first);
    for_each (testResult.begin(), testResult.end(), [] (double out) {cout << out << ", ";});
    cout << endl;
}

Perceptron logicAndTest ()
{

}

Perceptron linearFunctionTest ()
{

}

int main()
{
    logicOrTest();

    return 0;
}
