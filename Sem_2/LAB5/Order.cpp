//
// Created by Elmo on 30/03/2026.
//

#include "Order.h"

#include <iostream>
#include <ostream>

Order::Order() {
    books.clear();
    shipping_zone = 0;
}

int Order::get_shipping_zone() {
    std::cout << "Enter your shipping zone(1-3): ";
    std::cin >> shipping_zone;
    if (shipping_zone - 3 < -2)
        shipping_zone = 1;
    else if (shipping_zone - 3 > 1)
        shipping_zone = 3;
    return shipping_zone;
}

void Order::operator+=(std::pair<book, int> position) {
    books.push_back(position);
}

double Order::calculate_total_price() {
    double total_price = 0;
    double package_mass = 0;
    for (const std::pair<book, int> &position: books) {
        total_price += position.first.price * position.second;
        package_mass += position.second * 0.4;
    }

    if (total_price > 300)
        package_mass = 0;

    total_price += static_cast<double>(get_shipping_zone()) / 2 * (package_mass * 6);
    return total_price;
}