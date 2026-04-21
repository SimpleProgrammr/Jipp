#include "Rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(const double width, const double height) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be greater than 0.");
    }

    _width = width;
    _height = height;
}

Rectangle Rectangle::createSquare(const double side) {
    return Rectangle(side, side);
}


double Rectangle::area() const {
    return _width * _height;
}

double Rectangle::perimeter() const {
    return 2 * (_width + _height);
}

bool Rectangle::isSquare() const {
    return _width == _height;
}

void Rectangle::scale(const double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Factor must be greater than 0.");
    }

    _width *= factor;
    _height *= factor;
}