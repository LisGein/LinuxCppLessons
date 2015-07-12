#pragma once
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <QWidget>
#include <QBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>


class InsetDialog : public QWidget
{
    Q_OBJECT

public:
    explicit InsetDialog(QString name_inset, QWidget *parent = 0);
    ~InsetDialog();
    void read_message(QString str);

private slots:
    void send_private();
signals:
    void send(QString message);

private:
    QString name_inset_;
    QWidget *widget_;
    QVBoxLayout *layout_;
    QTextEdit *in_text_;
    QLineEdit *out_text_;
    QPushButton *send_message_;
};

