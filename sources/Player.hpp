#include <iostream>
#pragma once
#include <string>
#include <vector>
#include "Game.hpp"
namespace coup
{
    class Player
    {
        public:
            // const.dest
            Player(Game& curr_game, const std::string &p_name);
            ~Player(){}

            // vars
            Game& game;
            int my_money;
            bool alive;
            std::string lastDecision;
            std::string name;

            // funcs
            void checkMyTurn(bool isCoup = false);
            void income();
            void foreign_aid();
            int coins() const;
            void coup(Player &target);
            void kill(){alive = false;}
            void restore(){alive = true;}

    };
}