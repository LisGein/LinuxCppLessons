#pragma once
#include <map>
#include <string>
#include <vector>
#include <fstream>


class Dataset
{
public:
    Dataset();
    ~Dataset();
    void calc_labyrinth();
    void calc_prev_cell();
    std::vector<Cell> get_labyrinth();
    Cell get_prev_cell();
    void write_data(Cell& exit);

private:
    int width_;
    int heidth_;
    int r_price_, g_price_, b_price_, y_price_;
    std::string graf_;
    std::vector<Cell> labyrinth_;
    Cell prev_cell_;

    int convert_price(int bitset);
};
