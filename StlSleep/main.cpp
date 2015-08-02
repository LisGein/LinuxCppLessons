#include "dataset.h"
#include <cmath>

int main()
{
    Dataset dataset;
    dataset.calc_labyrinth();
    dataset.calc_prev_cell();
    std::vector<Cell> labyrinth = dataset.get_labyrinth();
    std::vector<Cell> prev_cell;
    prev_cell.push_back(dataset.get_prev_cell());

    while (!prev_cell.empty())
    {
        std::vector<Cell> next_cell;
        for (size_t i = 0; i < prev_cell.size(); ++i)
        {
            std::pair<int, int> curr_coor = prev_cell[i].get_coordinates();
            for (size_t j = 0; j < labyrinth.size(); ++j)
            {

                std::pair<int, int> diff_coor(labyrinth[j].get_coordinates().first - curr_coor.first,
                                              labyrinth[j].get_coordinates().second - curr_coor.second);
                if (((abs(diff_coor.first) + abs (diff_coor.second)) == 1)
                        && (labyrinth[j].change_colors(prev_cell[i].get_colors())))
                {
                    next_cell.push_back(labyrinth[j]);
                }
            }

        }

        prev_cell = next_cell;
    }

    Cell exit;
    for (size_t i = 0; i < labyrinth.size(); ++i)
        if (labyrinth[i].get_value() == 'e')
            exit = labyrinth[i];
    dataset.write_data(exit);

    return 0;
}


