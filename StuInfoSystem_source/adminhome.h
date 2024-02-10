#ifndef ADMINHOME_H
#define ADMINHOME_H

#include <QWidget>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QModelIndex>
#include <QLabel>


#include "changeinfo.h"
#include "ui_changeinfo.h"
#include "srch_user.h"
#include "ui_srch_user.h"
#include "changelesinfo.h"
#include "ui_changelesinfo.h"
#include "srch_les.h"
#include "ui_srch_les.h"
#include "changeteainfo.h"
#include "ui_changeteainfo.h"
#include "srch_tea.h"
#include "ui_srch_tea.h"
#include "changestuinfo.h"
#include "ui_changestuinfo.h"
#include "srch_stu.h"
#include "ui_srch_stu.h"

enum Flag {
    StuModel,
    TeaModel,
    AdminModel
};

namespace Ui {
class AdminHome;
}

class AdminHome : public QWidget
{
    Q_OBJECT

public:
    explicit AdminHome(QWidget *parent = nullptr);
    ~AdminHome();

    Ui::AdminHome *ui;
private slots:

    void on_radioButton_2_clicked();

    void on_stu_rb_clicked();

    void on_admin_rb_clicked();

    void on_user_tableView_doubleClicked(const QModelIndex &index);

    void updateUserTable();

    void on_btn_srchUser_clicked();

    void srchUserTable();

    void on_les_tableView_doubleClicked(const QModelIndex &index);

    void updateLesTable();

    void on_btn_bckLogin_clicked();

    void on_btn_addLes_clicked();

    void addLesRecord();

    void on_btn_delLes_clicked();

    void on_btn_srchLes_clicked();

    void srchLesTable();

    void on_tea_tableView_doubleClicked(const QModelIndex &index);

    void updateTeaTable();

    void on_btn_addTea_clicked();

    void addTeaRecord();

    void on_btn_delTea_clicked();

    void on_btn_srchTea_clicked();

    void srchTeaTable();

    void on_stu_tableView_doubleClicked(const QModelIndex &index);

    void updateStuTable();

    void on_btn_addStu_clicked();

    void addStuRecord();

    void on_btn_delStu_clicked();

    void on_btn_srchStu_clicked();

    void srchStuTable();

    void on_btn_originU_clicked();

    void on_btn_originL_clicked();

    void on_btn_originT_clicked();

    void on_btn_originS_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlQueryModel *stu_qmodel;
    QSqlQueryModel *tea_qmodel;
    QSqlQueryModel *les_qmodel;
    QSqlQueryModel *user_qmodel;
    QModelIndex currentIndexModel;

    //重置人员密码
    ChangeInfo changeInfo;
    int model_flag = StuModel;

    //重置功能用户查找
    srch_user srch_u;

    //课程信息修改
    ChangeLesInfo changelesinfo;

    //课程查找窗口
    Srch_Les srch_l;

    //教师信息修改
    ChangeTeaInfo changeteainfo;

    //教师查找窗口
    Srch_Tea srch_t;

    //学生信息修改
    ChangeStuInfo changestuinfo;

    //学生查找窗口
    Srch_stu srch_s;
};

#endif // ADMINHOME_H
