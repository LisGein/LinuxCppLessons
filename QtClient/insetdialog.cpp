#include "insetdialog.h"

InsetDialog::InsetDialog(QString name_inset, QWidget *parent)
    : QWidget(parent)
    , name_inset_(name_inset)
    , widget_(new QWidget)
    , layout_(new QVBoxLayout)
    , in_text_(new QTextEdit)
    , out_text_(new QLineEdit)
    , send_message_(new QPushButton("&Send"))
{
    connect(send_message_, SIGNAL(clicked(bool)), SLOT(send_private()));
    connect(out_text_, SIGNAL(returnPressed()), this, SLOT(send_private()));
    in_text_->setReadOnly(true);
    layout_->addWidget(in_text_);
    layout_->addWidget(out_text_);
    layout_->addWidget(send_message_);
    setLayout(layout_);

}

InsetDialog::~InsetDialog()
{
}

void InsetDialog::send_private()
{
    QString message = "@" + name_inset_ + " ";
    message.append(out_text_->text());
    emit send(message);
    out_text_->clear();
}
void InsetDialog::read_message(QString str)
{
    in_text_->append(str);
}
