#include "Player.h"

Player::Player(const std::string& name, char symbol)
    : name(name), symbol(symbol) {
}

std::string Player::getName() const {
    return name;
}

char Player::getSymbol() const {
    return symbol;
}
