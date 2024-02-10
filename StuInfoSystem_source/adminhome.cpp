#include "adminhome.h"
#include "ui_adminhome.h"

//窗体构造函数
AdminHome::AdminHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminHome)
{
    ui->setupUi(this);

}

//窗体析构函数
AdminHome::~AdminHome()
{
    delete ui;
}

//账号信息tab中tabView教师
void AdminHome::on_radioButton_2_clicked()  //勾选教师选项，忘记改名了
{
    //关闭查找窗口
    srch_u.close();

    user_qmodel->setQuery("select uid,pwd from teacher");
    ui->user_tableView->setModel(user_qmodel);
    user_qmodel->setHeaderData(0,Qt::Horizontal,"Netid");
    user_qmodel->setHeaderData(1,Qt::Horizontal,"密码");
    model_flag = TeaModel;
}

//账号信息tab中tabView学生
void AdminHome::on_stu_rb_clicked()
{
    //关闭查找窗口
    srch_u.close();

    user_qmodel->setQuery("select uid,pwd from stuinfo");
    ui->user_tableView->setModel(user_qmodel);
    user_qmodel->setHeaderData(0,Qt::Horizontal,"Netid");
    user_qmodel->setHeaderData(1,Qt::Horizontal,"密码");
    model_flag = StuModel;
}

//账号信息tab中tabView管理员
void AdminHome::on_admin_rb_clicked()
{
    //关闭查找窗口
    srch_u.close();

    user_qmodel->setQuery("select uid,pwd from admininfo");
    ui->user_tableView->setModel(user_qmodel);
    user_qmodel->setHeaderData(0,Qt::Horizontal,"Netid");
    user_qmodel->setHeaderData(1,Qt::Horizontal,"密码");
    model_flag = AdminModel;
}

//账号信息tab中双击tabView重置人员密码
void AdminHome::on_user_tableView_doubleClicked(const QModelIndex &index)
{
    QString username = index.siblingAtColumn(0).data().toString();
    QString password = index.siblingAtColumn(1).data().toString();
    changeInfo.show();
    changeInfo.ui->ID_line->setText(username);
    changeInfo.ui->PWD_line->setText(password);

    disconnect(changeInfo.ui->btn_checkChange, &QDialogButtonBox::accepted, this, &AdminHome::updateUserTable); //每次先断再连不然会多次连接下面的QM会被多次call
    connect(changeInfo.ui->btn_checkChange,&QDialogButtonBox::accepted,this,QOverload<>::of(&AdminHome::updateUserTable));
}
//确认密码修改后更新
void AdminHome::updateUserTable()
{
    QString username = changeInfo.ui->ID_line->text(); //已设置成不可修改
    QString password = changeInfo.ui->PWD_line->text();

    //根据勾选判断在哪个表更新数据
    if(model_flag == StuModel){
        QString sql = "update stuinfo set pwd='"+password+"' where uid='"+username+"'";
        query = new QSqlQuery(); //一定要先new在exec不然会QSqlQuery::exec: called before driver has been set up
        query->exec(sql);
        user_qmodel->setQuery("select uid,pwd from stuinfo");
    }else if(model_flag == TeaModel){
        QString sql = "update teacher set pwd='"+password+"' where uid='"+username+"'";
        query = new QSqlQuery(); //一定要先new在exec不然会QSqlQuery::exec: called before driver has been set up
        query->exec(sql);
        user_qmodel->setQuery("select uid,pwd from teacher");
    }else if(model_flag == AdminModel){
        QString sql = "update admininfo set pwd='"+password+"' where uid='"+username+"'";
        query = new QSqlQuery(); //一定要先new在exec不然会QSqlQuery::exec: called before driver has been set up
        query->exec(sql);
        user_qmodel->setQuery("select uid,pwd from admininfo");
    }

    //QM提醒一下
    QMessageBox::information(&changeInfo,"消息","用户'"+username+"'密码已重置！(未修改则仍为原密码)");
    changeInfo.close();
}

//用户查找按钮
void AdminHome::on_btn_srchUser_clicked()
{
    //用户查找
    srch_u.ui->ID_line->setText("");
    srch_u.show();
    disconnect(srch_u.ui->btn_srch, &QPushButton::clicked, this, &AdminHome::srchUserTable); //每次先断再连不然会多次连接下面的QM会被多次call
    connect(srch_u.ui->btn_srch, &QPushButton::clicked, this, QOverload<>::of(&AdminHome::srchUserTable));
}
//用户查找界面
void AdminHome::srchUserTable()
{
    QString username = srch_u.ui->ID_line->text();

    //根据勾选判断在哪个表查找用户
    if(model_flag == StuModel){
        QString sql = "select uid,pwd from stuinfo where uid='"+username+"'";
        query = new QSqlQuery();
        query->exec(sql);
        //检查查询结果是否非空
        if(query->next()){
            user_qmodel->setQuery("select uid,pwd from stuinfo where uid='"+username+"'");
        }else{
            QMessageBox::information(&srch_u,"消息","不存在此学生账号！");
        }
    }else if(model_flag == TeaModel){
        QString sql = "select uid,pwd from teacher where uid='"+username+"'";
        query = new QSqlQuery();
        query->exec(sql);
        //检查查询结果是否非空
        if(query->next()){
            user_qmodel->setQuery("select uid,pwd from teacher where uid='"+username+"'");
        }else{
            QMessageBox::information(&srch_u,"消息","不存在此教师账号！");
        }
    }else if(model_flag == AdminModel){
        QString sql = "select uid,pwd from admininfo where uid='"+username+"'";
        query = new QSqlQuery();
        query->exec(sql);
        //检查查询结果是否非空
        if(query->next()){
            user_qmodel->setQuery("select uid,pwd from admininfo where uid='"+username+"'");
        }else{
            QMessageBox::information(&srch_u,"消息","不存在此管理员账号！");
        }
    }
}

