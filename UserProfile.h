
#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <string>
#include "Data.h"
#include "array"
class UserProfile {
public:
    UserProfile(const std::string& name, int height, int weight);

    int getUserId() const;
    std::string getName() const;
    int getHeight() const;
    int getWeight() const;
    Data* getData() const;
    std::vector<Data*>getHistory() const { return history; }
    std::array<int, 24> getTotalData() const { return totalUnprocessedData; };

    void setName(const std::string& name);
    void setHeight(int height);
    void setWeight(int weight);
    void setTotalData(std::array<int, 24> newMeasure);
    void addData(const Data& newData);

private:
    int userId;
    Data* data;
    std::vector<Data*> history;
    std::string name;
    int height; // cm
    int weight; // kg
    std::array<int, 24> totalUnprocessedData;
};

#endif
