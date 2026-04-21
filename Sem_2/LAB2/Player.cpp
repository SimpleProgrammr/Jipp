#include "Player.h"

#include <iostream>
#include <ostream>

Player::Player(const std::string &name) : _hp(100), _maxHP(100), _level(0) {
    _name = name;
}

void Player::damage(const int damage) {
    if (damage <= 0) {
        throw std::invalid_argument("Damage cannot be less than zero. Use Heal");
    }
    _hp = std::max(_hp - damage, 0);
}

void Player::heal(const int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Heal cannot be less than zero. Use Damage");
    }
    _hp = std::max(_maxHP, _hp + amount);
}

void Player::levelUp() {
    _level++;
}

void Player::printStats() const {
    std::cout << "Name: " << _name << std::endl
            << "HP: " << _hp << "/" << _maxHP << std::endl
            << "Level: " << _level << std::endl;
}