#include "Indicator.h"

Indicator::Indicator()
{
    //Default values for health indicators set so that they will decrement to 0 and never a negative value in the worst case scenario for cleaner display.
    energy = 3;
    immune = 6;
    metabolism = 1;
    psychoemo = 8;
    musculoskeletal = 3;
    states = {State::NORMAL, State::NORMAL, State::NORMAL, State::NORMAL, State::NORMAL};
}

Indicator::Indicator(int en, int im, int met, int psy, int mus)
{
    energy = en;
    immune = im;
    metabolism = met;
    psychoemo = psy;
    musculoskeletal = mus;
    states = {State::NORMAL, State::NORMAL, State::NORMAL, State::NORMAL, State::NORMAL};
}

//Calculates the average health indicator value of the user
void Indicator::calculateAverage(){
    average = (energy + immune + metabolism + psychoemo + musculoskeletal)/5;
}