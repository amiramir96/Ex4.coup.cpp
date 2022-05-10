#pragma once
#include "Player.hpp"

namespace coup
{
    class Duke : public Player
    {
        public:
            Duke(Game&,const std::string&);
            ~Duke(){}
            std::string role(){return "Duke";}
            void tax();
            static void block(Player &target);
    };    
}