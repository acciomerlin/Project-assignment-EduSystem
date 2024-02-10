#include "srch_stu.h"
#include "ui_srch_stu.h"

Srch_stu::Srch_stu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Srch_stu)
{
    ui->setupUi(this);
    ui->SEX_cb->addItem("");
    ui->SEX_cb->addItem("F");
    ui->SEX_cb->addItem("M");

    ui->YEAR_cb->addItem("");
    for(int i = 0;i < 30;i++){
        int year = 2000+i;
        ui->YEAR_cb->addItem(QString::number(year));
    }
}

Srch_stu::~Srch_stu()
{
    delete ui;
}

void Srch_stu::on_btn_srch_clicked()
{

}


void Srch_stu::on_btn_leave_clicked()
{
    //离开查找
    this->close();
}

