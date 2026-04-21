#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H
#include "ParkedObject.h"


class Motorcycle : ParkedObject {
private:
    double _engineVolume;
    double _discount;

public:
    Motorcycle(std::string reg,
               ParkingZones zone,
               double time,
               double engineVolume,
               double discount);


    double getDiscount() const;

    std::string getVehicleType() const override;

    double getPrice() const override;

    void print() const override;
};


#endif // MOTORCYCLE_H