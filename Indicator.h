#ifndef INDICATOR_H
#define INDICATOR_H
#include <vector>
#include "State.h"

class Indicator
{
public:
    Indicator();
    Indicator(int en, int im, int met, int psy, int mus);
    int energy;
    int immune;
    int metabolism;
    int psychoemo;
    int musculoskeletal;
    int average;
    void calculateAverage();
    std::vector<State> states;
};


#endif // INDICATOR_H
