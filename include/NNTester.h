#ifndef NNTESTER_H
#define NNTESTER_H

#include "Perceptron.h"
#include "StepFunction.h"

class NNTester
{
    public:
        static double epsilon;
        static bool debugging, addInfo;

        class LinSamGen
        {
        public:
            LinSamGen (double a, double b, double delta, pair <double, double> ylim);

            void setDelta (const double value);

            void setLim (const pair <double, double>& nylim);

            double getDelta() const;

            pair <double, double> getYlim() const;

            virtual Sample operator() () = 0;

        protected:
            double ma, mb, mDelta;
            pair <double, double> mYlim;
        };

        class RandLinSamGen : public LinSamGen
        {
        public:

            RandLinSamGen (double a, double b, double delta, pair <double, double> ylim);

            Sample operator() ();

        protected:
        };

        class PartLinSamGen : public LinSamGen
        {
        public:

            PartLinSamGen (double a, double b, double delta, pair <double, double> ylim, size_t firstPartSamples);

            Sample operator() ();

            protected:
            size_t mCntFirstPartSamples;
        };

        NNTester(ActionPotentialFunction* actFunc, const int& numberOfInputs, const vector<int>& numberOfNeurons);

        void trainIncreasing (const size_t iterations, const size_t samPerIt, const double addDelta, LinSamGen* const pSamGen, bool fastTraining = true);

        void trainRandom (const size_t iterations, const size_t samPerIt, LinSamGen* const pSamGen, bool fastTraining = true);

        void trainCombo (const size_t iterations, const size_t samPerIt, const double addDelta, LinSamGen* const pIncrSamGen, LinSamGen* const pRandSamGen, bool fastTraining = true);

        double verify (const size_t numSamples, LinSamGen* pSamGen);

        void printNet();

    protected:
    private:
        Perceptron mPtron;
};

#endif // NNTESTER_H
