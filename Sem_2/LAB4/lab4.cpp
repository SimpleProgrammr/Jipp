#include <iostream>
#include <valarray>

template<typename T>
T maxValue(T a, T b) {
    return a > b ? a : b;
};

template<typename T>
void swapValues(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void printArray(T arr, const long size) {
    std::cout << "[";
    for (long i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "]" << std::endl;
}

template<typename T>
class Box {
private:
    T value;

public:
    Box(T v) { value = v; };
    void set(T v) { value = v; };
    T get() const { return value; };
    void print() const { std::cout << value << std::endl; };
};

template<typename T>
class Pair {
private:
    T first;
    T second;

public:
    Pair(T a, T b) : first(a), second(b) {
    };
    T sum() const { return first + second; };
};

template<typename T>
class Vector2D {
public:
    T x;
    T y;

    Vector2D(T x, T y) : x(x), y(y) {
    };
    T lengthSquared() const { return pow(x + y, 2); };
};

template<typename T>
T dotProduct(const Vector2D<T> &a, const Vector2D<T> &b) {
    return a.x * b.x + a.y * b.y;
};

template<typename T>
void printVector(const std::vector<T> &v) {
    std::cout << "[";
    for (T a: v)
        std::cout << a << ", ";
    std::cout << "\b\b]" << std::endl;
};

template<typename T>
T sumVector(const std::vector<T> &v) {
    T sum = 0;
    for (const T a: v)
        sum += a;
    return sum;
}

int main() {
    double d1 = 2.5, d2 = 2.2;
    int i1 = 1, i2 = 2;
    std::string s1 = "abc", s2 = "def";
    char c1 = 'a', c2 = 'b';

    std::cout << "Z1: " << std::endl
            << maxValue<int>(i1, i2) << std::endl
            << maxValue<double>(d1, d2) << std::endl
            << maxValue<char>(c1, c2) << std::endl << std::endl;

    std::cout << "Z2: " << std::endl;
    std::cout << "i1 = " << i1 << " i2 = " << i2 << "\t|\t";
    swapValues(i1, i2);
    std::cout << "i1 = " << i1 << " i2 = " << i2 << std::endl;

    std::cout << "d1 = " << d1 << " d2 = " << d2 << "\t|\t";
    swapValues(d1, d2);
    std::cout << "d1 = " << d1 << " d2 = " << d2 << std::endl;

    std::cout << "s1 = " << s1 << " s2 = " << s2 << "\t|\t";
    swapValues(s1, s2);
    std::cout << "s1 = " << s1 << " s2 = " << s2 << std::endl << std::endl;

    printVector(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    printVector(std::vector<std::string>{"a", "b", "c", "d", "e", "f"});
    std::cout << std::endl;

    auto b1 = new Box<std::string>("b");
    auto b2 = new Box<int>(1);
    auto b3 = new Box<double>(2.5);
    std::cout << "Z4: " << std::endl;
    b1->print();
    b2->print();
    b3->print();
    free(b1);
    free(b2);
    free(b3);
    std::cout << std::endl;

    auto p1 = Pair<int>(1, 2);
    auto p2 = Pair<double>(1.5, 2.5);
    auto p3 = Pair<std::string>("a", "b");
    std::cout << "Z5: " << std::endl
            << p1.sum() << std::endl
            << p2.sum() << std::endl
            << p3.sum() << std::endl << std::endl;


    std::cout << "Z7: " << std::endl;
    std::vector<int> v = {7, 2, 9, 1, 5, 2};
    printVector(v);

    std::cout << std::endl << "Z8: " << std::endl;
    std::sort(v.begin(), v.end());
    printVector(v);

    std::cout << "Max value: " << v.at(v.size() - 1) << std::endl << "Avg value: " << sumVector(v) / static_cast<double>
            (v.size());
}