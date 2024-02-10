#ifndef SRCH_USER_H
#define SRCH_USER_H

#include <QWidget>

namespace Ui {
class srch_user;
}

class srch_user : public QWidget
{
    Q_OBJECT

public:
    explicit srch_user(QWidget *parent = nullptr);
    ~srch_user();
    Ui::srch_user *ui;
private slots:
    void on_btn_srch_clicked();
};

#endif // SRCH_USER_H
