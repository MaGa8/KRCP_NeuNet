#include "NNTester.h"

#include <map>
#include <algorithm>
#include <assert.h>
#include <iostream>

using namespace std;

double NNTester::epsilon = 0.000001;
bool NNTester::debugging = false, NNTester::addInfo = false;

NNTester::LinSamGen::LinSamGen (double a, double b, double delta, pair <double, double> ylim) :
    ma (a), mb (b), mDelta (delta), mYlim (ylim) {}

void NNTester::LinSamGen::setDelta (double value)
{
    mDelta = value;
}

void NNTester::LinSamGen::setLim (const pair <double, double>& nylim)
{
    mYlim = nylim;
}

double NNTester::LinSamGen::getDelta() const
{
    return mDelta;
}

pair <double, double> NNTester::LinSamGen::getYlim() const
{
    return mYlim;
}

NNTester::RandLinSamGen::RandLinSamGen (double a, double b, double delta, pair <double, double> ylim) :
    LinSamGen (a, b, delta, ylim) {}

Sample NNTester::RandLinSamGen::operator() ()
{
    random_device rdev;
    mt19937 randGen (rdev());
    uniform_real_distribution <double> xdist (mYlim.first / ma - mb - mDelta, mYlim.second / ma - mb + mDelta);
    double xrand = xdist (randGen);
    uniform_real_distribution <double> ydist (ma * xrand + mb - mDelta, ma * xrand + mb + mDelta);
    double yrand = ydist (randGen);
    //true if sample above line
    double result = (double)(ma * xrand + mb < yrand);
    return make_pair (vector <double> ({xrand, yrand}), vector <double> ({result}));
}

NNTester::PartLinSamGen::PartLinSamGen (double a, double b, double delta, pair <double, double> ylim, size_t firstPartSamples) :
    LinSamGen (a, b, delta, ylim), mCntFirstPartSamples (firstPartSamples) {}

Sample NNTester::PartLinSamGen::operator() ()
{
    random_device rdev;
    mt19937 randGen (rdev());
    uniform_real_distribution <double> xdist;
    if (mCntFirstPartSamples > 0)
    {
        //generate samples below line
        xdist = uniform_real_distribution <double> (mYlim.first / ma - mb - mDelta, mYlim.second / ma - mb);
        --mCntFirstPartSamples;
    }
    else
        xdist = uniform_real_distribution <double> (mYlim.first / ma - mb + epsilon, mYlim.second / ma - mb + mDelta);

    double xrand = xdist (randGen);
    uniform_real_distribution <double> ydist (ma * xrand + mb - mDelta, ma * xrand + mb + mDelta);
    double yrand = ydist (randGen);
    //true if sample above line
    double result = (double)(ma * xrand + mb < yrand);
    assert (mCntFirstPartSamples == 0 || !result);
    return make_pair (vector <double> ({xrand, yrand}), vector <double> ({result}));
}

NNTester::NNTester(ActionPotentialFunction* actFunc, const int& numberOfInputs, const vector <int>& numberOfNeurons) :
    mPtron (actFunc, numberOfInputs, numberOfNeurons)
{
    mPtron.Initialize();
}

void NNTester::trainIncreasing(const size_t iterations, const size_t samPerIt, const double addDelta, LinSamGen* const pSamGen)
{
    vector <Sample> samples (samPerIt);
    for (size_t cIter = 0; cIter < iterations; ++cIter)
    {
        pSamGen->setDelta (pSamGen->getDelta() + addDelta);
        for (auto& sam : samples)
            sam = (*pSamGen)();
        mPtron.trainFast(samples);
    }
}

void NNTester::trainRandom(const size_t iterations, const size_t samPerIt, LinSamGen* const pSamGen)
{
    vector <Sample> samples (samPerIt);
    for (size_t cIter = 0; cIter < iterations; ++cIter)
    {
        for (auto& sam : samples)
            sam = (*pSamGen)();
        mPtron.trainFast(samples);
    }
}

double NNTester::verify(const size_t numSamples, LinSamGen* pSamGen)
{
    vector <Sample> samples (numSamples);
    for (auto& sam : samples)
            sam = (*pSamGen)();
    pair <size_t, size_t> trueFalseCnt;
    map <vector <double>, pair <size_t, size_t>> hitsPerOutput;
    for (const Sample& sam : samples)
    {
        vector <double> actOut = mPtron.Accumulate (sam.first);
        actOut.erase (actOut.end() - 1);

        auto ihitMap = hitsPerOutput.begin();
        while (ihitMap != hitsPerOutput.end() && !equal (actOut.begin(), actOut.end(), ihitMap->first.begin()))
            ++ihitMap;
        if (ihitMap == hitsPerOutput.end())
            ihitMap = hitsPerOutput.insert (make_pair (actOut, make_pair (0, 0))).first;
        if (debugging)
        {
            cout << "input ";
            for_each (sam.first.begin(), sam.first.end(), [] (double i) {cout << i << " "; });
            cout << endl;
            cout << "actual output ";
            for_each (actOut.begin(), actOut.end(), [] (double ao) {cout << ao << " "; });
            cout << endl;
            cout << "expected output ";
            for_each (sam.second.begin(), sam.second.end(), [] (double o) {cout << o << " "; });
            cout << endl;
        }
        if (equal (actOut.begin(), actOut.end(), sam.second.begin()))
        {
            ++trueFalseCnt.first;
            ++ihitMap->second.first;
            if (debugging)
                cout << "true output" << endl;
        }
        else
        {
            ++trueFalseCnt.second;
            ++ihitMap->second.second;
            if (debugging)
                cout << "false output" << endl;
        }
    }

    if (addInfo)
    {
        cout << "checked " << numSamples << " samples" << endl;
        cout << "output true | false " << trueFalseCnt.first << " | " << trueFalseCnt.second << endl;
        cout << "per output true | false" << endl;
        for (const auto& hit : hitsPerOutput)
        {
            cout << "output ";
            for_each (hit.first.begin(), hit.first.end(), [] (double out) {cout << out << ", "; });
            cout << " " << hit.second.first << " | " << hit.second.second << endl;
        }
    }
    return (double)(trueFalseCnt.first / (trueFalseCnt.first + trueFalseCnt.second));
}
