#include "Game.hpp"
#include "Player.hpp"
constexpr int STEAL_LEN = 5;
constexpr int COUP = 7;
constexpr int KILL = 3;

namespace coup
{
    //     //funcs
    // std::string turn();
    // std::vector<std::string> players() const;
    // std::string winner();
    // void coup(const std::string&);
    // void uncoup(const std::string&);
    // void advance();
    // void cancelTurn();

    void Game::advance()
    {
        this->game_on = true;
        if (this->curr_char+1 >= this->all_players.size())
        {
            this->curr_char = 0;
        }
        else 
        {
            this->curr_char++;
        }
    }

    void Game::coup(const std::string& player){this->getPlayer(player)->kill();}
    void Game::uncoup(const std::string& player){this->getPlayer(player)->restore();}


    std::vector<std::string> Game::players() const
    {
        std::vector<std::string> output_names;
        for(Player* pl : all_players)
        {
            if(pl->alive){
                output_names.push_back(pl->name);
            }
        }
        return output_names;
    }



    Player* Game::getPlayer(const std::string &name_t)
    {
        for (Player* player : this->all_players)
        {   
            if (player->name == name_t)
            {
                return player;
            }
        }
        return NULL;
    }

    std::string Game::winner()
    {
        if (!this->game_on)
        {
            throw std::logic_error("no winner if game didnt started yet..\n");
        }
        Player* pot_to_win = nullptr;
        int players_alive = 0;
        for (Player* pl : this->all_players)
        {
            if (pl->alive)
            {
                pot_to_win = pl;
                players_alive++;
            }
        }
        if (players_alive > 1)
        {
            throw std::logic_error("game didnt ended yet..\n");
        }
        std::string res;
        if (pot_to_win != nullptr)
        {
            res = pot_to_win->name;
        }
        return res;
    }

    std::string Game::turn()
    {
        if (this->all_players.size() <= 1) {throw std::logic_error("game isnt started yet..\n.");}
        while (!this->all_players.at((size_t)this->curr_char)->alive)
        {
            this->advance();
        }
        return this->all_players.at((size_t)this->curr_char)->name;
    }

    void Game::cancelTurn()
    {
        this->curr_char = (this->curr_char-1) % ((int)this->all_players.size());
    }

    void Game::contessa_block(Player& target)
    {
        if (target.lastDecision.starts_with("coup_"))
        {
            this->uncoup(target.lastDecision.substr(target.lastDecision.find('_')+1, target.lastDecision.length()));
            return;
        }
        throw std::logic_error("how u trying to block somebody who didnt used coup??? \n");
    }

    void Game::captain_steal(Player& src, Player& target)
    {
        this->getPlayer(target.name);
        this->getPlayer(src.name);
        src.checkMyTurn();
        if (target.my_money < 2)
        {
            src.my_money += target.my_money;
            src.lastDecision = "steal_" + target.name + "-" + std::to_string(target.my_money);
            target.my_money = 0;
        }
        else 
        {
            target.my_money -= 2;
            src.my_money += 2;
            src.lastDecision = "steal_" + target.name + "-2";
        }
    }

    void Game::captain_block(Player& target)
    {
        std::string first_four_chars = target.lastDecision.substr(0, (size_t)STEAL_LEN);
        if (first_four_chars == "steal")
        {
            Player* pl = this->getPlayer(target.lastDecision.substr(target.lastDecision.find('_')+1, target.lastDecision.find('-')));
            int stolen = std::stoi(target.lastDecision.substr(target.lastDecision.find('-')+1, target.lastDecision.length()));
            pl->my_money += stolen;
            target.my_money -= stolen;
        }
        else 
        {
            throw std::logic_error("how u trying to block somebody who didnt used steal??? \n");
        }
    }

    void Game::assassin_coup(Player& src, Player& target)
    {    
        src.checkMyTurn(true);
        if (!target.alive)
        {
            this->cancelTurn();
            throw std::logic_error("thefk bro.. pl died already..\n");
        }
        if (src.my_money >= COUP)
        {
            src.game.coup(target.name);
            src.lastDecision = "coup";
            src.my_money -= COUP;
        }
        else if (src.my_money >= KILL)
        {
            src.game.coup(target.name);
            src.lastDecision = "coup_" + target.name;
            src.my_money -= KILL;
        }
        else
        {
            this->cancelTurn();
            throw std::logic_error("this character is already dead....\n");
        }
    }

    void Game::ambassador_transfer(Player& src, Player& from, Player& to)
    {
        src.checkMyTurn();

        if (from.my_money == 0)
        {
            this->cancelTurn();
            throw std::logic_error("not even 1 coin to transfer between the players..\n");
        }

        from.my_money--;
        to.my_money++;
        src.lastDecision = "transfer";
    }
    void Game::ambassador_block(Player& target)
    {
        if (target.lastDecision.starts_with("steal"))
        {
            Player* pl = this->getPlayer(target.lastDecision.substr(target.lastDecision.find('_')+1, target.lastDecision.find('-') - target.lastDecision.find('_') - 1));
            int stolen = std::stoi(target.lastDecision.substr(target.lastDecision.find('-')+1, target.lastDecision.length()));
            pl->my_money += stolen;
            target.my_money -= stolen;
        }
        else
        {
            throw std::logic_error("... u cant block if he didnt used steal...\n");
        }
    }
}