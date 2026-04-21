#include "Car.h"

#include <iostream>
#include <ostream>

Car::Car(std::string reg, ParkingZones zone, double time, double discount) {
    _registrationPlates = reg;
    _time = time;
    _parkingZone = zone;
    _discount = discount;
}

double Car::getPrice() const {
    return _parkingZone * _time * (1 - _discount);
}

std::string Car::getVehicleType() const {
    return "Car";
}

double Car::getDiscount() const {
    return _discount;
}

void Car::print() const {
    std::cout << "---------------------------------" << std::endl
            << "Vehicle type: " << getVehicleType() << std::endl
            << "Register Plates: " << _registrationPlates << std::endl
            << "Parking zone: " << _parkingZone << std::endl
            << "Parking time: " << _time << std::endl
            << "Discount: " << getDiscount() * 100 << "%" << std::endl
            << "Paid: " << getPrice() << std::endl;
}