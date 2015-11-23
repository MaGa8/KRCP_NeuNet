
#include "..\include\Perceptron.h"
#include "..\include\Neuron.h"
#include "..\include\Layer.h"
#include "..\include\StepFunction.h"
#include "..\include\SigmoidFunction.h"

Perceptron logicOrTest ()
{
    double threshold = 0;
    Perceptron orNN (StepFunction (threshold), 2, vector <int> ({2, 1}));

    vector <pair <vector <double>, vector <double>> samples;
    samples.push_back (make_pair ({0, 0}, {0}));
    samples.push_back (make_pair ({1, 0}, {1}));
    samples.push_back (make_pair ({0, 1}, {1}));
    samples.push_back (make_pair ({1, 1}, {1}));

    auto iTrainSample = samples.begin();
    while (iTrainSample != samples.end())
    {
        double error = 0;
        bool immediateMatch = true;
        do
        {
            error = orNN.Train (iTrainSample->first, iTrainSample->second);
            if (error != 0)
                immediateMatch = false;
        }while (error != 0);

        if (!immediateMatch)
            samples.insert (samples.end(), samples.begin(), iTrainSample);
        else
            ++iTrainSample;
    }
}

Perceptron logicAndTest ()
{

}

Perceptron linearFunctionTest ()
{

}

int main()
{


    return 0;
}
