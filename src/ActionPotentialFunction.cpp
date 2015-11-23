#include "../include/ActionPotentialFunction.h"

ActionPotentialFunction::ActionPotentialFunction (double threshold) : mThreshold (threshold) {}

ActionPotentialFunction::getThreshold()
{
    return mThreshold;
}
