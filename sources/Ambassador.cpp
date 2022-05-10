#include "Ambassador.hpp"

namespace coup{
    Ambassador::Ambassador(Game &ref_game, const std::string &name): Player(ref_game, name){} 

    void Ambassador::transfer(Player &from, Player &to)
    {
        this->game.ambassador_transfer(*this, from, to);
    }

    void Ambassador::block(Player& target)
    {
        this->game.ambassador_block(target);
    }
}