//表格恢复到查找前
void AdminHome::on_btn_originU_clicked()
{
    //根据勾选判断在哪个表查找用户
    if(model_flag == StuModel){
        user_qmodel->setQuery("select uid,pwd from stuinfo");
    }else if(model_flag == TeaModel){
        user_qmodel->setQuery("select uid,pwd from teacher");
    }else if(model_flag == AdminModel){
        user_qmodel->setQuery("select uid,pwd from admininfo");
    }
}
//返回登录界面
void AdminHome::on_btn_bckLogin_clicked()
{
    //退出登录
}


//课程管理Tab双击修改课程信息
void AdminHome::on_les_tableView_doubleClicked(const QModelIndex &index)
{
    QString les_id = index.siblingAtColumn(0).data().toString();
    QString les_name = index.siblingAtColumn(1).data().toString();
    QString t_name = index.siblingAtColumn(2).data().toString();
    QString chour = index.siblingAtColumn(3).data().toString();
    QString type = index.siblingAtColumn(4).data().toString();
    QString test = index.siblingAtColumn(5).data().toString();
    QString credit = index.siblingAtColumn(6).data().toString();
    //窗口显示，已经改因为复用窗口要再改一遍的信息
    changelesinfo.show();
    changelesinfo.setWindowTitle("Admin - 课程信息修改");
    changelesinfo.ui->ID_line->setReadOnly(true); //修改为可编辑
    QString htmlText = "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">"
                       "p, li { white-space: pre-wrap; }"
                       "hr { height: 1px; border-width: 0; }"
                       "li.unchecked::marker { content: \"\\2610\"; }"
                       "li.checked::marker { content: \"\\2612\"; }"
                       "</style></head><body style=\" font-family:'等线 Light'; font-size:12pt; font-weight:300; font-style:normal;\">"
                       "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
                       "<span style=\" font-family:'Microsoft YaHei UI'; font-size:14pt; font-weight:400; color:#5b5b5b;\">课程信息修改</span></p></body></html>";
    changelesinfo.ui->lesWinTitle->setText(htmlText);
    changelesinfo.ui->lesWinTitle->setTextFormat(Qt::RichText);
    changelesinfo.ui->ID_line->setText(les_id);
    changelesinfo.ui->LNAME_line->setText(les_name);
    //对教师选项卡的处理
    query = new QSqlQuery();
    if (query->exec("SELECT uid, t_name FROM teacher")) {
        // 清空下拉框内容
        changelesinfo.ui->T_comboBox->clear();

        // 将查询结果添加到下拉框中
        while (query->next()) {
            QString id = query->value("uid").toString();
            QString t_name = query->value("t_name").toString();

            // 在 QComboBox 中显示 t_name，但存储对应的 id
            changelesinfo.ui->T_comboBox->addItem(t_name, id);
        }
    } else {
        QMessageBox::information(this,"消息","选项卡数据库查询失败！");
    }
    changelesinfo.ui->T_comboBox->setCurrentText(t_name);
    changelesinfo.ui->CHOUR_lineEdit->setText(chour);
    changelesinfo.ui->CREDIT_lineEdit->setText(credit);
    changelesinfo.ui->TYPE_cb->setCurrentText(type);
    changelesinfo.ui->TEST_cb->setCurrentText(test);
    disconnect(changelesinfo.ui->btn_checkChange, &QDialogButtonBox::accepted, this, &AdminHome::addLesRecord); //断掉另一个要用的不然会混
    disconnect(changelesinfo.ui->btn_checkChange, &QDialogButtonBox::accepted, this, &AdminHome::updateLesTable); //每次先断再连不然会多次连接下面的QM会被多次call
    connect(changelesinfo.ui->btn_checkChange,&QDialogButtonBox::accepted,this,QOverload<>::of(&AdminHome::updateLesTable));
}
//确认更新课程信息
void AdminHome::updateLesTable()
{
    QString les_id = changelesinfo.ui->ID_line->text();
    QString les_name = changelesinfo.ui->LNAME_line->text();
    QString t_id = changelesinfo.ui->T_comboBox->currentData().toString();
    int chour = changelesinfo.ui->CHOUR_lineEdit->text().toInt();
    int credit = changelesinfo.ui->CREDIT_lineEdit->text().toInt();
    QString type = changelesinfo.ui->TYPE_cb->currentText();
    QString test = changelesinfo.ui->TEST_cb->currentText();

    query = new QSqlQuery(); //一定要先new在exec不然会QSqlQuery::exec: called before driver has been set up
    query->prepare("update lesson set lname=:les_name, tid=:t_id, chour=:chour, type=:type, test=:test, credit=:credit where lid=:les_id");
    query->bindValue(":les_id", les_id);
    query->bindValue(":les_name", les_name);
    query->bindValue(":t_id", t_id);
    query->bindValue(":chour", chour);
    query->bindValue(":type", type);
    query->bindValue(":test", test);
    query->bindValue(":credit", credit);

    if (query->exec()) {
        QMessageBox::information(&changelesinfo,"消息","课程'"+les_id+les_name+"'信息修改成功！\n(未修改则不变)");
    } else {
        QMessageBox::information(&changelesinfo,"消息","课程信息修改失败!\nERROR:'"+query->lastError().text()+"'");
    }
    //更新面板
    les_qmodel->setQuery("select lesson.lid,lesson.lname,teacher.t_name,chour,type,test,credit from lesson join teacher on lesson.tid = teacher.uid");

    changelesinfo.close(); //也许不关更方便
}
//添加课程信息
void AdminHome::on_btn_addLes_clicked()
{
    //添加课程记录
    changelesinfo.show();
    changelesinfo.setWindowTitle("Admin - 添加课程");
    changelesinfo.ui->ID_line->setReadOnly(false); //修改为可编辑
    //清空上一回的信息
    changelesinfo.ui->ID_line->setText("");
    changelesinfo.ui->LNAME_line->setText("");
    changelesinfo.ui->CHOUR_lineEdit->setText("");
    changelesinfo.ui->TYPE_cb->setCurrentIndex(0);
    changelesinfo.ui->TEST_cb->setCurrentIndex(0);
    changelesinfo.ui->CREDIT_lineEdit->setText("");

    QString htmlText = "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">"
                       "p, li { white-space: pre-wrap; }"
                       "hr { height: 1px; border-width: 0; }"
                       "li.unchecked::marker { content: \"\\2610\"; }"
                       "li.checked::marker { content: \"\\2612\"; }"
                       "</style></head><body style=\" font-family:'等线 Light'; font-size:12pt; font-weight:300; font-style:normal;\">"
                       "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
                       "<span style=\" font-family:'Microsoft YaHei UI'; font-size:14pt; font-weight:400; color:#5b5b5b;\">添加课程信息</span></p></body></html>";
    changelesinfo.ui->lesWinTitle->setText(htmlText);
    changelesinfo.ui->lesWinTitle->setTextFormat(Qt::RichText);
    //对教师选项卡的处理
    query = new QSqlQuery();
    if (query->exec("SELECT uid, t_name FROM teacher")) {
        // 清空下拉框内容
        changelesinfo.ui->T_comboBox->clear();

        // 将查询结果添加到下拉框中
        while (query->next()) {
            QString id = query->value("uid").toString();
            QString t_name = query->value("t_name").toString();

            // 在 QComboBox 中显示 t_name，但存储对应的 id
            changelesinfo.ui->T_comboBox->addItem(t_name, id);
        }
    } else {
        QMessageBox::information(this,"消息","选项卡数据库查询失败！");
    }
    //复用changeinfo窗口，方便
    disconnect(changelesinfo.ui->btn_checkChange, &QDialogButtonBox::accepted, this, &AdminHome::updateLesTable); //断掉另一个要用的不然会混
    disconnect(changelesinfo.ui->btn_checkChange, &QDialogButtonBox::accepted, this, &AdminHome::addLesRecord); //每次先断再连不然会多次连接下面的QM会被多次call
    connect(changelesinfo.ui->btn_checkChange,&QDialogButtonBox::accepted,this,QOverload<>::of(&AdminHome::addLesRecord));
}
void AdminHome::addLesRecord() //真正记录添加的实现
{
    //判断课程号是否为空，课程名是否为空
    QString les_id = changelesinfo.ui->ID_line->text();
    QString les_name = changelesinfo.ui->LNAME_line->text();
    QString t_id = changelesinfo.ui->T_comboBox->currentData().toString();
    int chour = changelesinfo.ui->CHOUR_lineEdit->text().toInt();
    int credit = changelesinfo.ui->CREDIT_lineEdit->text().toInt();
    QString type = changelesinfo.ui->TYPE_cb->currentText();
    QString test = changelesinfo.ui->TEST_cb->currentText();

    if (les_id.isEmpty() || les_name.isEmpty()) {
        QMessageBox::information(&changelesinfo,"消息","课程号和课程名称不可为空！");
    } else {
        //添加新记录
        query = new QSqlQuery();
        QString insertQuery = "INSERT INTO lesson (lid, lname, tid, chour, type, test, credit) VALUES (:les_id, :les_name, :t_id, :chour, :type, :test, :credit)";
        query->prepare(insertQuery);
        query->bindValue(":les_id", les_id);
        query->bindValue(":les_name", les_name);
        query->bindValue(":t_id", t_id);
        query->bindValue(":chour", chour);
        query->bindValue(":type", type);
        query->bindValue(":test", test);
        query->bindValue(":credit", credit);

        if (query->exec()) {
            // 插入成功
            QMessageBox::information(&changelesinfo,"消息","课程'"+les_id+les_name+"'信息添加成功!");
            //更新面板
            les_qmodel->setQuery("select lesson.lid,lesson.lname,teacher.t_name,chour,type,test,credit from lesson join teacher on lesson.tid = teacher.uid");

            changelesinfo.close(); //也许不关更方便
        } else {
            // 插入失败
            QMessageBox::information(&changelesinfo,"消息","添加课程信息失败!\nERROR:'"+query->lastError().text()+"'");
        }

    }
}
//删除课程记录
void AdminHome::on_btn_delLes_clicked()
{
    //删除选择记录
    currentIndexModel = ui->les_tableView->currentIndex();

    //未选择，返回
    if(currentIndexModel.siblingAtColumn(0).data().toString().isEmpty())
        return;

    QString lid = currentIndexModel.siblingAtColumn(0).data().toString();
    QString lname = currentIndexModel.siblingAtColumn(1).data().toString();
    QString sql = "delete from lesson where lid='"+lid+"'";
    //删除确认
    query = new QSqlQuery();
    if (query->exec(sql)) {
        //删除成功
        QMessageBox::information(&changelesinfo,"消息","课程'"+lid+lname+"'信息已被删除");
        //更新面板
        les_qmodel->setQuery("select lesson.lid,lesson.lname,teacher.t_name,chour,type,test,credit from lesson join teacher on lesson.tid = teacher.uid");
    } else {
        //删除失败
        QMessageBox::information(&changelesinfo,"消息","课程记录删除失败!\nERROR:'"+query->lastError().text()+"'");
    }
}
//课程查找
void AdminHome::on_btn_srchLes_clicked()
{
    //课程查找
    srch_l.ui->ID_line->setText("");
    srch_l.ui->LNAME_line->setText("");
    srch_l.ui->CHOUR_lineEdit->setText("");
    srch_l.ui->CREDIT_lineEdit->setText("");
    srch_l.ui->TYPE_cb->setCurrentIndex(0);
    srch_l.ui->TEST_cb->setCurrentIndex(0);
    //对教师选项卡的处理
    query = new QSqlQuery();
    if (query->exec("SELECT uid, t_name FROM teacher")) {
        // 清空下拉框内容
        srch_l.ui->T_comboBox->clear();
        srch_l.ui->T_comboBox->addItem(""); //加空项

        // 将查询结果添加到下拉框中
        while (query->next()) {
            QString id = query->value("uid").toString();
            QString t_name = query->value("t_name").toString();

            // 在 QComboBox 中显示 t_name，但存储对应的 id
            srch_l.ui->T_comboBox->addItem(t_name, id);
        }
    } else {
        QMessageBox::information(this,"消息","选项卡数据库查询失败！");
    }
    srch_l.show();
    disconnect(srch_l.ui->btn_srch, &QPushButton::clicked, this, &AdminHome::srchLesTable);
    connect(srch_l.ui->btn_srch, &QPushButton::clicked, this, QOverload<>::of(&AdminHome::srchLesTable));
}
void AdminHome::srchLesTable()
{
    QString les_id = srch_l.ui->ID_line->text();
    QString les_name = srch_l.ui->LNAME_line->text();
    QString t_id = srch_l.ui->T_comboBox->currentData().toString();
    int chour = srch_l.ui->CHOUR_lineEdit->text().toInt();
    int credit = srch_l.ui->CREDIT_lineEdit->text().toInt();
    QString type = srch_l.ui->TYPE_cb->currentText();
    QString test = srch_l.ui->TEST_cb->currentText();
    //实现多关键词随意查询
    QString sql = "select lid,lname,teacher.t_name,chour,type,test,credit from lesson join teacher on lesson.tid = teacher.uid WHERE 1=1";
    if (!les_id.isEmpty()) {
        sql += " AND lid LIKE '%" + les_id + "%'";
    }
    if (!les_name.isEmpty()) {
        sql += " AND lname LIKE '%" + les_name + "%'";
    }
    if (!t_id.isEmpty()) {
        sql += " AND tid = '" + t_id + "'";
    }
    if (chour != 0) {
        sql += " AND chour = " + QString::number(chour);
    }
    if (!type.isEmpty()) {
        sql += " AND type = '" + type + "'";
    }
    if (!test.isEmpty()) {
        sql += " AND test = '" + test + "'";
    }
    if (credit != 0) {
        sql += " AND credit = " + QString::number(credit);
    }
    //执行并检查查询结果是否非空
    query = new QSqlQuery();
    query->exec(sql);
    if (query->next()) {
        les_qmodel->setQuery(sql);
    } else {
        QMessageBox::information(&srch_l, "消息", "不存在符合条件的课程！");
    }
}
//返回查找前LESSON表格
void AdminHome::on_btn_originL_clicked()
{
    les_qmodel->setQuery("select lesson.lid,lesson.lname,teacher.t_name,chour,type,test,credit from lesson join teacher on lesson.tid = teacher.uid");
}

