#include "Player.h"

Player::Player(int id) : _id(id)
{
    std::cout << "Init" << std::endl;
}

void Player::Update()
{
    std::cout << "Updated" << _id << std::endl;
}
