#pragma once
#include <string>

class BankAccount {
private:
    std::string _owner;
    double _balance;
    int _id;
    static int _nextId;

public:
    BankAccount(const std::string &owner, double balance);

    void deposit(double);

    void withdraw(double);

    double getBalance() const;

    int getId() const;

    void print() const;
};