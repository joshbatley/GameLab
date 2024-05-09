#include "Tile.h"

std::unordered_map<Type, Tile> setupTileTypes() {
    std::unordered_map<Type, Tile> types;

    types[Type::Water] = Tile();
    types[Type::Water].type = Type::Water;
    types[Type::Water].src = {12 * 16,11 * 16};
    types[Type::Water].color = { 0, 0,255,255};

    types[Type::Land] = Tile();
    types[Type::Land].type = Type::Land;
    types[Type::Land].src = {0 * 16,1*16};
    types[Type::Land].color = { 255, 0,0,255};

    types[Type::Sand] = Tile();
    types[Type::Sand].type = Type::Sand;
    types[Type::Sand].src = {1 * 16,11 * 16};
    types[Type::Sand].color = { 255, 255,0,255};

    return types;
}

Tile::Tile()
{

}
