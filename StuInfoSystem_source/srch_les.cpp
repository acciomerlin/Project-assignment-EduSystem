#include "srch_les.h"
#include "ui_srch_les.h"

Srch_Les::Srch_Les(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Srch_Les)
{
    ui->setupUi(this);
    ui->TYPE_cb->addItem("");
    ui->TYPE_cb->addItem("公选");
    ui->TYPE_cb->addItem("公必");
    ui->TYPE_cb->addItem("专必");
    ui->TYPE_cb->addItem("专选");
    ui->TYPE_cb->addItem("跨专业");

    ui->TEST_cb->addItem("");
    ui->TEST_cb->addItem("闭卷");
    ui->TEST_cb->addItem("开卷");
    ui->TEST_cb->addItem("项目考核");
}

Srch_Les::~Srch_Les()
{
    delete ui;
}

void Srch_Les::on_btn_srch_clicked()
{

}


void Srch_Les::on_btn_leave_clicked()
{
    //关闭搜索课程窗口
    this->close();
}

