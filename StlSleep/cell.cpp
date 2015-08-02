#include "cell.h"

Cell::Cell()
{

}

Cell::Cell(std::pair<int, int> coor, std::pair<char, int> value_color)
    : value_(value_color.first)
    , coor_(coor)
    , change_(false)
    , start_colors_(value_color.second)
{
    colors_.insert(start_colors_);
}

Cell::~Cell(){}

std::pair<int, int> Cell::get_coordinates()
{
    return coor_;
}

std::set<int> Cell::get_colors()
{
    return colors_;
}

bool Cell::change_colors(std::set<int> current_colors)
{
    if ((value_ == 's')||(value_ == 'x'))
        return false;

    else
    {
        std::set<int> new_colors;

        for (auto j = current_colors.begin(); j != current_colors.end(); ++j)
        {
            int new_color = (start_colors_)|(*j);
            if ((!change_)||(colors_.find(new_color) == colors_.end()))
                new_colors.insert(new_color);
        }
        if (!new_colors.empty())
        {
            if (change_)
                for (auto i = new_colors.begin(); i != new_colors.end(); ++i)
                    colors_.insert(*i);
            else
                colors_ = new_colors;
            change_ = true;
            return true;
        }
        else
            return false;
    }

}

char Cell::get_value()
{
    return value_;
}

bool Cell::change()
{
    return change_;
}

