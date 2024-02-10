#include "srch_score.h"
#include "ui_srch_score.h"

Srch_score::Srch_score(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Srch_score)
{
    ui->setupUi(this);
    ui->SEX_cb->addItem("");
    ui->SEX_cb->addItem("F");
    ui->SEX_cb->addItem("M");

    ui->SCORE_cb->addItem("");
    ui->SCORE_cb->addItem("90-100");
    ui->SCORE_cb->addItem("80-90");
    ui->SCORE_cb->addItem("60-80");
    ui->SCORE_cb->addItem("<60");
}

Srch_score::~Srch_score()
{
    delete ui;
}

void Srch_score::on_btn_srch_clicked()
{
    //查询成绩
}


void Srch_score::on_btn_leave_clicked()
{
    //离开查询成绩
    this->close();
}

