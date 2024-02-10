#include "changelesinfo.h"
#include "ui_changelesinfo.h"

ChangeLesInfo::ChangeLesInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeLesInfo)
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

ChangeLesInfo::~ChangeLesInfo()
{
    delete ui;
}

void ChangeLesInfo::on_btn_checkChange_rejected()
{
    //取消返回
    this->close();
}


void ChangeLesInfo::on_btn_checkChange_accepted()
{
    //点击确认修改按钮
}

