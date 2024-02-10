#include "recordscore.h"
#include "ui_recordscore.h"

RecordScore::RecordScore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordScore)
{
    ui->setupUi(this);
}

RecordScore::~RecordScore()
{
    delete ui;
}

void RecordScore::on_btn_checkChange_accepted()
{
    //改成绩不在这里真正实现
}


void RecordScore::on_btn_checkChange_rejected()
{
    //退出成绩修改
    this->close();
}

