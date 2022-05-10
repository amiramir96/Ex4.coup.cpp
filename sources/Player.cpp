#include "Player.hpp"
constexpr int MAX_MONEY = 10;
constexpr int MIN_COUP = 7;
constexpr int MAX_PLAYERS = 6;
namespace coup
{
    Player::Player(Game& curr_game,const std::string &p_name): game{curr_game} ,name{p_name} , my_money{0}, alive{true}
    {
        if (this->game.players().size() < MAX_PLAYERS && !this->game.game_on)
        {
            this->game.all_players.push_back(this);
        }
        else 
        {
            throw std::logic_error("cannot load more than 6 players to the game -.-\n");
        }
    }

    void Player::checkMyTurn(bool isCoup)
    {
        if (this->my_money >= MAX_MONEY && !isCoup){throw std::logic_error("cannot continue since the current player crossed the 10 money pts. \n");}
        if (this->game.turn() != this->name) {throw std::logic_error("the fk? not ur turn..\n");}
        this->game.advance();
    }
    
    void Player::income()
    {
        checkMyTurn();
        this->my_money++;
        this->lastDecision = "income";
    }

    void Player::foreign_aid()
    {
        checkMyTurn();
        this->my_money++;
        this->my_money++;
        this->lastDecision = "foreign_aid";
    }
    int Player::coins() const
    {
        return this->my_money;
    }

    void Player::coup(Player &target)
    {
        checkMyTurn(true);
        if (!target.alive)
        {
            this->game.cancelTurn();
            throw std::logic_error("cannot coup char that already died......\n"); 
        }
        if (this->my_money >= MIN_COUP)
        {
            this->game.coup(target.name);
            this->lastDecision = "coup";
            this->my_money -= MIN_COUP;
        }
        else 
        {
            this->game.cancelTurn();
            throw std::logic_error("cannot coup with less than 7 money_pts...\n");
        }
    }
} // namespace coup