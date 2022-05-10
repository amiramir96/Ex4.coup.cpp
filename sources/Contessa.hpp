#pragma once
#include "Player.hpp"

namespace coup
{
    class Contessa : public Player
    {
        public:
            Contessa(Game &ref_game, const std::string& name);
            ~Contessa(){}
            std::string role(){return "Contessa";}
            void block(Player &target);
    };    
}