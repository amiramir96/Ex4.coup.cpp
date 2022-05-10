#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace coup
{
    class Player;

    class Game 
    {
        public:
            // const,dest
            Game() = default;
            ~Game() = default;
            
            // vars
            std::vector<Player*> all_players;
            int curr_char;
            bool game_on;

            //funcs
            std::vector<std::string> players() const;
            std::string turn();
            std::string winner();
            Player* getPlayer(const std::string&);
            void coup(const std::string&);
            void uncoup(const std::string&);
            void advance();
            void cancelTurn();
            void contessa_block(Player&);
            void captain_block(Player&);
            void ambassador_block(Player&);
            void captain_steal(Player&, Player&); 
            void assassin_coup(Player&, Player&);
            void ambassador_transfer(Player&, Player&, Player&);

    };
}