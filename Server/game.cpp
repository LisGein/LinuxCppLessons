#include "game.h"
#include <iostream>


Game::Game(BaseConnection *connection)
    :end_game_(false)
    , connection_(connection)
{
    first_player_ = connection_->first_turn();

    std::cout << "first_turn = " << first_player_<< std::endl;

    for (int i = 1; i <= WIDTH; ++i)//заполнения поля для игры
    {
        for (int j = 1; j <= HEIGHT; ++j)
        {
            point_t pos(j, i);
            pair_pos_.insert(std::pair<point_t, char>(pos,'*'));
        }
    }

    directions.push_back(point_t(1, 0));//по х
    directions.push_back(point_t(-1, 0));

    directions.push_back(point_t(1, 1));//диагональ с лева на право
    directions.push_back(point_t(-1, -1));

    directions.push_back(point_t(-1, 1));//диагональ с право на лево
    directions.push_back(point_t(1, -1));

    directions.push_back(point_t(0, 1));//по у
    directions.push_back(point_t(0, -1));

    draw_field();
}

Game::~Game(){}
bool Game::finish()
{
    return end_game_;
}

void Game::make_oponent_step()
{
    point_t pos = connection_->recv_step();
    put_symbol_on_field(pos, (!first_player_) ? 'X' : 'O');
    draw_field();
    check_win_combination(pos);
}

void Game::make_my_step()
{
    point_t pos = read_pos();
    connection_->send_step(pos);
    put_symbol_on_field(pos, first_player_ ? 'X' : 'O');
    draw_field();
    check_win_combination(pos);
}
void Game::make_step()
{
    if (first_player_)
    {
        make_my_step();
        make_oponent_step();
    }
    else
    {
        make_oponent_step();
        make_my_step();
    }
}

void Game::draw_field()
{
    std::cout << "\033[2J\033[1;1H";
    int id = 1;
    for (auto iter=pair_pos_.begin(); iter!=pair_pos_.end(); ++iter)
    {
        if(id != WIDTH)
        {
            std::cout << iter->second << " ";
            id++;
        }
        else
        {
            std::cout << iter->second << " " << '\n';
            id=1;
        }
    }
}

void Game::put_symbol_on_field(point_t const & pos, char symb)
{
    pair_pos_.erase(pos);
    pair_pos_.insert(std::pair<point_t, char>(pos, symb));
}

point_t Game::read_pos()
{
    point_t pos;
    while (true)
    {
        std::cout << "Your turn:" << std::endl;
        std::cin >> pos.x >> pos.y;

        if ((pos.x > WIDTH)||(pos.y > HEIGHT))
            std::cout << "Invalid input. Try again:\n";
        else
            return pos;
    }
}

void  Game::check_win_combination(point_t const & pos)
{
    point_t find_prev_pos = pos;
    int sign = 0;
    int numb_char = 1;
    for (point_t const &direction : directions)
    {
        find_prev_pos.x = pos.x + direction.x;
        find_prev_pos.y = pos.y + direction.y;
        while((find_prev_pos.x <= WIDTH)||(find_prev_pos.y <= HEIGHT)||(find_prev_pos.x >= 0)||(find_prev_pos.y >= 0))
        {
            sign++;
            auto it =  pair_pos_.find(pos);
            auto iter = pair_pos_.find(find_prev_pos);
            if (iter->second == it->second)
            {
                numb_char++;
                find_prev_pos.x += direction.x;
                find_prev_pos.y += direction.y;
            }
            else
            {
                if (numb_char >=4)
                {
                    end_game_ = true;
                }
                if (sign % 2 == 0)
                    numb_char = 1;
                break;
            }
        }
    }
}

