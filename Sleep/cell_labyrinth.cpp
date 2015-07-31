#include "cell_labyrinth.h"

Cell_labyrinth::Cell_labyrinth()
{

}

Cell_labyrinth::Cell_labyrinth(int width_labirinth, int height_labirinth, QPair<int, int> coor, QString value_coil)
    : value_coil_(value_coil)
    , coordinates_(coor)
    , width_(width_labirinth)
    , height_(height_labirinth)
{
    if (value_coil == "r")
        colors_.push_back(0b1000);
    else if (value_coil == "g")
        colors_.push_back(0b0100);
    else if (value_coil == "b")
        colors_.push_back(0b0010);
    else if (value_coil == "y")
        colors_.push_back(0b0001);
    else
        colors_.push_back(0b0000);
}

QString Cell_labyrinth::get_mark()
{
    return value_coil_;
}

QVector<int> Cell_labyrinth::get_colors()
{
    return colors_;
}

QPair<int, int> Cell_labyrinth::get_coordinates()
{
    return coordinates_;
}

int Cell_labyrinth::change_color(QVector<int> current_color)
{
    if (!colors_.empty())
    {
        QVector<int> new_colors_;
        for (int i = 0; i < colors_.size(); ++i)
            for (int j = 0; j < current_color.size(); ++j)
                if (colors_[i] != current_color[j])
                    new_colors_.push_back(colors_[i] | current_color[j]);
        colors_.clear();

        for (int i = 0; i < new_colors_.size()-1; ++i)
            colors_.push_back(new_colors_[i] < new_colors_[i+1] ? new_colors_[i] : new_colors_[i+1]);



    }
    else
        colors_ = current_color;
}