//双击修改教师信息
void AdminHome::on_tea_tableView_doubleClicked(const QModelIndex &index)
{
    QString t_id = index.siblingAtColumn(0).data().toString();
    QString teaName = index.siblingAtColumn(1).data().toString();
    QString t_sex = index.siblingAtColumn(2).data().toString();
    QString t_title = index.siblingAtColumn(3).data().toString();
    QString t_tel = index.siblingAtColumn(4).data().toString();
    QString t_oren = index.siblingAtColumn(5).data().toString();

    //窗口显示，已经改因为复用窗口要再改一遍的信息
    changeteainfo.show();
    changeteainfo.ui->ID_line->setReadOnly(true); //改回为不可编辑
    changeteainfo.setWindowTitle("Admin - 修改教师信息");

    QString htmlText = "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">"
                       "p, li { white-space: pre-wrap; }"
                       "hr { height: 1px; border-width: 0; }"
                       "li.unchecked::marker { content: \"\\2610\"; }"
                       "li.checked::marker { content: \"\\2612\"; }"
                       "</style></head><body style=\" font-family:'等线 Light'; font-size:12pt; font-weight:300; font-style:normal;\">"
                       "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
                       "<span style=\" font-family:'Microsoft YaHei UI'; font-size:14pt; font-weight:400; color:#5b5b5b;\">修改教师信息</span></p></body></html>";
    changeteainfo.ui->teaWinTitle->setText(htmlText);
    changeteainfo.ui->teaWinTitle->setTextFormat(Qt::RichText);

    changeteainfo.ui->ID_line->setText(t_id);
    changeteainfo.ui->TNAME_line->setText(teaName);
    changeteainfo.ui->SEX_cb->setCurrentText(t_sex);
    changeteainfo.ui->TITLE_cb->setCurrentText(t_title);
    changeteainfo.ui->TEL_le->setText(t_tel);
    changeteainfo.ui->ORIEN_le->setText(t_oren);

    disconnect(changeteainfo.ui->btn_checkChange, &QDialogButtonBox::accepted, this, &AdminHome::addTeaRecord);
    disconnect(changeteainfo.ui->btn_checkChange, &QDialogButtonBox::accepted, this, &AdminHome::updateTeaTable); //每次先断再连不然会多次连接下面的QM会被多次call
    connect(changeteainfo.ui->btn_checkChange,&QDialogButtonBox::accepted,this,QOverload<>::of(&AdminHome::updateTeaTable));
}
//真正实现更新的函数
void AdminHome::updateTeaTable()
{
    QString t_id = changeteainfo.ui->ID_line->text();
    QString teaName = changeteainfo.ui->TNAME_line->text();
    QString t_sex = changeteainfo.ui->SEX_cb->currentText();
    QString t_title = changeteainfo.ui->TITLE_cb->currentText();
    QString t_tel = changeteainfo.ui->TEL_le->text();
    QString t_oren = changeteainfo.ui->ORIEN_le->text();

    query = new QSqlQuery(); //一定要先new在exec不然会QSqlQuery::exec: called before driver has been set up
    query->prepare("update teacher set t_name=:t_name, sex=:t_sex, title=:t_title, tel=:tel, orientation=:orien where uid=:t_id");
    query->bindValue(":t_id", t_id);
    query->bindValue(":t_name", teaName);
    query->bindValue(":t_sex", t_sex);
    query->bindValue(":t_title", t_title);
    query->bindValue(":tel", t_tel);
    query->bindValue(":orien", t_oren);

    if (query->exec()) {
        QMessageBox::information(&changeteainfo,"消息","教师'"+t_id+" "+teaName+"'信息修改成功！\n(未修改则不变)");
    } else {
        QMessageBox::information(&changeteainfo,"消息","教师信息修改失败!\nERROR:'"+query->lastError().text()+"'");
    }
    //更新面板
    tea_qmodel->setQuery("select uid,t_name,sex,title,tel,orientation from teacher");

    changeteainfo.close(); //也许不关更方便
}

