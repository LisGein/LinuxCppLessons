#include "confusion_matrix.h"

ConfusionMatrix::ConfusionMatrix(size_t dim)
  :dim_(dim)
{
  confusion_matrix_.resize(dim_);
  for (size_t i=0; i < confusion_matrix_.size(); ++i)
    confusion_matrix_[i].resize(dim_);
}

void ConfusionMatrix::increment(std::vector<char> const &numb, std::vector<char> const &find_numb)
{
  int line, column;
  for (size_t i = 0; i < dim_; ++i)
    {
      if (numb[i] != 0)
        line = i;
      if (find_numb[i] != 0)
        column = i;
    }
    confusion_matrix_[line][column] ++;
}

double ConfusionMatrix::f_1()
{
  double precision = 0;
  double recallc = 0;
  std::vector<double> div_precision;
  std::vector<double> div_recallc;
  for (size_t i = 0; i < dim_; ++i)
    {
      int summ_precision = 0;
      int summ_recallc = 0;
      precision = confusion_matrix_[i][i];
      recallc = confusion_matrix_[i][i];
      for (size_t k = 0; k < dim_; ++k)
        {
          summ_precision += confusion_matrix_[i][k];
          summ_recallc += confusion_matrix_[k][i];
        }
      precision /= summ_precision;
      div_precision.push_back(precision);
      recallc /= summ_recallc;
      div_recallc.push_back(recallc);
    }
  precision = 0;
  recallc = 0;
  for (size_t i = 0; i < dim_; ++i)
    {
      precision += div_precision[i];
      recallc += div_recallc[i];
    }
  precision /= dim_;
  recallc /= dim_;
  double F = 2 * ((precision * recallc)/(precision + recallc));
  return F;
}

void ConfusionMatrix::clear_confusion_matrix()
{
  confusion_matrix_.clear();
  confusion_matrix_.resize(dim_);
  for (size_t i=0; i < confusion_matrix_.size(); ++i)
    confusion_matrix_[i].resize(dim_);
}
