#include "Data.h"
#include <cstring>
#include <sstream>
#include <stdexcept>

Data::Data(const Indicator& ind, std::vector<State> orgs)
{
    indicators = ind;
    recommendation =  "Recommendation.";
    organs = orgs;
    organNames = {"Left Lung", "Right Lung", "Heart", "Stomach", "Kidneys", "Large Intestine", "Small Intestine"};
}

//Generates text for recommendation corresponding to the state of user's health indicators.
void Data::generateRecommendation() {
    std::ostringstream oss;

    // Energy
    if (indicators.states[0] == State::ABOVENORM) {
        oss << "Energy levels are high. Stay active but avoid over-exertion.\n";
    }
    else if (indicators.states[0] == State::BELOWNORM) {
        oss << "Energy levels are low. Improve your nutrition and prioritize rest.\n";
    }
    else {
        oss << "Energy levels are normal. Maintain your current lifestyle.\n";
    }

    // Immune System
    if (indicators.states[1] == State::ABOVENORM) {
        oss << "Immune system is high. Make sure to get adequate rest.\n";
    }
    else if (indicators.states[1] == State::BELOWNORM) {
        oss << "Immune system is low. Increase your vitamin intake and get adequate rest.\n";
    }
    else {
        oss << "Immune system is normal. Maintain your current lifestyle.\n";
    }

    // Metabolism
    if (indicators.states[2] == State::ABOVENORM) {
        oss << "Metabolism is high. Ensure you are eating nutritious and satiating food.\n";
    }
    else if (indicators.states[2] == State::BELOWNORM) {
        oss << "Metabolism is low. Increase your physical activity and focus more on protein.\n";
    }
    else {
        oss << "Metabolism is normal. Maintain your current lifestyle.\n";
    }

    // Psychoemotional
    if (indicators.states[3] == State::ABOVENORM) {
        oss << "Psycho-emotional state is high. Practice mindfulness and prioritize rest.\n";
    }
    else if (indicators.states[3] == State::BELOWNORM) {
        oss << "Psycho-emotional state is low. Practice mindfulness and prioritize rest.\n";
    }
    else {
        oss << "Psychoemotional state is normal. Maintain your current lifestyle.\n";
    }

    // Musculoskeletal
    if (indicators.states[4] == State::ABOVENORM) {
        oss << "Musculoskeletal health is high. Prioritize proper recovery.\n";
    }
    else if (indicators.states[4] == State::BELOWNORM) {
        oss << "Musculoskeletal health is low. Increase your physical activity.\n";
    }
    else {
        oss << "Musculoskeletal health is normal. Maintain your current lifestyle.\n";
    }

    std::string result = oss.str();
    recommendation = result.c_str();
}

std::string Data::getRecommendation() const {
    return recommendation;
}

Indicator Data::getIndicators() const {
    return indicators;
}

std::vector<State> Data::getStates() const {
    return organs;
}