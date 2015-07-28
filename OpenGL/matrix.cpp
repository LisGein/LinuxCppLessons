#include "matrix.h"


Matrix::Matrix()
    : size_matrix_(4)
{
    matrix_.resize(size_matrix_);
}


void Matrix::identity()
{
    for(int i = 0; i < size_matrix_; ++i)
        for(int j = 0; j < size_matrix_; ++j)
            matrix_[i].push_back(i==j ? 1.f : 0.f);

}

void Matrix::view_port(int x, int y, int w, int h)
{
    identity();
    matrix_[0][3] = x+w/2.f;
    matrix_[1][3] = y+h/2.f;
    matrix_[2][3] = depth_/2.f;

    matrix_[0][0] = w/2.f;
    matrix_[1][1] = h/2.f;
    matrix_[2][2] = depth_/2.f;
}

QVector<float>& Matrix::operator[](int i)
{
    Q_ASSERT((i>=0) && (i<size_matrix_));
    return matrix_[i];
}

Matrix Matrix::operator*(Matrix& a)
{
    Matrix matrix;
    matrix.identity();
    for(int j = 0; j < size_matrix_; ++j)
        for(int i = 0; i < size_matrix_; ++i)
        {
            matrix[j][i] = 0.f;
            for(int k = 0; k < size_matrix_; ++k)
                matrix[j][i] += matrix_[j][k] * a[k][i];
        }
    return matrix;
}

point_3f Matrix::operator*(point_3f a)
{
    point_3f result;
    float coor_diff = matrix_[3][0] * a.x + matrix_[3][1] *a.y + matrix_[3][2] * a.z + matrix_[3][3];
    result.x = (matrix_[0][0] * a.x + matrix_[0][1] *a.y + matrix_[0][2] * a.z + matrix_[0][3])/coor_diff;
    result.y = (matrix_[1][0] * a.x + matrix_[1][1] *a.y + matrix_[1][2] * a.z + matrix_[1][3])/coor_diff;
    result.z = (matrix_[2][0] * a.x + matrix_[2][1] *a.y + matrix_[2][2] * a.z + matrix_[2][3])/coor_diff;
    return result;
}


Matrix lookat(point_3f eye, point_3f center, point_3f up)
{
    point_3f z = (eye-center).normalize();
    point_3f x = (up ^ z).normalize();
    point_3f y = (z ^ x).normalize();

    Matrix Minv;
    Minv.identity();
    Matrix Tr;
    Tr.identity();

    for (int t = 0; t < 3; ++t)
    {
        Tr[t][3] = -center[t];
        Minv[0][t] = x[t];
        Minv[1][t] = y[t];
        Minv[2][t] = z[t];
    }
    return Minv*Tr;
}


