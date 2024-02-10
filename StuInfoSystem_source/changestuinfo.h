#ifndef CHANGESTUINFO_H
#define CHANGESTUINFO_H

#include <QWidget>

namespace Ui {
class ChangeStuInfo;
}

class ChangeStuInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeStuInfo(QWidget *parent = nullptr);
    ~ChangeStuInfo();
    Ui::ChangeStuInfo *ui;
private slots:
    void on_btn_checkChange_accepted();
    void on_btn_checkChange_rejected();
};

#endif // CHANGESTUINFO_H
