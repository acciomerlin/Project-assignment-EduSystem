#ifndef SRCH_LES_H
#define SRCH_LES_H

#include <QWidget>

namespace Ui {
class Srch_Les;
}

class Srch_Les : public QWidget
{
    Q_OBJECT

public:
    explicit Srch_Les(QWidget *parent = nullptr);
    ~Srch_Les();
    Ui::Srch_Les *ui;
private slots:
    void on_btn_srch_clicked();
    void on_btn_leave_clicked();
};

#endif // SRCH_LES_H
