/*The user class will have a device which represents the user's RaDoTech Device as well as an app object which represents the user's RaDoTech app. The user will has a boolean to track if they
 * have water as well as if they have wet skin. They will also have boolean to represent if there is skinContact and if the user is analysing. There are also functions that allow the user to
 * use their app to create, delete and modify profiles. The user can press the device against a point to start measurements as well as finish the analysis which triggers the device to send the
 * data and the app to start processing. The user can also apply water to their skin and refill the water*/
#ifndef USER_H
#define USER_H
#include "Data.h"
#include <vector>
#include "App.h"
#include "Device.h"
class User
{
public:
    User();
    void startAnalysis();
    void refill();
    void pressAgainstPoint(int point);
    void createProfile(char* name, int height, int weight);
    void deleteProfile(char* name);
    void modifyProfile(int num, char* newName, int newHeight, int newWeight);
    void removeContact();
    App* getApp() const;
    void finishAnalysis(int profileNum);
    Device* getDevice() const;
    bool getSkinContact();
    std::vector<Data*>getHistory(int profileNum);
    void applyWater();
    bool isWet();
    void setDry();
private:
    bool hasWater;
    App* app;
    Device* device;
    bool hasSkinContact;
    bool isAnalysing;
    bool hasWetSkin;


};

#endif // USER_H
