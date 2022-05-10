#pragma once
#include "Player.hpp"

namespace coup
{
    class Assassin : public Player
    {
        public:
            Assassin(Game &ref_game, const std::string& name);
            ~Assassin(){}
            std::string role(){return "Assassin";}
            void coup(Player &target);
    };    
}