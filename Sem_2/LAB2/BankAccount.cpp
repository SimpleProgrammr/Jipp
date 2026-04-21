#include "BankAccount.h"

#include <iostream>
#include <ostream>

int BankAccount::_nextId = 1;

BankAccount::BankAccount(const std::string &owner, const double balance) {
    _balance = balance;
    _owner = owner;
    _id = _nextId++;
}

void BankAccount::deposit(const double balance) {
    _balance += balance;
}

void BankAccount::withdraw(const double balance) {
    if (_balance >= balance)
        _balance -= balance;
    else
        throw std::invalid_argument("Balance must be greater than withdraw.");
}

double BankAccount::getBalance() const {
    return _balance;
}

int BankAccount::getId() const {
    return _id;
}

void BankAccount::print() const {
    std::cout << "ID: " << _id << std::endl
            << "Owner: " << _owner << std::endl
            << "Balance: " << _balance << std::endl;
}