//添加教师信息
void AdminHome::on_btn_addTea_clicked()
{
    //添加教师记录
    changeteainfo.show();
    changeteainfo.setWindowTitle("Admin - 添加教师");
    changeteainfo.ui->ID_line->setReadOnly(false); //修改为可编辑

    //清空上一回的信息
    changeteainfo.ui->ID_line->setText("");
    changeteainfo.ui->TNAME_line->setText("");
    changeteainfo.ui->SEX_cb->setCurrentIndex(0);
    changeteainfo.ui->TITLE_cb->setCurrentIndex(0);
    changeteainfo.ui->TEL_le->setText("");
    changeteainfo.ui->ORIEN_le->setText("");

    QString htmlText = "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">"
                       "p, li { white-space: pre-wrap; }"
                       "hr { height: 1px; border-width: 0; }"
                       "li.unchecked::marker { content: \"\\2610\"; }"
                       "li.checked::marker { content: \"\\2612\"; }"
                       "</style></head><body style=\" font-family:'等线 Light'; font-size:12pt; font-weight:300; font-style:normal;\">"
                       "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
                       "<span style=\" font-family:'Microsoft YaHei UI'; font-size:14pt; font-weight:400; color:#5b5b5b;\">添加教师</span></p></body></html>";
    changeteainfo.ui->teaWinTitle->setText(htmlText);
    changeteainfo.ui->teaWinTitle->setTextFormat(Qt::RichText);

    //复用changeinfo窗口，方便
    disconnect(changeteainfo.ui->btn_checkChange, &QDialogButtonBox::accepted, this, &AdminHome::updateTeaTable); //断掉另一个要用的不然会混
    disconnect(changeteainfo.ui->btn_checkChange, &QDialogButtonBox::accepted, this, &AdminHome::addTeaRecord); //每次先断再连不然会多次连接下面的QM会被多次call
    connect(changeteainfo.ui->btn_checkChange,&QDialogButtonBox::accepted,this,QOverload<>::of(&AdminHome::addTeaRecord));
}
void AdminHome::addTeaRecord() //真正记录添加的实现
{
    //判断教师id，姓名是否为空
    QString t_id = changeteainfo.ui->ID_line->text();
    QString teaName = changeteainfo.ui->TNAME_line->text();
    QString t_sex = changeteainfo.ui->SEX_cb->currentText();
    QString t_title = changeteainfo.ui->TITLE_cb->currentText();
    QString t_tel = changeteainfo.ui->TEL_le->text();
    QString t_oren = changeteainfo.ui->ORIEN_le->text();
    if (t_id.isEmpty() || teaName.isEmpty()) {
        QMessageBox::information(&changeteainfo,"消息","NetID和教师姓名不可为空！");
    } else {
        //添加新记录
        query = new QSqlQuery();
        QString insertQuery = "INSERT INTO teacher (uid, t_name, sex, title, tel, orientation) VALUES (:t_id, :t_name, :t_sex, :title, :tel, :orien)";
        query->prepare(insertQuery);
        query->bindValue(":t_id", t_id);
        query->bindValue(":t_name", teaName);
        query->bindValue(":t_sex", t_sex);
        query->bindValue(":title", t_title);
        query->bindValue(":tel", t_tel);
        query->bindValue(":orien", t_oren);
        if (query->exec()) {
            //插入成功
            QMessageBox::information(&changeteainfo,"消息","教师'"+t_id+" "+teaName+"'添加成功!\n初始默认密码：123456");
            //更新面板
            tea_qmodel->setQuery("select uid,t_name,sex,title,tel,orientation from teacher");

            changeteainfo.close(); //也许不关更方便
        } else {
            //插入失败
            QMessageBox::information(&changeteainfo,"消息","添加教师失败!\nERROR:'"+query->lastError().text()+"'");
        }

    }
}

