#pragma once
#include <string>


enum ParkingZones {
    ZONE_A = 6,
    ZONE_B = 4,
    ZONE_C = 2
};

class ParkedObject {
public:
    std::string _registrationPlates;
    ParkingZones _parkingZone;
    double _time;


    ParkedObject() : _parkingZone(ZONE_A), _time(0), _registrationPlates("") {
    };

    virtual double getPrice() const = 0;

    virtual void print() const = 0;

    virtual std::string getVehicleType() const = 0;
};