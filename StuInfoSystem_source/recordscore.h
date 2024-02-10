#ifndef RECORDSCORE_H
#define RECORDSCORE_H

#include <QWidget>

namespace Ui {
class RecordScore;
}

class RecordScore : public QWidget
{
    Q_OBJECT

public:
    explicit RecordScore(QWidget *parent = nullptr);
    ~RecordScore();
    Ui::RecordScore *ui;
private slots:
    void on_btn_checkChange_accepted();
    void on_btn_checkChange_rejected();
};

#endif // RECORDSCORE_H