//删除教师信息
void AdminHome::on_btn_delTea_clicked()
{
    //删除选择记录
    currentIndexModel = ui->tea_tableView->currentIndex();

    //未选择，返回
    if(currentIndexModel.siblingAtColumn(0).data().toString().isEmpty())
        return;

    QString tid = currentIndexModel.siblingAtColumn(0).data().toString();
    QString tname = currentIndexModel.siblingAtColumn(1).data().toString();
    QString sql = "delete from teacher where uid='"+tid+"'";
    //删除确认
    query = new QSqlQuery();
    if (query->exec(sql)) {
        //删除成功
        QMessageBox::information(&changeteainfo,"消息","教师'"+tid+" "+tname+"'信息已被删除");
        //更新面板
        tea_qmodel->setQuery("select uid,t_name,sex,title,tel,orientation from teacher");
    } else {
        //删除失败
        QMessageBox::information(&changeteainfo,"消息","教师记录删除失败!\nERROR:'"+query->lastError().text()+"'");
    }
}

//教师查找
void AdminHome::on_btn_srchTea_clicked()
{
    //清空上次查找时的输入
    srch_t.ui->ID_line->setText("");
    srch_t.ui->TNAME_line->setText("");
    srch_t.ui->SEX_cb->setCurrentIndex(0);
    srch_t.ui->TITLE_cb->setCurrentIndex(0);
    srch_t.ui->TEL_le->setText("");
    srch_t.ui->ORIEN_le->setText("");

    //显示查找窗口
    srch_t.show();

    //连接查找窗口的查找按钮信号方便在这里实现
    disconnect(srch_t.ui->btn_srch, &QPushButton::clicked, this, &AdminHome::srchTeaTable);
    connect(srch_t.ui->btn_srch, &QPushButton::clicked, this, QOverload<>::of(&AdminHome::srchTeaTable));
}
void AdminHome::srchTeaTable()
{
    QString t_id = srch_t.ui->ID_line->text();
    QString teaName = srch_t.ui->TNAME_line->text();
    QString t_sex = srch_t.ui->SEX_cb->currentText();
    QString t_title = srch_t.ui->TITLE_cb->currentText();
    QString t_tel = srch_t.ui->TEL_le->text();
    QString t_oren = srch_t.ui->ORIEN_le->text();

    //实现多关键词随意查询
    QString sql = "select uid,t_name,sex,title,tel,orientation from teacher WHERE 1=1";
    if (!t_id.isEmpty()) {
        sql += " AND uid LIKE '%" + t_id + "%'";
    }
    if (!teaName.isEmpty()) {
        sql += " AND t_name LIKE '%" + teaName + "%'";
    }
    if (!t_sex.isEmpty()) {
        sql += " AND sex = '" + t_sex + "'";
    }
    if (!t_title.isEmpty()) {
        sql += " AND title = '" + t_title + "'";
    }
    if (!t_tel.isEmpty()) {
        sql += " AND tel LIKE '%" + t_tel + "%'";
    }
    if (!t_oren.isEmpty()) {
        sql += " AND orientation LIKE '%" + t_oren + "%'";
    }

    //执行并检查查询结果是否非空
    query = new QSqlQuery();
    query->exec(sql);
    if (query->next()) {
        tea_qmodel->setQuery(sql);
    } else {
        QMessageBox::information(&srch_t, "消息", "不存在符合条件的教师！");
    }
}

