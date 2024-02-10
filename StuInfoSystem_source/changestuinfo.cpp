#include "changestuinfo.h"
#include "ui_changestuinfo.h"

ChangeStuInfo::ChangeStuInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeStuInfo)
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

ChangeStuInfo::~ChangeStuInfo()
{
    delete ui;
}

void ChangeStuInfo::on_btn_checkChange_accepted()
{
    //修改学生信息
}


void ChangeStuInfo::on_btn_checkChange_rejected()
{
    //取消修改
    this->close();
}

