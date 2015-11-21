#ifndef FEFONETWORK_H
#define FEFONETWORK_H

#include <AbstractNetwork.h>


class FeFoNetwork : public AbstractNetwork
{
    public:
        FeFoNetwork (const vector <unsigned>& neuronsPerLayer, const vector <abstractActFunctor>& activations);

        double compute(const vector <double>& inVec);

    protected:
    private:
};

#endif // FEFONETWORK_H
