#ifndef CHANGELESINFO_H
#define CHANGELESINFO_H

#include <QWidget>

namespace Ui {
class ChangeLesInfo;
}

class ChangeLesInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeLesInfo(QWidget *parent = nullptr);
    ~ChangeLesInfo();
    Ui::ChangeLesInfo *ui;
private slots:
    void on_btn_checkChange_rejected();
    void on_btn_checkChange_accepted();
};

#endif // CHANGELESINFO_H
