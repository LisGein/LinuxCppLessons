#pragma once
#include <set>
#include <utility>


class Cell
{
public:
    Cell();
    Cell(std::pair<int, int> coor, std::pair<char, int> value_color);
    ~Cell();
    std::pair<int, int> get_coordinates();
    std::set<int> get_colors();
    bool change_colors(std::set<int> current_colors);
    char get_value();
    bool change();

private:
    char value_;
    std::pair<int, int> coor_;
    std::set <int> colors_;
    int start_colors_;
    bool change_;
};

