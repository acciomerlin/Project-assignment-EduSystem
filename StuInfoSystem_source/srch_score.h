#ifndef SRCH_SCORE_H
#define SRCH_SCORE_H

#include <QWidget>

namespace Ui {
class Srch_score;
}

class Srch_score : public QWidget
{
    Q_OBJECT

public:
    explicit Srch_score(QWidget *parent = nullptr);
    ~Srch_score();
    Ui::Srch_score *ui;
private slots:
    void on_btn_srch_clicked();
    void on_btn_leave_clicked();
};

#endif // SRCH_SCORE_H
