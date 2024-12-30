#ifndef TILE_HANDLER_H
#define TILE_HANDLER_H

#include "core/Tile.hpp"
#include "tile/Sand.hpp"

class World;

class TileHandler {
public:
    enum TileType {
        SAND = 1,
        BLOCK = 2,
    };

    static Tile* SwitchTile(sf::Vector2f position, int Type, World* world);
};

#endif // TILE_HANDLER_H