//回原始教师表格
void AdminHome::on_btn_originT_clicked()
{
    tea_qmodel->setQuery("select uid,t_name,sex,title,tel,orientation from teacher");
}

//双击修改学生信息
void AdminHome::on_stu_tableView_doubleClicked(const QModelIndex &index)
{
    QString s_id = index.siblingAtColumn(0).data().toString();
    QString sName = index.siblingAtColumn(1).data().toString();
    QString s_sex = index.siblingAtColumn(2).data().toString();
    QString s_age = index.siblingAtColumn(3).data().toString();
    QString s_college = index.siblingAtColumn(4).data().toString();
    QString s_year = index.siblingAtColumn(5).data().toString();
    QString s_home = index.siblingAtColumn(6).data().toString();
    QString s_tel = index.siblingAtColumn(7).data().toString();

    //窗口显示，已经改因为复用窗口要再改一遍的信息
    changestuinfo.show();
    changestuinfo.ui->ID_line->setText(s_id);
    changestuinfo.ui->NAME_line->setText(sName);
    changestuinfo.ui->SEX_cb->setCurrentText(s_sex);
    changestuinfo.ui->AGE_le->setText(s_age);
    changestuinfo.ui->COL_le->setText(s_college);
    changestuinfo.ui->YEAR_cb->setCurrentText(s_year);
    changestuinfo.ui->AD_le->setText(s_home);
    changestuinfo.ui->TEL_le->setText(s_tel);

    disconnect(changestuinfo.ui->btn_checkChange, &QDialogButtonBox::accepted, this, &AdminHome::addStuRecord);  //断掉另一个窗口用时连接的的信号
    disconnect(changestuinfo.ui->btn_checkChange, &QDialogButtonBox::accepted, this, &AdminHome::updateStuTable); //每次先断再连不然会多次连接下面的QM会被多次call
    connect(changestuinfo.ui->btn_checkChange,&QDialogButtonBox::accepted,this,QOverload<>::of(&AdminHome::updateStuTable));
}
void AdminHome::updateStuTable()
{
    QString s_id = changestuinfo.ui->ID_line->text();
    QString s_name = changestuinfo.ui->NAME_line->text();
    QString s_sex = changestuinfo.ui->SEX_cb->currentText();
    QString s_age = changestuinfo.ui->AGE_le->text();
    QString s_col = changestuinfo.ui->COL_le->text();
    QString s_year = changestuinfo.ui->YEAR_cb->currentText();
    QString s_ad = changestuinfo.ui->AD_le->text();
    QString s_tel = changestuinfo.ui->TEL_le->text();

    query = new QSqlQuery(); //一定要先new在exec不然会QSqlQuery::exec: called before driver has been set up
    query->prepare("update stuinfo set name=:s_name, sex=:s_sex, age=:s_age, tel=:tel, major=:s_col, year=:year, home=:ad, tel=:tel where uid=:s_id");
    query->bindValue(":s_id", s_id);
    query->bindValue(":s_name", s_name);
    query->bindValue(":s_sex", s_sex);
    query->bindValue(":s_age", s_age);
    query->bindValue(":s_col", s_col);
    query->bindValue(":year", s_year);
    query->bindValue(":ad", s_ad);
    query->bindValue(":tel", s_tel);

    if (query->exec()) {
        QMessageBox::information(&changestuinfo,"消息","学生'"+s_id+" "+s_name+"'信息修改成功！\n(未修改则不变)");
    } else {
        QMessageBox::information(&changestuinfo,"消息","学生信息修改失败!\nERROR:'"+query->lastError().text()+"'");
    }
    //更新面板
    stu_qmodel->setQuery("select uid,name,sex,age,major,year,home,tel from stuinfo");

    changestuinfo.close(); //也许不关更方便
}

