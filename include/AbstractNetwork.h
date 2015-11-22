#ifndef ABSTRACTNETWORK_H
#define ABSTRACTNETWORK_H

#include "Layer.h"

class AbstractNetwork
{
    public:
/*
        class Sample
        {
        public:
            //inVals: input values
            //outVals: output values
            Sample (const vector <int>& inVals, const vector <int>& outVals);

            vector <int>::const_iterator iterIn() const;

            vector <int>::const_iterator iterOut() const;

        private:
            vector <int> mInVals;
            vector <int> mOutVals;
        };

        //neuronsPerLayer size determines number of layers, elements number of neurons per layer
        //activations specifies activation function to be used for each layer, has to have same size as neuronsPerLayer
        AbstractNetwork (const vector <unsigned>& neuronsPerLayer, const vector <abstractActFunctor>& activations);

        //inVec input vector to be applied to input nodes
        //returns value computed by network
        double compute(const vector <Sample>& inVec) const;

        //performs training, adjusting the network's weights
        void train(const vector <vector <Sample>> samples) = 0;

    protected:
        //trains a particular sample until desired value is reached
        void train_sample(const vector <Sample>& sample);

    private:
        //creates input layer and stores it in mInLay
        //noNeurons: number of neurons in this layer
        //actFunctor: activation function for this layer
        void createInputLayer(const unsigned noNeurons, const abstractActFunctor& actFunctor);

        //creates hidden layer and appends it to mHidLays
        //noNeurons: number of neurons in this layer
        //actFunctor: activation function for this layer
        //prevLay: precedent layer in network hierarchy
        void createHiddenLayer(const unsigned noNeurons, const abstractActFunctor& actFunctor, const AbstractLayer& prevLay);

        //creates output layer and stores it in mOutLay
        //noNeurons: number of neurons in this layer
        //actFunctor: activation function for this layer
        //prevLay: precedent layer in network hierarchy
        void createOutputLayer(const unsigned noNeurons, const abstractActFunctor& actFunctor, const AbstractLayer& prevLay);

        InputLayer mInLay;
        vector <HiddenLayer> mHidLays;
        OutputLayer mOutLay;
*/
		AbstractNetwork(int inputsCount, int layersCount);
		virtual void Initialize();
		int getNumberOfInputs();
		int getNumberOfLayers();
		vector<double> getOutput();
		Layer& operator[](const size_t index);

		virtual vector<double> Accumulate(vector<double> input) = 0;
		virtual double Train(vector<double> input, vector<double> output) = 0;
		virtual void SaveToDisk() = 0;
		virtual void LoadFromDisk() = 0;

	protected:
		vector<Layer> theLayers;
		vector<double> theOutput;
		int theNumberOfInputs;
		int theNumberOfLayers;
};

#endif // ABSTRACTNETWORK_H
