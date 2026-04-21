#pragma once

#include <string>

class Car2 {
private:
    std::string _brand;
    double _speed;
    double _max_speed;

public:
    Car2(const std::string &brand, double max_speed);

    ~Car2();

    void accelerate(double acceleration);

    void brake(double braking);

    double getSpeed() const;

    void printInfo() const;
};