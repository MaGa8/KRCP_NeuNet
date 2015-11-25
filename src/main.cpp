
#include <iostream>
#include <algorithm>

#include "Perceptron.h"
#include "Neuron.h"
#include "Layer.h"
#include "StepFunction.h"
#include "SigmoidFunction.h"
#include "LinearFunction.h"
#include "NNTester.h"

using namespace std;

Perceptron logicOrTest ()
{
    StepFunction pfunc;
    Perceptron orNN (&pfunc, 2, vector <int> ({2, 1}));
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

    return orNN;
}

Perceptron logicAndTest ()
{
    StepFunction pfunc;
    Perceptron andNN (&pfunc, 2, vector <int> ({2, 1}));
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

    return andNN;
}

void linearFunctionTest ()
{
    NNTester::addInfo = true;

    StepFunction linActFun = StepFunction();
    NNTester tester (&linActFun, 2, vector <int> ({2, 1}));

    NNTester::RandLinSamGen randSamples (2, 1, 1, make_pair (-10000, 10000));
    cout << "training..." << endl;
    tester.trainIncreasing (250, 500, 2, &randSamples);
    cout << "verifying" << endl;
    randSamples.setDelta (100);
    tester.verify (1000, &randSamples);
}

void genTest()
{
    NNTester::RandLinSamGen test (2, 1, 10, make_pair (-100, 100));
    vector <Sample> sams (10);
    generate (sams.begin(), sams.end(), test);
    for (auto& sam : sams)
    {
        cout << "input ";
        for_each (sam.first.begin(), sam.first.end(), [] (double i) {cout << i << " "; });
        cout << endl;
        cout << "output ";
        for_each (sam.second.begin(), sam.second.end(), [] (double i) {cout << i << " "; });
        cout << endl;
    }
}

int main()
{
    Neuron::debugging = false;
    Layer::debugging = false;
    FeFoNetwork::debugging = false;


    //logicOrTest();

    //logicAndTest();

    linearFunctionTest();

    //genTest();

    return 0;
}
