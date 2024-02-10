#include "srch_tea.h"
#include "ui_srch_tea.h"

Srch_Tea::Srch_Tea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Srch_Tea)
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

Srch_Tea::~Srch_Tea()
{
    delete ui;
}

void Srch_Tea::on_btn_srch_clicked()
{
    //查找
}


void Srch_Tea::on_btn_leave_clicked()
{
    //离开查找
    this->close();
}

