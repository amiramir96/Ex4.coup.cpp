#pragma once
#include "Player.hpp"

namespace coup
{
    class Ambassador : public Player
    {
        public:
            Ambassador(Game &ref_game, const std::string &name);
            ~Ambassador(){}
            std::string role(){return "Ambassador";}
            void transfer(Player &from, Player &to);
            void block(Player& target);
    };    
}