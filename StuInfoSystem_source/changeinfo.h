#ifndef CHANGEINFO_H
#define CHANGEINFO_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class ChangeInfo;
}

class ChangeInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeInfo(QWidget *parent = nullptr);
    ~ChangeInfo();

    Ui::ChangeInfo *ui;
private slots:
    void on_btn_checkChange_accepted();
    void on_btn_checkChange_rejected();
};

#endif // CHANGEINFO_H