//添加学生信息
void AdminHome::on_btn_addStu_clicked()
{
    //添加教师记录
    changestuinfo.show();
    changestuinfo.setWindowTitle("Admin - 添加学生");
    changestuinfo.ui->ID_line->setReadOnly(false); //修改为可编辑

    //清空上一回的信息
    changestuinfo.ui->ID_line->setText("");
    changestuinfo.ui->NAME_line->setText("");
    changestuinfo.ui->SEX_cb->setCurrentIndex(0);
    changestuinfo.ui->AGE_le->setText("");
    changestuinfo.ui->COL_le->setText("");
    changestuinfo.ui->YEAR_cb->setCurrentIndex(0);
    changestuinfo.ui->AD_le->setText("");
    changestuinfo.ui->TEL_le->setText("");



    QString htmlText = "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">"
                       "p, li { white-space: pre-wrap; }"
                       "hr { height: 1px; border-width: 0; }"
                       "li.unchecked::marker { content: \"\\2610\"; }"
                       "li.checked::marker { content: \"\\2612\"; }"
                       "</style></head><body style=\" font-family:'等线 Light'; font-size:12pt; font-weight:300; font-style:normal;\">"
                       "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
                       "<span style=\" font-family:'Microsoft YaHei UI'; font-size:14pt; font-weight:400; color:#5b5b5b;\">添加学生</span></p></body></html>";
    changestuinfo.ui->stuWinTitle->setText(htmlText);
    changestuinfo.ui->stuWinTitle->setTextFormat(Qt::RichText);

    //复用窗口，方便
    disconnect(changestuinfo.ui->btn_checkChange, &QDialogButtonBox::accepted, this, &AdminHome::updateStuTable); //断掉另一个要用的不然会混
    disconnect(changestuinfo.ui->btn_checkChange, &QDialogButtonBox::accepted, this, &AdminHome::addStuRecord); //每次先断再连不然会多次连接下面的QM会被多次call
    connect(changestuinfo.ui->btn_checkChange,&QDialogButtonBox::accepted,this,QOverload<>::of(&AdminHome::addStuRecord));
}
void AdminHome::addStuRecord()
{
    //判断学生id，姓名是否为空
    QString s_id = changestuinfo.ui->ID_line->text();
    QString s_name = changestuinfo.ui->NAME_line->text();
    QString s_sex = changestuinfo.ui->SEX_cb->currentText();
    QString s_age = changestuinfo.ui->AGE_le->text();
    QString s_col = changestuinfo.ui->COL_le->text();
    QString s_year = changestuinfo.ui->YEAR_cb->currentText();
    QString s_ad = changestuinfo.ui->AD_le->text();
    QString s_tel = changestuinfo.ui->TEL_le->text();

    if (s_id.isEmpty() || s_name.isEmpty()) {
        QMessageBox::information(&changeteainfo,"消息","NetID和学生姓名不可为空！");
    } else {
        //添加新记录
        query = new QSqlQuery();
        QString insertQuery = "INSERT INTO stuinfo (uid, name, sex, age, major, year, home, tel) VALUES (:s_id, :s_name, :s_sex, :s_age, :s_col, :year, :ad, :tel)";
        query->prepare(insertQuery);
        query->bindValue(":s_id", s_id);
        query->bindValue(":s_name", s_name);
        query->bindValue(":s_sex", s_sex);
        query->bindValue(":s_age", s_age);
        query->bindValue(":s_col", s_col);
        query->bindValue(":year", s_year);
        query->bindValue(":ad", s_ad);
        query->bindValue(":tel", s_tel);

        if (query->exec()) {
            //插入成功
            QMessageBox::information(&changestuinfo,"消息","学生'"+s_id+" "+s_name+"'添加成功!\n初始默认密码：123456");
            //更新面板
            stu_qmodel->setQuery("select uid,name,sex,age,major,year,home,tel from stuinfo");

            changestuinfo.close(); //也许不关更方便
        } else {
            //插入失败
            QMessageBox::information(&changestuinfo,"消息","添加学生失败!\nERROR:'"+query->lastError().text()+"'");
        }

    }
}

//删除学生信息
void AdminHome::on_btn_delStu_clicked()
{
    //删除选择记录
    currentIndexModel = ui->stu_tableView->currentIndex();

    //未选择，返回
    if(currentIndexModel.siblingAtColumn(0).data().toString().isEmpty())
        return;

    QString sid = currentIndexModel.siblingAtColumn(0).data().toString();
    QString sname = currentIndexModel.siblingAtColumn(1).data().toString();
    QString sql = "delete from stuinfo where uid='"+sid+"'";
    //删除确认
    query = new QSqlQuery();
    if (query->exec(sql)) {
        //删除成功
        QMessageBox::information(&changestuinfo,"消息","学生'"+sid+" "+sname+"'信息已被删除");
        //更新面板
        stu_qmodel->setQuery("select uid,name,sex,age,major,year,home,tel from stuinfo");
    } else {
        //删除失败
        QMessageBox::information(&changestuinfo,"消息","学生记录删除失败!\nERROR:'"+query->lastError().text()+"'");
    }
}

