#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <cmath>

class Cell
{
public:
    Cell( std::pair<int,int> coor_cell, int role)
        : coor_cell_(coor_cell)
        , role_(role)
        , check_(false)
    {}

    ~Cell(){}

    std::pair<int,int> get_coordinates()
    {
        return coor_cell_;
    }

    int white()
    {
        return role_;
    }
    bool get_check()
    {
        return check_;
    }
    void check()
    {
        check_ = true;
    }

private:
    std::pair<int,int> coor_cell_;
    int role_;
    bool check_;
};

int main()
{
    std::fstream fin("INPUT.txt");

    char x;
    int y;
    fin >> x >> y;
    std::pair<int,int> start_coor(x - 'A', y - 1);
    fin >> x >> y;
    fin.close();
    std::pair<int,int> exit(x - 'A', y - 1);
    std::vector<Cell > chess;
    int size_board = 9;
    int role = 0;
    for (int i = 0; i < size_board; ++i)
        for (int j = 0; j < size_board; ++j)
        {
            Cell cell(std::make_pair(i, j), role);
            chess.push_back(cell);
            if (role)
                role = 0;
            else
                role = 1;
        }
    std::vector<Cell > prev_cell;
    for (int i = 0; i < chess.size(); ++i)
        if (chess[i].get_coordinates() == start_coor)
            prev_cell.push_back(chess[i]);
    int summ = 0;
    bool find_finish = true;
    for (int i = 0; i < chess.size(); ++i)
        for (int j = 0; j < chess.size(); ++j)
            if ((chess[i].get_coordinates() == exit)&&(chess[i].white())&&(chess[j].get_coordinates() == start_coor)&&(!chess[j].white()))
            {
                find_finish = false;
                summ = -1;
            }
    if ((exit.first > size_board - 1) ||(start_coor.first > size_board - 1)||(exit.second > size_board - 1)||(start_coor.second > size_board - 1)
            || (exit.first < 0) ||(start_coor.first < 0)||(exit.second < 0)||(start_coor.second < 0))
    {
        find_finish = false;
        summ = -1;
    }
    if ((exit.first == start_coor.first)&&(exit.second == start_coor.second ))
    {
        find_finish = false;
        summ = 0;
    }

    while(find_finish)
    {

        std::vector<Cell > next_cell;
        for (int i = 0; i < prev_cell.size(); ++i)
        {
            std::pair<int,int> prev_coor = prev_cell[i].get_coordinates();
            for (int j = 0; j < chess.size(); ++j)
            {
                std::pair<int,int> current_coor = chess[j].get_coordinates();
                std::pair<int,int> diff(std::abs(prev_coor.first - current_coor.first), std::abs(prev_coor.second - current_coor.second));

                if ((((prev_cell[i].white()) && (std::abs(diff.first - diff.second) == 1) && ((diff.first + diff.second) == 3)) ||
                     ((std::abs(diff.first == diff.second))&&(!prev_cell[i].white()))) &&
                        (!chess[j].get_check()))
                {
                    chess[j].check();
                    next_cell.push_back(chess[j]);
                    if (current_coor == exit)
                        find_finish = false;

                }

            }
        }
        if (!next_cell.empty())
        {
            prev_cell = next_cell;
            ++summ;
        }
        else
        {
            find_finish = false;
            summ = -1;
        }
    }

    std::ofstream out("OUTPUT.TXT");
    out << summ << "\n";
    out.close();



    return 0;

}

