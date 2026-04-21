#include "ElectricCar.h"

#include <iostream>

ElectricCar::ElectricCar(std::string reg, ParkingZones zone, double time, int prodYear) {
    _registrationPlates = reg;
    _time = time;
    _parkingZone = zone;
    _prodYear = prodYear;
}

std::string ElectricCar::getVehicleType() const {
    return "Electric car";
}

double ElectricCar::getPrice() const {
    if (_prodYear <= 2020)
        return INFINITY;
    return _parkingZone * 2 * _prodYear;
}

double ElectricCar::getDiscount() const {
    return 0;
}


void ElectricCar::print() const {
    std::cout << "---------------------------------" << std::endl
            << "Vehicle type: " << getVehicleType() << std::endl
            << "Register Plates: " << _registrationPlates << std::endl
            << "Parking zone: " << _parkingZone << std::endl
            << "Parking time: " << _time << std::endl
            << "Discount: " << getDiscount() * 100 << "%" << std::endl
            << "Paid: " << getPrice() << std::endl;
}