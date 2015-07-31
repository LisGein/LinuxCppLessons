#include "labyrinth.h"

Labyrinth::Labyrinth(int width_labirinth, int height_labirinth)
    : height_(height_labirinth)
    , width_(width_labirinth)
{    
    QString mark;
    mark = 'x';
    for (int i = 0; i < width_; ++i)
    {
        cells_.push_back(Cell_labyrinth(width_, height_, qMakePair(i, -1), mark));
        cells_.push_back(Cell_labyrinth(width_, height_, qMakePair(i, height_), mark));
    }
    for (int i = 0; i < height_; ++i)
    {
        cells_.push_back(Cell_labyrinth(width_, height_, qMakePair(-1, i), mark));
        cells_.push_back(Cell_labyrinth(width_, height_, qMakePair(width_, i), mark));
    }
}

void Labyrinth::add_element(Cell_labyrinth cell)
{
    cells_.push_back(cell);
}

QVector<int> Labyrinth::find_way()
{
        QVector<Cell_labyrinth> prev_cells;
        for (int i = 0; i < cells_.size(); ++i)
            if(cells_[i].get_mark() == "s")
                prev_cells.push_back(cells_[i]);

        while (!prev_cells.empty())
        {
            QVector<Cell_labyrinth> next_cells;
            for (int i = 0; i < prev_cells.size(); ++i)
            {
                QVector<int> current_color = prev_cells[i].get_colors();
                for (int i = 0; i < cells_.size(); ++i)
                    if (cells_[i].get_mark() != "x")
                    {
                        QPair <int, int> next_coor = cells_[i].get_coordinates();
                        QPair <int, int> current_coor =  prev_cells[i].get_coordinates();
                        if ((next_coor == qMakePair(current_coor.first, current_coor.second + 1)) ||
                                (next_coor == qMakePair(current_coor.first + 1, current_coor.second)) ||
                                (next_coor == qMakePair(current_coor.first - 1, current_coor.second)) ||
                                (next_coor == qMakePair(current_coor.first, current_coor.second - 1)))
                        {
                            next_cells.push_back(cells_[i]);
                            cells_[i].change_color(current_color);
                        }

                    }
            }
            prev_cells = next_cells;
        }
        QVector<int> free_price;
        for (int i = 0; i < cells_.size(); ++i)
            if(cells_[i].get_mark() == "e")
                free_price = cells_[i].get_colors();
        return free_price;

}
