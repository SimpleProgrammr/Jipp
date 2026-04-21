//
// Created by Elmo on 12/03/2026.
//

#include "Tir.h"
#include <iostream>
#include <ostream>

Tir::Tir(std::string reg,
         ParkingZones zone,
         double size,
         double discount) {
    _registrationPlates = reg;
    _time = 1;
    _parkingZone = zone;
    _discount = discount;
    _size = size;
}

std::string Tir::getVehicleType() const {
    return "Tir";
}

double Tir::getPrice() const {
    if (_size >= 10) {
        return 1000;
    } else {
        return _parkingZone * 50 * (1 - _discount);
    }
}

double Tir::getDiscount() const {
    return _discount;
}

void Tir::print() const {
    std::cout << "---------------------------------" << std::endl
            << "Vehicle type: " << getVehicleType() << std::endl
            << "Register Plates: " << _registrationPlates << std::endl
            << "Parking zone: " << _parkingZone << std::endl
            << "Parking time: " << _time << std::endl
            << "Discount: " << getDiscount() * 100 << "%" << std::endl
            << "Paid: " << getPrice() << std::endl;
}