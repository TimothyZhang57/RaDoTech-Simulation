#ifndef STATE_H
#define STATE_H
#include <string>

//The state of either organs or health indicators corresponding to the reading obtainde from the Device.
enum class State {
    ABOVENORM,
    NORMAL,
    BELOWNORM
};

//Returns the state of organs or health indicators as strings
inline std::string ToString(State state){
    switch(state){
        case State::ABOVENORM: return "Above Normal";
        case State::NORMAL: return "Normal";
        case State::BELOWNORM: return "Below Normal";
    }
}
#endif // STATE_H
