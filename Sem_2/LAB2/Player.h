#pragma once
#include <string>

class Player {
private:
    int _hp;
    std::string _name;
    int _maxHP;
    int _level;

public:
    Player(const std::string &name);

    void damage(int);

    void heal(int);

    void levelUp();

    void printStats() const;
};