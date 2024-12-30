#ifndef TIlE_HANDLER_H
#define TIlE_HANDLER_H


// include Tile Type
#include "core/Tile.hpp"
#include "tile/Sand.hpp"


class TileHandler {

    public:

        enum TileType {
            SAND = 1,
            BLOCK = 2,
        };

        static Tile* SwitchTile(sf::Vector2f position,int Type,World* world){
            Tile* tile;
            switch (Type)
            {
            case 1:
                tile = new Sand(position,world);
                break;
            
            default:
                tile = new Tile(position);
                break;
            }
            return tile;
        }
};

#endif // TIlE_HANDLER_H