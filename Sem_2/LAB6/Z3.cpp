//
// Created by Elmo on 16/04/2026.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include <cmath>
#include <string>
#include <functional>
#include <unordered_map>


class UnknownTypeException : public std::runtime_error {
public:
    explicit UnknownTypeException(const std::string &typeId)
        : std::runtime_error("Unknown type identifier in binary file: \"" + typeId + "\"") {
    }
};


class Shape {
public:
    virtual ~Shape() = default;

    virtual double area() const = 0;

    virtual std::string typeName() const = 0;

    virtual void serialize(std::ostream &out) const = 0;

    virtual void print(std::ostream &out) const = 0;

    static void writeDouble(std::ostream &out, double v) {
        out.write(reinterpret_cast<const char *>(&v), sizeof(v));
    }

    static double readDouble(std::istream &in) {
        double v;
        in.read(reinterpret_cast<char *>(&v), sizeof(v));
        return v;
    }

    static void writeString(std::ostream &out, const std::string &s) {
        uint32_t len = static_cast<uint32_t>(s.size());
        out.write(reinterpret_cast<const char *>(&len), sizeof(len));
        out.write(s.data(), len);
    }

    static std::string readString(std::istream &in) {
        uint32_t len = 0;
        in.read(reinterpret_cast<char *>(&len), sizeof(len));
        if (!in) throw std::runtime_error("EOF while reading type id length");
        std::string s(len, '\0');
        in.read(s.data(), len);
        if (!in) throw std::runtime_error("EOF while reading type id data");
        return s;
    }
};


class Circle : public Shape {
public:
    explicit Circle(double r) : r_(r) {
    }

    double area() const override { return M_PI * r_ * r_; }
    std::string typeName() const override { return "Circle"; }
    double radius() const { return r_; }

    void serialize(std::ostream &out) const override {
        writeString(out, typeName());
        writeDouble(out, r_);
    }

    void print(std::ostream &out) const override {
        out << "Circle(r=" << r_ << ")  area=" << area();
    }

    static std::unique_ptr<Shape> deserialize(std::istream &in) {
        return std::make_unique<Circle>(readDouble(in));
    }

private:
    double r_;
};


class Rectangle : public Shape {
public:
    Rectangle(double w, double h) : w_(w), h_(h) {
    }

    double area() const override { return w_ * h_; }
    std::string typeName() const override { return "Rectangle"; }
    double width() const { return w_; }
    double height() const { return h_; }

    void serialize(std::ostream &out) const override {
        writeString(out, typeName());
        writeDouble(out, w_);
        writeDouble(out, h_);
    }

    void print(std::ostream &out) const override {
        out << "Rectangle(w=" << w_ << ", h=" << h_ << ")  area=" << area();
    }

    static std::unique_ptr<Shape> deserialize(std::istream &in) {
        double w = readDouble(in);
        double h = readDouble(in);
        return std::make_unique<Rectangle>(w, h);
    }

private:
    double w_, h_;
};


class Triangle : public Shape {
public:
    Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {
        if (a + b <= c || a + c <= b || b + c <= a)
            throw std::invalid_argument("Triangle inequality violated");
    }

    double area() const override {
        double s = (a_ + b_ + c_) / 2.0;
        return std::sqrt(s * (s - a_) * (s - b_) * (s - c_));
    }

    std::string typeName() const override { return "Triangle"; }

    void serialize(std::ostream &out) const override {
        writeString(out, typeName());
        writeDouble(out, a_);
        writeDouble(out, b_);
        writeDouble(out, c_);
    }

    void print(std::ostream &out) const override {
        out << "Triangle(a=" << a_ << ", b=" << b_ << ", c=" << c_ << ")  area=" << area();
    }

    static std::unique_ptr<Shape> deserialize(std::istream &in) {
        double a = readDouble(in);
        double b = readDouble(in);
        double c = readDouble(in);
        return std::make_unique<Triangle>(a, b, c);
    }

private:
    double a_, b_, c_;
};


using ShapeFactory = std::function<std::unique_ptr<Shape>(std::istream &)>;

class ShapeRegistry {
public:
    static ShapeRegistry &instance() {
        static ShapeRegistry reg;
        return reg;
    }

    void registerFactory(const std::string &id, ShapeFactory f) {
        factories_[id] = std::move(f);
    }

    std::unique_ptr<Shape> create(const std::string &id, std::istream &in) const {
        auto it = factories_.find(id);
        if (it == factories_.end()) throw UnknownTypeException(id);
        return it->second(in);
    }

private:
    std::unordered_map<std::string, ShapeFactory> factories_;
};

struct RegistryInit {
    RegistryInit() {
        auto &reg = ShapeRegistry::instance();
        reg.registerFactory("Circle", Circle::deserialize);
        reg.registerFactory("Rectangle", Rectangle::deserialize);
        reg.registerFactory("Triangle", Triangle::deserialize);
    }
} g_init;

