#include "Duke.hpp"

namespace coup
{
    Duke::Duke(Game &ref_game, const std::string& name): Player(ref_game, name)
    {}

    void Duke::tax()
    {
        checkMyTurn();
        this->my_money++;
        this->my_money++;
        this->my_money++;
        this->lastDecision = "tax";
    }
    
    void Duke::block(Player &target)
    {
        if (target.lastDecision == "foreign_aid")
        {
            target.my_money--;
            target.my_money--;
        }
        else 
        {
            throw std::logic_error("._. sync prob? how u got into tax ? \n");
        }
    }
}