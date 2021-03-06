
#include <iostream>
#include <algorithm>
#include <thread>

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

    /*vector <double> testResult = andNN.Accumulate(samples[1].first);
    for_each (testResult.begin(), testResult.end(), [] (double out) {cout << out << ", ";});
    cout << endl;*/
    cout << "training successful" << endl;
    cout << "State of network" << endl;
    andNN.dbgOut(cout);

    return andNN;
}

void linearFunctionTest ()
{
/*
    StepFunction linActFun = StepFunction();
    NNTester tester (&linActFun, 2, vector <int> ({2, 1}));

    NNTester::RandLinSamGen randSamples (2, 1, 1, make_pair (-100, 100));
    cout << "training..." << endl;
    tester.trainIncreasing (1, 10, 0, &randSamples, false);
    cout << "verifying" << endl;
    randSamples.setDelta (100);

    NNTester::addInfo = false;
    tester.verify (10, &randSamples);

    tester.printNet();
*/
    StepFunction ActFun;
    Perceptron ptron (&ActFun, 2, vector <int> ({2, 1}));
    ptron.Initialize();
    vector <Sample> samples;
    samples.push_back (make_pair (vector <double> ({1, 3.5}), vector <double> ({1})));
    samples.push_back (make_pair (vector <double> ({1, 2.5}), vector <double> ({0})));
	samples.push_back(make_pair(vector <double>({2, 6 }), vector <double>({ 1 })));
	samples.push_back(make_pair(vector <double>({2, 1 }), vector <double>({ 0 })));
    /*samples.push_back (make_pair (vector <double> ({5, 11.25}), vector <double> ({1})));
    samples.push_back (make_pair (vector <double> ({5, 10.75}), vector <double> ({0})));
    samples.push_back (make_pair (vector <double> ({-3, -4.75}), vector <double> ({1})));
    samples.push_back (make_pair (vector <double> ({-3, -5.25}), vector <double> ({0})));*/

    ptron.trainAll (samples);
    ptron.dbgOut (cout);
}

void randGenTest()
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

