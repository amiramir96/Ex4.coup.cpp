#pragma once
#include "Player.hpp"

namespace coup
{
    class Captain : public Player
    {
        public:
            Captain(Game &ref_game, const std::string& name);
            ~Captain(){}
            std::string role(){return "Captain";}
            void steal(Player &target);
            void block(Player &target);
    };    
}