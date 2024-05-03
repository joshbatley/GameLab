#include "Tile.h"

std::unordered_map<Type, Tile> setupTileTypes() {
    std::unordered_map<Type, Tile> types;

    types[Type::Water] = Tile();
    types[Type::Water].type = Type::Water;
    types[Type::Water].src = {0,0};

    types[Type::Land] = Tile();
    types[Type::Land].type = Type::Land;
    types[Type::Land].src = {12 * 16,11 * 16};

    return types;
}
Tile::Tile()
{
}
