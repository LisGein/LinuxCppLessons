#include "matrix.h"


Matrix::Matrix()
    :C_(-1444)
    , size_matrix_(4)
{
    for(int i = 0; i < size_matrix_; ++i)
        for(int j = 0; j < size_matrix_; ++j)
            matrix_[i][j] = 0;
    for(int i = 0; i < size_matrix_; ++i)
        matrix_[i][i] = 1;
    matrix_[size_matrix_][size_matrix_-1] = -1/C_;

}

point_3i Matrix::transform(float x, float y, float z)
{
    int new_x = matrix_[0][0]*x + matrix_[1][0]*y + matrix_[2][0]*z + matrix_[3][0]*1;
    int new_y = matrix_[0][1]*x + matrix_[1][1]*y + matrix_[2][1]*z + matrix_[3][1]*1;
    int new_z = matrix_[0][2]*x + matrix_[1][2]*y + matrix_[2][2]*z + matrix_[3][2]*1;
    return point_3i(new_x/(1-z/C_),new_y/(1-z/C_), new_z/(1-z/C_));
}
