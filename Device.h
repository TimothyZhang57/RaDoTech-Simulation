/*Device class that represents the physical RaDoTech device. It has functions to start up, shut down and measure point. It also has a vector for all the measurements that the device emasures
 * and an array for the device's unprocessed data. It also has a variable for the amount of power the device has and a boolean for if it is measuring. */
#ifndef DEVICE_H
#define DEVICE_H
#include "Data.h"
#include <cstdlib>
#include "array"
class Device
{
public:
    Device();
    void startUp();
    void measurePoint(int point);
    void shutDown();
    std::array<int, 24> getUnprocessedData();
    std::vector<std::string> getMeasurementPoints();
private:
    std::vector<std::string> measurementPoints;
    std::array<int, 24> unprocessedData;
    bool isMeasuring;
};
#endif // DEVICE_H
