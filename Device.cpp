#include "Device.h"
//Constructor for the device that sets the inital information including all the measurement points.
Device::Device()
{
    isMeasuring = false;
    measurementPoints = {"Wrist under thumb (Right hand)", "Middle wrist (Right hand)", "Wrist under pinky (Right hand)",
    "Back wrist under pinky (Right hand)", "Back wrist middle (Right hand)", "Back wrist under thumb (Right hand)", "Big toe joint (Right foot)",
    "Before toes (Right foot)", "Inside ankle (Right foot)", "Pinky toe joint (Right foot)", "Outside ankle (Right foot)", "Bridge (Right foot)",
    "Wrist under thumb (Left hand)", "Middle wrist (Left hand)", "Wrist under pinky (Left hand)", "Back wrist under pinky (Left hand)",
    "Back wrist middle (Left hand)", "Back wrist under thumb (Left hand)", "Big toe joint (Left foot)", "Before toes (Left foot)",
    "Inside ankle (Left foot)", "Pinky toe joint (Left foot)", "Outside ankle (Left foot)", "Bridge (Left foot)"};
}
//Starts up the device and makes it start measuring
void Device::startUp(){
    isMeasuring = true;
}
//Measures the point and generates data for it
void Device::measurePoint(int point){
    srand(time(0));
    int measurement;
    //Generating random values for measured value, corresponding to appropriate measured value
    //H1L and H1R
    if (point == 0 || point == 12){
        measurement = rand()%(190-5 + 1) + 5;
    }
    //H2L and H2R, H4L and H4R
    else if (point == 1 || point == 13 || point == 3 || point == 15){
        measurement = rand()%(170-5 + 1) + 5;
    }
    //H3L and H3R
    else if (point == 2 || point == 14){
        measurement = rand()%(140-5 + 1) + 5;
    }
    //H5L and H5R, H6L and H6R
    else if (point == 4 || point == 16 || point == 5 || point == 17){
        measurement = rand()%(200-5 + 1) + 5;
    }
    //F1L and F1R
    else if (point == 6 || point == 18){
        measurement = rand()%(160-5 + 1) + 5;
    }
    //F2L and F2R, F5L and F5R
    else if (point == 7 || point == 19 || point == 10 || point == 22){
        measurement = rand()%(130-5 + 1) + 5;
    }
    //F3L and F3R, F4L and F4R, F6L and F6R
    else if (point == 8 || point == 20 || point == 9 || point == 21 || point == 11 || point == 23){
        measurement = rand()%(150-5 + 1) + 5;
    }
    unprocessedData[point] = measurement;
}
//Shuts down the device and makes it stop measuring
void Device::shutDown(){
    isMeasuring = false;
}
std::array<int, 24> Device::getUnprocessedData(){
    return unprocessedData;
}
std::vector<std::string> Device::getMeasurementPoints(){
    return measurementPoints;
}
