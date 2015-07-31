#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <set>

int width = 6;
int heidth = 5;

class Cell
{
public:
    Cell(char value, std::pair<int, int> coor)
        : value_(value)
        , coor_(coor)
        , change_(false)
    {
        if (value == 'r')
            colors_.insert(1000);
        else if (value == 'g')
            colors_.insert(100);
        else if (value == 'b')
            colors_.insert(10);
        else if (value == 'y')
            colors_.insert(1);
        else
            colors_.insert(0);
    }

    ~Cell(){}

    std::pair<int, int> get_coordinates()
    {
        return coor_;
    }

    std::set<int> get_colors()
    {
        return colors_;
    }

    void change_colors(std::set<int> current_colors)
    {
        if ((colors_.size() == 1)&&((*colors_.begin()) == 0))
            colors_ = current_colors;
        else
        {
            std::set<int> new_colors;
            for (auto i = colors_.begin(); i != colors_.end(); ++i)
            {
                for (auto j = current_colors.begin(); j != current_colors.end(); ++j)
                    new_colors.insert(*i|*j);

            }
            colors_ = new_colors;
        }
        change_ = true;
    }
    char get_value()
    {
        return value_;
    }

    bool change()
    {
        return change_;
    }

private:
    char value_;
    std::pair<int, int> coor_;
    std::set <int> colors_;
    bool change_;
};

bool ok_change_colors(std::set<int> current_colors, std::set<int> prev_cell)
{
    if ((current_colors.size() == 1)&&((*current_colors.begin()) == 0))
        return true;
    else
    {
        std::set<int> new_colors;
        for (auto i = current_colors.begin(); i != current_colors.end(); ++i)
        {
            for (auto j = prev_cell.begin(); j != prev_cell.end(); ++j)
                new_colors.insert(*i|*j);
        }
        if ((*current_colors.begin())>(*new_colors.begin()))
            return true;
        else return false;

    }
}

int main()
{
    std::string graf = "srrrrrrrrrrgrgxgrrrrryrbrrrgre";
    int r_price = 1;
    int g_price = 2;
    int b_price = 3;
    int y_price = 4;
    std::vector<Cell> labyrinth;
    for (int i = 0; i < graf.size(); ++i)
    {
        int x = (i >= width) ? (i%width) : (i);
        int y = (i >= width) ? (i/width) : (0);
        labyrinth.push_back(Cell(graf[i], std::make_pair(x, y)));
    }

    std::vector<Cell> prev_cell;
    for (int i = 0; i < labyrinth.size(); ++i)
        if (labyrinth[i].get_value() == 's')
            prev_cell.push_back(labyrinth[i]);



    while (!prev_cell.empty())
    {
        std::vector<Cell> next_cell;
        for (int i = 0; i < prev_cell.size(); ++i)
        {
            std::pair<int, int> curr_coor = prev_cell[i].get_coordinates();
            for (int j = 0; j < labyrinth.size(); ++j)
            {
                if (labyrinth[j].get_value()!= 'x')
                {
                    std::pair<int, int> next_coor = labyrinth[j].get_coordinates();

                    if (((curr_coor.first+1 == next_coor.first)&&(curr_coor.second == next_coor.second))||
                            ((curr_coor.first == next_coor.first)&&(curr_coor.second+1 == next_coor.second))||
                            ((curr_coor.first-1 == next_coor.first)&&(curr_coor.second == next_coor.second))||
                            ((curr_coor.first == next_coor.first)&&(curr_coor.second-1 == next_coor.second)))
                    {
                        if ((ok_change_colors(labyrinth[j].get_colors(), prev_cell[i].get_colors()))||(!labyrinth[j].change()))
                        {
                            labyrinth[j].change_colors(prev_cell[i].get_colors());
                            next_cell.push_back(labyrinth[j]);
                        }
                    }

                }

            }
        }
        prev_cell = next_cell;
    }


    std::set<int> result_colors;
    for (int i = 0; i < labyrinth.size(); ++i)
        if (labyrinth[i].get_value() == 'e')
            result_colors = labyrinth[i].get_colors();
    std::set<int> result_price;
    for (auto i = result_colors.begin(); i != result_colors.end(); ++i)
    {
        result_price.insert( (*i)/1000*r_price + (*i)/100*g_price + (*i)/10*b_price + (*i)*y_price);
        std::cout << *i << "\n";
    }
    for (auto i = result_price.begin(); i != result_price.end(); ++i)
        std::cout << *i << "\n";
    return 0;
}
