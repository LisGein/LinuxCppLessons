#pragma once

#include <QDialog>
#include <QByteArray>

namespace Ui {
class DataAlternativeReality;
}

class DataAlternativeReality : public QDialog
{
    Q_OBJECT

public:
    explicit DataAlternativeReality(QWidget *parent = 0);
    ~DataAlternativeReality();

private slots:
    void check_data();

private:
    Ui::DataAlternativeReality *ui;

signals:
    void ready_reality(int width, int height, int R, int G, int B, int Y, QString description);
    void error_input(QString error_var);
};
