#ifndef SRCH_TEA_H
#define SRCH_TEA_H

#include <QWidget>

namespace Ui {
class Srch_Tea;
}

class Srch_Tea : public QWidget
{
    Q_OBJECT

public:
    explicit Srch_Tea(QWidget *parent = nullptr);
    ~Srch_Tea();
    Ui::Srch_Tea *ui;
private slots:
    void on_btn_srch_clicked();
    void on_btn_leave_clicked();
};

#endif // SRCH_TEA_H
