#include "dataset.h"

Dataset::Dataset()
{

    std::ifstream fin("INPUT.txt");
    fin >> heidth_ >> width_ >> r_price_ >> g_price_  >> b_price_ >> y_price_;
    std::string data_read;
    graf_ = "";
    while (fin >> data_read)
    {
        graf_ += data_read;
    }
    data_read = "";
    for (size_t i = 0; i < graf_.size(); ++i)
        data_read += std::tolower(graf_[i]);
    graf_ = data_read;
}

Dataset::~Dataset()
{

}

void Dataset::calc_labyrinth()
{
    std::map<char, int> const color2flag {
        { 'r', 0b1000 },
        { 'g', 0b0100 },
        { 'b', 0b0010 },
        { 'y', 0b0001 },
    };
    for (size_t i = 0; i < graf_.size(); ++i)
    {
        size_t x = (i >= width_) ? (i%width_) : (i);
        size_t y = (i >= width_) ? (i/width_) : (0);
        auto cell_color = color2flag.find(graf_[i]);
        if (cell_color != color2flag.end())
            labyrinth_.push_back(Cell(std::make_pair(x, y), *cell_color));
        else
        {
            std::pair<char, int> cell(graf_[i], 0b0000);
            labyrinth_.push_back(Cell(std::make_pair(x, y), cell));
        }
    }
}

void Dataset::calc_prev_cell()
{
    for (size_t i = 0; i < labyrinth_.size(); ++i)
        if (labyrinth_[i].get_value() == 's')
            prev_cell_ = labyrinth_[i];
}

std::vector<Cell> Dataset::get_labyrinth()
{
    return labyrinth_;
}

Cell Dataset::get_prev_cell()
{
    return prev_cell_;
}

int Dataset::convert_price(int bitset)
{
    std::vector <int> result;
    int next = bitset;
    while (next != 0)
    {
        result.push_back(next % 2);
        next = next / 2;
    }
    int result_bitset = 0;
    int idx = 1;
    for (size_t i = 0; i < result.size(); ++i)
    {
        result_bitset +=  result[i] * idx;
        idx *= 10;
    }
    return result_bitset;
}

void Dataset::write_data(Cell& exit)
{
    std::ofstream out_summ("OUTPUT.TXT");
    if (exit.change())
    {
        std::set<int> result_colors = exit.get_colors();
        std::set<int> result;

        for (auto idx = result_colors.begin(); idx != result_colors.end(); ++idx)
        {
            int convert = convert_price(*idx);
            int r = ((convert)/1000 * r_price_);
            int g  = ((convert)/100 % 10 * g_price_);
            int b = (((convert)/10) % 10)* b_price_;
            int y = ((convert)%10) * y_price_;
            result.insert(r + g + b + y);
        }

        out_summ << (*result.begin());
    }
    else
        out_summ << "Sleep\n";
    out_summ.close();
}

