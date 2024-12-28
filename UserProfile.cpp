#include "UserProfile.h"

UserProfile::UserProfile(const std::string& name, int height, int weight) :
    name(name), height(height), weight(weight), data(nullptr) {}

std::string UserProfile::getName() const {
    return name;
}

int UserProfile::getHeight() const {
    return height;
}

int UserProfile::getWeight() const {
    return weight;
}

void UserProfile::setName(const std::string& name){
    this->name = name;
}

void UserProfile::setHeight(int height) {
    this->height = height;
}

void UserProfile::setWeight(int weight) {
    this->weight = weight;
}

Data* UserProfile::getData() const {
    return data;
}

void UserProfile::addData(const Data& newData){
    data = new Data(newData);
    history.push_back(data);
}

void UserProfile::setTotalData(std::array<int, 24> newMeasure) {
    for (int i = 0; i < 24; i++) {
        totalUnprocessedData[i] += newMeasure[i];
    }
}
