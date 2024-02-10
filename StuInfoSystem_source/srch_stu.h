#ifndef SRCH_STU_H
#define SRCH_STU_H

#include <QWidget>

namespace Ui {
class Srch_stu;
}

class Srch_stu : public QWidget
{
    Q_OBJECT

public:
    explicit Srch_stu(QWidget *parent = nullptr);
    ~Srch_stu();
    Ui::Srch_stu *ui;
private slots:
    void on_btn_srch_clicked();
    void on_btn_leave_clicked();
};

#endif // SRCH_STU_H
