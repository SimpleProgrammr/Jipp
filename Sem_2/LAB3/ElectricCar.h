#ifndef ELECTRICCAR_H
#define ELECTRICCAR_H
#include "ParkedObject.h"

class ElectricCar : ParkedObject {
private:
    int _prodYear;

public:
    ElectricCar(
        std::string reg,
        ParkingZones zone,
        double time,
        int prodYear);


    double getDiscount() const;

    std::string getVehicleType() const override;

    double getPrice() const override;

    void print() const override;
};

#endif // ELECTRICCAR_H