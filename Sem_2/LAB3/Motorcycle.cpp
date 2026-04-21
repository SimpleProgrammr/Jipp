//
// Created by Elmo on 12/03/2026.
//

#include "Motorcycle.h"
#include <iostream>
#include <ostream>

Motorcycle::Motorcycle(std::string reg, ParkingZones zone, double time, double engineVolume, double discount) {
    _registrationPlates = reg;
    _time = time;
    _parkingZone = zone;

    _engineVolume = engineVolume;
    _discount = (_engineVolume > 0.125 ? discount : 1);
}

std::string Motorcycle::getVehicleType() const {
    return "Motorcycle";
}

double Motorcycle::getPrice() const {
    return _parkingZone * _time * (1 - _discount);
}

double Motorcycle::getDiscount() const {
    return _discount;
}

void Motorcycle::print() const {
    std::cout << "---------------------------------" << std::endl
            << "Vehicle type: " << getVehicleType() << std::endl
            << "Register Plates: " << _registrationPlates << std::endl
            << "Parking zone: " << _parkingZone << std::endl
            << "Parking time: " << _time << std::endl
            << "Discount: " << getDiscount() * 100 << "%" << std::endl
            << "Paid: " << getPrice() << std::endl;
}