const uint32_t MAGIC = 0x53485053u;
const uint32_t VERSION = 1u;

void saveShapes(const std::string &path,
                const std::vector<std::unique_ptr<Shape> > &shapes) {
    std::ofstream out(path, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot open file for writing: " + path);

    out.write(reinterpret_cast<const char *>(&MAGIC), sizeof(MAGIC));
    out.write(reinterpret_cast<const char *>(&VERSION), sizeof(VERSION));
    uint32_t n = static_cast<uint32_t>(shapes.size());
    out.write(reinterpret_cast<const char *>(&n), sizeof(n));

    for (const auto &s: shapes) {
        std::cout << "  [save] typeid=" << typeid(*s).name()
                << "  ownId=" << s->typeName() << "\n";
        s->serialize(out);
    }
    std::cout << "Saved " << n << " shapes to \"" << path << "\"\n";
}

std::vector<std::unique_ptr<Shape> > loadShapes(const std::string &path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::runtime_error("Cannot open file for reading: " + path);

    uint32_t magic = 0, ver = 0;
    in.read(reinterpret_cast<char *>(&magic), sizeof(magic));
    in.read(reinterpret_cast<char *>(&ver), sizeof(ver));
    if (magic != MAGIC) throw std::runtime_error("Bad magic — not a shapes file");
    if (ver != VERSION) throw std::runtime_error("Unsupported version: " + std::to_string(ver));

    uint32_t n = 0;
    in.read(reinterpret_cast<char *>(&n), sizeof(n));

    std::vector<std::unique_ptr<Shape> > shapes;
    shapes.reserve(n);
    for (uint32_t i = 0; i < n; ++i) {
        std::string id = Shape::readString(in);
        auto s = ShapeRegistry::instance().create(id, in);

        if (auto *c = dynamic_cast<Circle *>(s.get()))
            std::cout << "  [load] Circle    via dynamic_cast  r=" << c->radius() << "\n";
        else if (auto *r = dynamic_cast<Rectangle *>(s.get()))
            std::cout << "  [load] Rectangle via dynamic_cast  "
                    << r->width() << "x" << r->height() << "\n";
        else
            std::cout << "  [load] " << id << " via dynamic_cast (brak branch szczegółowego)\n";

        shapes.push_back(std::move(s));
    }
    std::cout << "Loaded " << n << " shapes from \"" << path << "\"\n";
    return shapes;
}


int main() {
    const std::string FILE = "shapes.bin";

    std::vector<std::unique_ptr<Shape> > original;
    original.push_back(std::make_unique<Circle>(5.0));
    original.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    original.push_back(std::make_unique<Triangle>(3.0, 4.0, 5.0));
    original.push_back(std::make_unique<Circle>(2.5));
    original.push_back(std::make_unique<Rectangle>(10.0, 3.0));

    std::cout << "=== Oryginalna kolekcja ===\n";
    for (const auto &s: original) {
        std::cout << "  ";
        s->print(std::cout);
        std::cout << "\n";
    }


    std::cout << "\n=== Zapis do pliku binarnego ===\n";
    saveShapes(FILE, original);


    std::cout << "\n=== Odczyt z pliku binarnego ===\n";
    auto loaded = loadShapes(FILE);

    std::cout << "\n=== Odtworzona kolekcja ===\n";
    for (const auto &s: loaded) {
        std::cout << "  ";
        s->print(std::cout);
        std::cout << "\n";
    }


    std::cout << "\n=== Test UnknownTypeException ===\n";
    try {
        {
            std::ofstream bad("bad.bin", std::ios::binary);
            bad.write(reinterpret_cast<const char *>(&MAGIC), sizeof(MAGIC));
            bad.write(reinterpret_cast<const char *>(&VERSION), sizeof(VERSION));
            uint32_t one = 1;
            bad.write(reinterpret_cast<const char *>(&one), sizeof(one));
            Shape::writeString(bad, "Hexagon");
        }
        loadShapes("bad.bin");
    } catch (const UnknownTypeException &e) {
        std::cout << "  CAUGHT UnknownTypeException: " << e.what() << "\n";
    }


    std::cout << "\n=== Weryfikacja pól (area) ===\n";
    bool ok = true;
    for (size_t i = 0; i < original.size(); ++i) {
        double a = original[i]->area(), b = loaded[i]->area();
        bool match = std::fabs(a - b) < 1e-9;
        std::cout << "  [" << i << "] orig=" << a << "  loaded=" << b
                << (match ? "  OK" : "  MISMATCH!") << "\n";
        if (!match) ok = false;
    }
    std::cout << (ok ? "\nSerializacja/deserializacja: OK\n" : "\nBLAD!\n");
    return ok ? 0 : 1;
}