#pragma once
#include <list>
#include <string>


struct book {
    std::string name;
    int price;
};

class Order {
private:
    std::list<std::pair<book, int> > books;
    int shipping_zone;

    int get_shipping_zone();

public:
    Order();

    void operator+=(std::pair<book, int>);

    double calculate_total_price();
};