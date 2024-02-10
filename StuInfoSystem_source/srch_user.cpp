#include "srch_user.h"
#include "ui_srch_user.h"

srch_user::srch_user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::srch_user)
{
    ui->setupUi(this);
}

srch_user::~srch_user()
{
    delete ui;
}

void srch_user::on_btn_srch_clicked()
{

}

