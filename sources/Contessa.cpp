#include "Contessa.hpp"

namespace coup
{
    Contessa::Contessa(Game &ref_game, const std::string& name): Player(ref_game, name){}

    void Contessa::block(Player &target)
    {
        this->game.contessa_block(target);
    }

}