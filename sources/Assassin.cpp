#include "Assassin.hpp"

namespace coup
{
    Assassin::Assassin(Game &ref_game, const std::string& name): Player(ref_game, name){}

    void Assassin::coup(Player &target)
    {
        this->game.assassin_coup(*this, target);
    }
}