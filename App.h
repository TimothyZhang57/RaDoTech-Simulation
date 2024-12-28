#ifndef APP_H
#define APP_H
#include "UserProfile.h"
#include <iostream>
#include "array"
class App
{
public:
    App();
    void processData(std::array<int, 24> unprocessedData, int currentUser);
    void addProfile(std::string name, int height, int weight);
    void deleteProfile(std::string name);
    void modifyProfile(int num, std::string name, int newHeight, int newWeight);
    std::vector<UserProfile*> getUsers();
    bool isDuplicate(std::string name);

private:
    std::vector<UserProfile*> users;
};

#endif // APP_H
