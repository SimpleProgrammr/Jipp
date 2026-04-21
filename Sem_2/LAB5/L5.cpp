//
// Created by Elmo on 30/03/2026.
//

#include "Order.cpp"

using namespace std;

#include <iostream>
#include <ostream>

int main() {
    auto ORDERS = Order();
    ORDERS += pair<book, int>{book{"B1", 10}, 5};
    ORDERS += pair<book, int>{book{"B2", 20}, 4};
    ORDERS += pair<book, int>{book{"B4", 40}, 2};
    ORDERS += pair<book, int>{book{"B5", 50}, 1};

    const double value = ORDERS.calculate_total_price();
    std::cout << value;
}