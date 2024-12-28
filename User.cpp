#include "User.h"
//Constructor for user. Sets the boolean to appropriate values and initalize the app and device
User::User()
{
    hasWater = true;
    hasSkinContact = false;
    device = new Device();
    app = new App();
    isAnalysing = false;
    hasWetSkin = false;
}
void User::refill(){
     hasWater = true;
}
//Applies the water and makes the skin wet
void User::applyWater(){
    hasWetSkin =true;
}
bool User::isWet(){
    return hasWetSkin;
}
//Starts up the device for analysis and sets isAnalysing to true
void User::startAnalysis(){
    isAnalysing = true;
    device->startUp();
}
//Ends the analysis and shuts down the device as well as makes the app process the data for the appropritate profile
void User::finishAnalysis(int profileNum){
    isAnalysing = false;
    device->shutDown();
    app->getUsers()[profileNum]->setTotalData(device->getUnprocessedData());
    app->processData(device->getUnprocessedData(), profileNum);
}
//Presses against a point and makes the device measure it
void User::pressAgainstPoint(int point){
    hasSkinContact = true;
    device->measurePoint(point);
}

void User::removeContact(){
    hasSkinContact = false;
}
//Functions for creating, deleting and modifying profiles using the app's functions
void User::createProfile(char* name, int height, int weight){
    app->addProfile(name, height, weight);
}
void User::deleteProfile(char* name){
    app->deleteProfile(name);
}
void User::modifyProfile(int  num, char* newName, int newHeight, int newWeight){
    app->modifyProfile(num, newName, newHeight, newWeight);
}
App* User::getApp() const{
    return app;
}

Device* User::getDevice() const{
    return device;
}

bool User::getSkinContact(){
    return hasSkinContact;
}

void User::setDry(){
    hasWetSkin = false;
}
std::vector<Data*> User::getHistory(int profileNum){
    return (app->getUsers()[profileNum]->getHistory());
}
