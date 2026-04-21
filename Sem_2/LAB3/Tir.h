#ifndef TIR_H
#define TIR_H
#include "ParkedObject.h"


class Tir : ParkedObject {
private:
    double _size;
    double _discount;

public:
    Tir(std::string reg,
        ParkingZones zone,
        double size,
        double discount);

    double getDiscount() const;

    std::string getVehicleType() const override;

    double getPrice() const override;

    void print() const override;
};

#endif // TIR_H