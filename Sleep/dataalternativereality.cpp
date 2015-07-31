#include "dataalternativereality.h"
#include "ui_dataalternativereality.h"

DataAlternativeReality::DataAlternativeReality(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataAlternativeReality)
{
    ui->setupUi(this);
    connect(ui->R, SIGNAL(selectionChanged()), ui->R, SLOT(clear()));
    connect(ui->G, SIGNAL(selectionChanged()), ui->G, SLOT(clear()));
    connect(ui->B, SIGNAL(selectionChanged()), ui->B, SLOT(clear()));
    connect(ui->Y, SIGNAL(selectionChanged()), ui->Y, SLOT(clear()));
    connect(ui->height, SIGNAL(selectionChanged()), ui->height, SLOT(clear()));
    connect(ui->wigth, SIGNAL(selectionChanged()), ui->wigth, SLOT(clear()));
    connect(ui->description, SIGNAL(selectionChanged()), ui->description, SLOT(clear()));
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(check_data()));
}

DataAlternativeReality::~DataAlternativeReality()
{
    delete ui;
}
void DataAlternativeReality::check_data()
{
    QString error_var;

    int width = ui->wigth->toPlainText().toInt();
    int height = ui->height->toPlainText().toInt();

    QString description = ui->description->toPlainText();
    description.replace("\n", "");

    if (description.size() != (width*height))//||(description.size() > (width*height + height)))
        error_var = "description";
//    else if ((description.count("S") != 1) || (description.count("E") != 1))
//        error_var = "description";

    if ((width > 50)||(height > 50))
        if (error_var.size() != 0)
            error_var += ", width or height";
        else
            error_var = "width or height";

    int R = ui->R->toPlainText().toInt();
    int G = ui->G->toPlainText().toInt();
    int B = ui->B->toPlainText().toInt();
    int Y = ui->Y->toPlainText().toInt();
    if ((R > 100)||(G > 100)||(B > 100)||(Y > 100))
        if (error_var.size() != 0)
            error_var += ", price";
        else
            error_var = "price";

    if (error_var.size() == 0)
        emit ready_reality(width, height, R, G, B, Y, description);
    else
        emit error_input(error_var);
}
