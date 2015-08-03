#include "cell_labyrinth.h"

Cell_labyrinth::Cell_labyrinth()
{

}

Cell_labyrinth::Cell_labyrinth(QPair<int, int> coor, QPair<char, int> value_color)
    : value_(value_color.first)
    , coordinates_(coor)
    , change_(false)
    , start_colors_(value_color.second)
{
   colors_.insert(start_colors_);
}

QString Cell_labyrinth::get_mark()
{
    return value_coil_;
}

QSet<int> Cell_labyrinth::get_colors()
{
    return colors_;
}

QPair<int, int> Cell_labyrinth::get_coordinates()
{
    return coordinates_;
}

bool Cell_labyrinth::change_colors(QSet<int> current_colors)
{
    if ((value_ == 's')||(value_ == 'x'))
        return false;

    else
    {
        QSet<int> new_colors;

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

QChar Cell_labyrinth::get_value()
{
    return value_;
}

bool Cell_labyrinth::change()
{
    return change_;
}