void homGenTest()
{
    NNTester::PartLinSamGen test (2, 1, 10, make_pair (-100, 100), 5);
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

void nnTesterTest()
{
    StepFunction step;
    NNTester test (&step, 2, vector <int> ({2, 1}));
    NNTester::RandLinSamGen samGen (2, 1, 10, make_pair (-1000, 1000));
    test.trainIncreasing(5, 3, 10, &samGen);

    test.verify(100, &samGen);
}

void bigLinTest (unsigned totSamples, unsigned minIts, unsigned maxIts, unsigned deltaIts, double testDelta, double trainDelta, pair <double, double> testLims, pair <double, double> trainLims, unsigned testSamples)
{
    double a = 2, b = 1;

    //shifts balance between iterations <-> samples per iteration
    for (unsigned noIts = minIts; noIts <= maxIts; noIts += deltaIts)
    {
        //unsigned noIts = steps * cBal;
        unsigned noSams = totSamples / noIts;

        NNTester::RandLinSamGen randSamGenNonIncr (a, b, trainDelta, trainLims);
        NNTester::RandLinSamGen randSamGenIncr (a, b, trainDelta / noIts, trainLims);
        NNTester::RandLinSamGen randSamGenCombI (a, b, trainDelta / noIts, trainLims);
        NNTester::RandLinSamGen randSamGenCombR (a, b, trainDelta, trainLims);
        NNTester::PartLinSamGen homSamGenNonIncr (a, b, trainDelta, trainLims, (unsigned)(noSams / 2));
        NNTester::PartLinSamGen homSamGenIncr (a, b, trainDelta / noIts, trainLims, (unsigned)(noSams / 2));
        NNTester::PartLinSamGen homSamGenCombI (a, b, trainDelta / noIts, trainLims, (unsigned)(noSams / 2));
        NNTester::PartLinSamGen homSamGenCombR (a, b, trainDelta, trainLims, (unsigned)(noSams / 2));

        StepFunction actFun;

        NNTester tRandInRand (&actFun, 2, vector <int> ({2, 1}));
        NNTester tIncrInRand (&actFun, 2, vector <int> ({2, 1}));
        NNTester tCombInRand (&actFun, 2, vector <int> ({2, 1}));
        NNTester tRandInHom (&actFun, 2, vector <int> ({2, 1}));
        NNTester tIncrInHom (&actFun, 2, vector <int> ({2, 1}));
        NNTester tCombInHom (&actFun, 2, vector <int> ({2, 1}));

        /*
        //test random trainer with random input
        thread trr (&NNTester::trainRandom, tRandInRand, noIts, noSams, &randSamGenNonIncr);
        //test increasing trainer with random input
        thread tir (&NNTester::trainIncreasing, tIncrInRand, noIts, noSams, randSamGenIncr.getDelta(), &randSamGenIncr);
        //test increasing trainer and random trainer subsequently with random input
        thread tcr (&NNTester::trainCombo, tCombInRand, noIts, noSams, randSamGenCombI.getDelta(), &randSamGenCombI, &randSamGenCombR);
        //test random trainer with homogeneous input
        thread trh (&NNTester::trainRandom, tRandInHom, noIts, noSams, &homSamGenNonIncr);
        //test increasing trainer with homogeneous input
        thread tih (&NNTester::trainIncreasing, tIncrInHom, noIts, noSams, homSamGenIncr.getDelta(), &homSamGenIncr);
        //test increasing trainer and random trainer subsequently with homogeneous input
        thread tch (&NNTester::trainCombo, tCombInHom, noIts, noSams, homSamGenCombI.getDelta(), &homSamGenCombI, &homSamGenCombR);
        */

        //test random trainer with random input
        tRandInRand.trainRandom (noIts, noSams, &randSamGenNonIncr);
        //test increasing trainer with random input
        tIncrInRand.trainIncreasing (noIts, noSams, randSamGenIncr.getDelta(), &randSamGenIncr);
        //test increasing trainer and random trainer subsequently with random input
        tCombInRand.trainCombo (noIts, noSams, randSamGenCombI.getDelta(), &randSamGenCombI, &randSamGenCombR);
        //test random trainer with homogeneous input
        tRandInHom.trainRandom (noIts, noSams, &homSamGenNonIncr);
        //test increasing trainer with homogeneous input
        tIncrInHom.trainIncreasing (noIts, noSams, homSamGenIncr.getDelta(), &homSamGenIncr);
        //test increasing trainer and random trainer subsequently with homogeneous input
        tCombInHom.trainCombo (noIts, noSams, homSamGenCombI.getDelta(), &homSamGenCombI, &homSamGenCombR);


        NNTester::addInfo = false;
        NNTester::RandLinSamGen verGen (a, b, testDelta, testLims);
        cout << "iterations " << noIts << " samples per iteration " << noSams << endl;
        cout << "result random trainer with random input" << endl;
        double rrratio = tRandInRand.verify (testSamples, &verGen);
        cout << rrratio << endl;
        cout << "result increasing trainer with random input" << endl;
        double irratio = tIncrInRand.verify (testSamples, &verGen);
        cout << irratio << endl;
        cout << "result combined trainer with random input" << endl;
        double crratio = tCombInRand.verify (testSamples, &verGen);
        cout << crratio << endl;
        cout << "result random trainer with homogeneous input" << endl;
        double hrratio = tRandInHom.verify (testSamples, &verGen);
        cout << hrratio << endl;
        cout << "result increasing trainer with homogeneous input" << endl;
        double hiratio = tIncrInHom.verify (testSamples, &verGen);
        cout << hiratio << endl;
        cout << "result combined trainer with homogeneous input" << endl;
        double hcratio = tCombInHom.verify (testSamples, &verGen);
        cout << hcratio << endl;
    }
}

void launchbigTest ()
{
    size_t numSamples = 5000, minIters = 1, maxIters = 10, deltaIters = 1, testSamples = 250;
    pair <double, double> trainLim (-100, 100), testLim (-10000, 10000), trainDeltas (10, 100);
    double testDelta = 1000, addDelta = 9;

    for (double cDelta = trainDeltas.first; cDelta <= trainDeltas.second; cDelta += addDelta)
    {
        cout << "Training delta " << cDelta << endl;
        bigLinTest (numSamples, minIters, maxIters, deltaIters, testDelta, cDelta, testLim, trainLim, testSamples);
        cout << endl;
    }
}

int main()
{
    Neuron::debugging = false;
    Layer::debugging = false;
    FeFoNetwork::debugging = false;
    NNTester::addInfo = true;


    //logicOrTest();

    //logicAndTest();

    //linearFunctionTest();

    //randGenTest();
    //homGenTest();


    NNTester::debugging = true;
    nnTesterTest();




    return 0;
}
