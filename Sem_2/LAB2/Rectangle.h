#pragma once
class Rectangle {
private:
    double _width, _height;

public:
    Rectangle(double width, double height);

    static Rectangle createSquare(double side);

    bool isSquare() const;

    double area() const;

    double perimeter() const;

    void scale(double);
};