#include "Car2.h"

#include <iostream>
#include <string>

Car2::Car2(const std::string &brand, const double max_speed) : _speed(0) {
    _brand = brand;
    _max_speed = max_speed;
}

Car2::~Car2() = default;

void Car2::accelerate(const double acceleration) {
    _speed += acceleration;
    if (_speed > _max_speed) {
        _speed = _max_speed;
    }
}

void Car2::brake(const double braking) {
    _speed -= braking;
    if (_speed < 0.0) {
        _speed = 0.0;
    }
}

double Car2::getSpeed() const {
    return _speed;
}

void Car2::printInfo() const {
    std::cout << "Brand: " << _brand << std::endl
            << "Max Speed: " << _max_speed << std::endl
            << "Speed: " << _speed << std::endl;
}