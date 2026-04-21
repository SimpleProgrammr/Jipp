#include <iostream>
#include <ostream>
#include <variant>
#include <vector>
//
// Created by Elmo on 16/04/2026.
//
using namespace std;

void z1() {
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = 0;
    for (auto i: v) {
        sum += i;
    }
    cout << "Sum: " << sum << endl;
    int even_count = 0;
    for_each(v.begin(), v.end(),
             [&even_count](int i) {
                 if (i % 2 == 0) even_count++;
             });
    cout << "Even numbers: " << even_count << endl;
}

int *test_z2_bad() {
    int *num = new int;
    *num = 42;
    return num;
}

unique_ptr<int> test_z2_unique() {
    std::unique_ptr<int> num(new int);
    *num = 42;
    return num;
}

void z2() {
    for (long i = 0; i < 1000000000; i++) {
        test_z2_bad(); // memory leak
    }
    cout << "Bad ended " << endl;
    for (long i = 0; i < 1000000000; i++) {
        test_z2_unique();
    }
}

std::optional<int> find_even(const std::vector<int> &v) {
    for (auto i: v) {
        if (i % 2 == 0) return i;
    }
    return nullopt;
}

void z3() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    if (auto res = find_even(v)) {
        std::cout << *res;
    }
}

struct Point {
    int x, y;
};

std::pair<int, int> decompose_point(Point p) {
    return std::make_pair(p.x, p.y);
}

void z4() {
    Point p = {1, 2};
    auto [x,y] = p;
    auto [xx,yy] = decompose_point(p);
}

void z5() {
    std::variant<int, string> p = 2;
    std::visit([](auto &&p) { cout << p << endl; }, p);
    p = "Hello";
    std::visit([](auto &&p) { cout << p << endl; }, p);
}

void z6() {
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int counter = 0;

    // for_each(v.begin(), v.end(),
    //     [=](int i) {
    //         counter++; // won't compile
    //     });
    for_each(v.begin(), v.end(),
             [&](int i) {
                 counter++;
             });
}

struct Student {
    int grade;
};

void z7() {
    Student s = {5};

    auto cmp = (s.grade <=> 3);
    if (cmp > 0)
        cout << "Good" << endl;
    else if (cmp == 0)
        cout << "Mid" << endl;
    else
        cout << "Bad" << endl;
}

optional<string> describe(int x) {
    if (x < 0)
        return nullopt;
    [=]() {
        if (x % 2 == 0) {
            return "Even";
        }
        return "Odd";
    };
}

int main() {
    z7();
}


