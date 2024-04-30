#include "Player.h"

Player::Player(int id) : _id(id)
{
    std::cout << "Init" << std::endl;
}

void Player::Update()
{
    std::cout << "Updated" << _id << std::endl;
}

Player2::Player2(int id) : _id2(id)
{
    std::cout << "Init" << std::endl;
}

void Player2::Update()
{
    std::cout << "Updated" << _id2 << std::endl;
}