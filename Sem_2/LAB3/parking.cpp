#include "Car.cpp"
#include "ElectricCar.cpp"
#include "Tir.cpp"
#include "Motorcycle.cpp"

int main() {
    auto car1 = new Car("CAR1", ZONE_A, 10, 0);
    auto car2 = new Car("CAR2", ZONE_A, 10, 0.1);
    auto tir1 = new Tir("Tir1", ZONE_B, 5, 0);
    auto tir2 = new Tir("Tir2", ZONE_B, 10, 0);
    auto ev1 = new ElectricCar("Ev1", ZONE_C, 10, 2010);
    auto ev2 = new ElectricCar("Ev2", ZONE_C, 10, 2040);
    auto moto1 = new Motorcycle("Moto1", ZONE_A, 10, 0.1, 0);
    auto moto2 = new Motorcycle("Moto2", ZONE_A, 10, 0.2, 0);

    car1->print();
    car2->print();
    tir1->print();
    tir2->print();
    ev1->print();
    ev2->print();
    moto1->print();
    moto2->print();
}