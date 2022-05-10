
#include "Captain.hpp"
namespace coup
{
    Captain::Captain(Game &ref_game, const std::string &name): Player(ref_game, name){}

    void Captain::steal(Player &target)
    {
        this->game.captain_steal(*this ,target);
    }

    void Captain::block(Player &target)
    {
        this->game.captain_block(target);
    }
}