//查找学生
void AdminHome::on_btn_srchStu_clicked()
{
    //清空上次查找时的输入
    srch_s.ui->ID_line->setText("");
    srch_s.ui->NAME_line->setText("");
    srch_s.ui->SEX_cb->setCurrentIndex(0);
    srch_s.ui->AGE_le->setText("");
    srch_s.ui->COL_le->setText("");
    srch_s.ui->YEAR_cb->setCurrentIndex(0);
    srch_s.ui->AD_le->setText("");
    srch_s.ui->TEL_le->setText("");

    //显示查找窗口
    srch_s.show();

    //连接查找窗口的查找按钮信号方便在这里实现
    disconnect(srch_s.ui->btn_srch, &QPushButton::clicked, this, &AdminHome::srchStuTable);
    connect(srch_s.ui->btn_srch, &QPushButton::clicked, this, QOverload<>::of(&AdminHome::srchStuTable));
}
void AdminHome::srchStuTable()
{
    QString s_id = srch_s.ui->ID_line->text();
    QString s_name = srch_s.ui->NAME_line->text();
    QString s_sex = srch_s.ui->SEX_cb->currentText();
    QString s_age = srch_s.ui->AGE_le->text();
    QString s_col = srch_s.ui->COL_le->text();
    QString s_year = srch_s.ui->YEAR_cb->currentText();
    QString s_ad = srch_s.ui->AD_le->text();
    QString s_tel = srch_s.ui->TEL_le->text();

    //实现多关键词随意查询
    QString sql = "select uid, name, sex, age, major, year, home, tel from stuinfo WHERE 1=1";
    if (!s_id.isEmpty()) {
        sql += " AND uid LIKE '%" + s_id + "%'";
    }
    if (!s_name.isEmpty()) {
        sql += " AND name LIKE '%" + s_name + "%'";
    }
    if (!s_sex.isEmpty()) {
        sql += " AND sex = '" + s_sex + "'";
    }
    if (!s_age.isEmpty()) {
        sql += " AND age LIKE '%" + s_age + "%'";
    }
    if (!s_col.isEmpty()) {
        sql += " AND major LIKE '%" + s_col + "%'";
    }
    if (!s_year.isEmpty()) {
        sql += " AND year = '" + s_year + "'";
    }
    if (!s_ad.isEmpty()) {
        sql += " AND home LIKE '%" + s_ad + "%'";
    }
    if (!s_tel.isEmpty()) {
        sql += " AND tel LIKE '%" + s_tel + "%'";
    }

    //执行并检查查询结果是否非空
    query = new QSqlQuery();
    query->exec(sql);
    if (query->next()) {
        stu_qmodel->setQuery(sql);
    } else {
        QMessageBox::information(&srch_s, "消息", "不存在符合条件的学生！");
    }
}

//回原始学生表格
void AdminHome::on_btn_originS_clicked()
{
    stu_qmodel->setQuery("select uid,name,sex,age,major,year,home,tel from stuinfo");
}

//换界面刷新表格
void AdminHome::on_tabWidget_currentChanged(int index)
{
    //学生管理表格
    stu_qmodel = new QSqlQueryModel(); //用这个数据模型渲染下面的表格
    stu_qmodel->setQuery("select uid,name,sex,age,major,year,home,tel from stuinfo");
    ui->stu_tableView->setModel(stu_qmodel);
    stu_qmodel->setHeaderData(0,Qt::Horizontal,"Netid");
    stu_qmodel->setHeaderData(1,Qt::Horizontal,"姓名");
    stu_qmodel->setHeaderData(2,Qt::Horizontal,"性别");
    stu_qmodel->setHeaderData(3,Qt::Horizontal,"年龄");
    stu_qmodel->setHeaderData(4,Qt::Horizontal,"隶属院系");
    stu_qmodel->setHeaderData(5,Qt::Horizontal,"入学年份");
    stu_qmodel->setHeaderData(6,Qt::Horizontal,"家庭地址");
    stu_qmodel->setHeaderData(7,Qt::Horizontal,"Tel");

    //教师管理表格
    tea_qmodel = new QSqlQueryModel(); //用这个数据模型渲染下面的表格
    tea_qmodel->setQuery("select uid,t_name,sex,title,tel,orientation from teacher");
    ui->tea_tableView->setModel(tea_qmodel);
    tea_qmodel->setHeaderData(0,Qt::Horizontal,"Netid");
    tea_qmodel->setHeaderData(1,Qt::Horizontal,"教师姓名");
    tea_qmodel->setHeaderData(2,Qt::Horizontal,"性别");
    tea_qmodel->setHeaderData(3,Qt::Horizontal,"职称");
    tea_qmodel->setHeaderData(4,Qt::Horizontal,"电话号码");
    tea_qmodel->setHeaderData(5,Qt::Horizontal,"研究方向");

    //课程管理表格
    les_qmodel = new QSqlQueryModel(); //用这个数据模型渲染下面的表格
    les_qmodel->setQuery("select lesson.lid,lesson.lname,teacher.t_name,chour,type,test,credit from lesson join teacher on lesson.tid = teacher.uid");
    ui->les_tableView->setModel(les_qmodel);
    les_qmodel->setHeaderData(0,Qt::Horizontal,"课程号");
    les_qmodel->setHeaderData(1,Qt::Horizontal,"课程名");
    les_qmodel->setHeaderData(2,Qt::Horizontal,"授课教师");
    les_qmodel->setHeaderData(3,Qt::Horizontal,"课时");
    les_qmodel->setHeaderData(4,Qt::Horizontal,"课程类别");
    les_qmodel->setHeaderData(5,Qt::Horizontal,"考核方式");
    les_qmodel->setHeaderData(6,Qt::Horizontal,"学分");

    //用户信息表格,默认先显示学生
    user_qmodel = new QSqlQueryModel();
    user_qmodel->setQuery("select uid,pwd from stuinfo");
    ui->user_tableView->setModel(user_qmodel);
    user_qmodel->setHeaderData(0,Qt::Horizontal,"Netid");
    user_qmodel->setHeaderData(1,Qt::Horizontal,"密码");
}

