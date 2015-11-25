
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

    delete pfunc;
    return orNN;
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

    return andNN;
}

Perceptron linearFunctionTest ()
{
    class LinFunNumberGen
    {
        /*random_device randDevice;
	std::mt19937 generator(randDevice());
	std::uniform_real_distribution<double> distribution(INIT_EPSILON, 1);*/
    public:

        LinFunNumberGen (double a, double b, double x1, double x2, double delta) :
            ma (a), mb (b), mx1 (x1), mx2 (x2), mdelta (delta), mGen (random_device()()), mDist (mx1, mx2) {}

        Sample operator () (Sample sam)
        {
            double randX = mDist (mGen);
            uniform_real_distribution <double> yDist (ma * randX + mb - mdelta, ma * randX + mb + mdelta);
            double randY = yDist (mGen);
/*
            cout << "get random x value within " << mx1 << " " << mx2 << endl;
            cout << "get random y value within " << (ma * randX + mb - mdelta) << " " << (ma * randX + mb + mdelta) << endl;
            cout << "selected " << randX << " " << randY << " " << ((double)(ma * randX + mb > randY)) << endl;*/
            return make_pair (vector <double> ({randX, randY}), vector <double> ({(double)(ma * randX + mb > randY)}));
            //true if larger
        }

    private:
        double ma, mb, mx1, mx2, mdelta;
        mt19937 mGen;
        uniform_real_distribution <double> mDist;
    };

    StepFunction* pfunc = new StepFunction();

    Perceptron linNN (pfunc, 1, vector <int> ({2, 1}));
    linNN.Initialize();

    //try 3x + 2;
    size_t numSamples = 1000, iterations = 9990, deltaDiff = 5;
    double maxDelta = 100;
/*
    for (int cIter = 0; cIter < iterations; ++cIter)
    {
        vector <Sample> samples (numSamples);
        transform (samples.begin(), samples.end(), samples.begin(), LinFunNumberGen (2, 1, -25, 25, 1 + cIter * deltaDiff));
        linNN.trainFast(samples);
    }
*/
    random_device randDevice;
    mt19937 gener (randDevice());
    uniform_real_distribution <double> randDeltaDist (-maxDelta, maxDelta);
    for (int cIter = 0; cIter < iterations; ++cIter)
    {
        vector <Sample> samples (numSamples);
        transform (samples.begin(), samples.end(), samples.begin(), LinFunNumberGen (2, 1, -25, 25, randDeltaDist (gener)));
        linNN.trainFast(samples);
    }

    //linNN.trainAll (samples);


    size_t numCheckSamples = 10;
    vector <Sample> checkSamples (numCheckSamples);
    transform (checkSamples.begin(), checkSamples.end(), checkSamples.begin(), LinFunNumberGen (2, 1, -100, 100, 1));
    for (Sample check : checkSamples)
    {
        vector <double> out = linNN.Accumulate(check.first);

        cout << "input ";
        for_each (check.first.begin(), check.first.end(), [] (double val) {cout << val << ", "; });
        cout << endl;
        cout << "output ";
        for_each (out.begin(), out.end(), [] (double val) {cout << val << ", "; });
        cout << endl;
        cout << "expected output ";
        for_each (check.second.begin(), check.second.end(), [] (double val) {cout << val << ", "; });
        cout << endl;
    }

    cout << "training successful" << endl;
    delete pfunc;

    return linNN;
}

int main()
{
    Neuron::debugging = false;
    Layer::debugging = false;
    FeFoNetwork::debugging = false;


    //logicOrTest();

    //logicAndTest();

    linearFunctionTest();

    return 0;
}
