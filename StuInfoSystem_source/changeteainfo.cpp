#include "changeteainfo.h"
#include "ui_changeteainfo.h"

ChangeTeaInfo::ChangeTeaInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeTeaInfo)
{
    ui->setupUi(this);
    ui->SEX_cb->addItem("");
    ui->SEX_cb->addItem("F");
    ui->SEX_cb->addItem("M");

    ui->TITLE_cb->addItem("");
    ui->TITLE_cb->addItem("讲师(Lecturer)");
    ui->TITLE_cb->addItem("助教(Assistant Professor)");
    ui->TITLE_cb->addItem("副教授(Associate Professor)");
    ui->TITLE_cb->addItem("教授(Professor)");
}

ChangeTeaInfo::~ChangeTeaInfo()
{
    delete ui;
}

void ChangeTeaInfo::on_btn_checkChange_accepted()
{
    //确认修改教师信息
}


void ChangeTeaInfo::on_btn_checkChange_rejected()
{
    //取消修改教师信息
    this->close();
}

