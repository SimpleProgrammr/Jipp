#ifndef CAR_H
#define CAR_H
#include "ParkedObject.h"


class Car : ParkedObject {
private:
    double _discount;

public:
    Car(std::string reg, ParkingZones zone, double time, double discount);


    double getDiscount() const;

    double getPrice() const override;

    std::string getVehicleType() const override;

    void print() const override;
};
#endif // CAR_H