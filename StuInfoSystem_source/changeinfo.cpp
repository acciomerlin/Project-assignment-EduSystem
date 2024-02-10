#include "changeinfo.h"
#include "ui_changeinfo.h"

ChangeInfo::ChangeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeInfo)
{
    ui->setupUi(this);
}

ChangeInfo::~ChangeInfo()
{
    delete ui;
}

void ChangeInfo::on_btn_checkChange_accepted()
{
    //点击确认修改按钮
}


void ChangeInfo::on_btn_checkChange_rejected()
{
    //取消返回
    this->close();
}

