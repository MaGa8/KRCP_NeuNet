
#include <iostream>
#include <algorithm>

#include "Perceptron.h"
#include "Neuron.h"
#include "Layer.h"
#include "StepFunction.h"
#include "SigmoidFunction.h"
#include "LinearFunction.h"

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

    orNN.trainAll (samples);

    vector <double> testResult = orNN.Accumulate(samples[1].first);
    for_each (testResult.begin(), testResult.end(), [] (double out) {cout << out << ", ";});
    cout << endl;
    cout << "training successful" << endl;
}

Perceptron logicAndTest ()
{
    StepFunction* pfunc = new StepFunction ();
    Perceptron andNN (pfunc, 2, vector <int> ({2, 1}));
    andNN.Initialize();

    vector <pair <vector <double>, vector <double>>> samples;
    samples.push_back (make_pair (vector <double> ({0, 0}), vector <double> ({0}) ));
    samples.push_back (make_pair (vector <double> ({1, 0}), vector <double> ({0}) ));
    samples.push_back (make_pair (vector <double> ({0, 1}), vector <double> ({0}) ));
    samples.push_back (make_pair (vector <double> ({1, 1}), vector <double> ({1}) ));

    andNN.trainAll (samples);

    vector <double> testResult = andNN.Accumulate(samples[1].first);
    for_each (testResult.begin(), testResult.end(), [] (double out) {cout << out << ", ";});
    cout << endl;
    cout << "training successful" << endl;
    delete pfunc;
}

Perceptron linearFunctionTest ()
{
    LinearFunction* pfunc = new LinearFunction();

    Perceptron linNN (pfunc, 1, vector <int> ({1, 1}));
    linNN.Initialize();

    //try 3x + 2;
    vector <Sample> samples;
    samples.push_back (make_pair (vector <double> ({1}), vector <double> ({5})));//x = 1
    samples.push_back (make_pair (vector <double> ({6}), vector <double> ({20})));//x = 6
    samples.push_back (make_pair (vector <double> ({-2}), vector <double> ({-4})));//x = -2

    linNN.trainAll (samples);

    cout << "training successful" << endl;
    delete pfunc;
}

int main()
{
    Neuron::debugging = false;
    Layer::debugging = false;
    FeFoNetwork::debugging = false;


    logicOrTest();

    //logicAndTest();

    linearFunctionTest();

    return 0;
}
