#ifndef DATA_H
#define DATA_H
#include "State.h"
#include <vector>
#include <string>
#include "Indicator.h"

class Data
{
public:
    Data(const Indicator& ind, std::vector<State> orgs);

    std::string getRecommendation() const;
    Indicator getIndicators() const;
    std::vector<State> getStates() const;
    void generateRecommendation();

private:
    std::string recommendation;
    std::vector<State> organs;
    std::vector<std::string> organNames;
    Indicator indicators;
    ~Data();
};

#endif // DATA_H
