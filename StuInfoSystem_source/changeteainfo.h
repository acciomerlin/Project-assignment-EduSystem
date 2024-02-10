#ifndef CHANGETEAINFO_H
#define CHANGETEAINFO_H

#include <QWidget>

namespace Ui {
class ChangeTeaInfo;
}

class ChangeTeaInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeTeaInfo(QWidget *parent = nullptr);
    ~ChangeTeaInfo();
    Ui::ChangeTeaInfo *ui;

private slots:
    void on_btn_checkChange_accepted();

    void on_btn_checkChange_rejected();
};

#endif // CHANGETEAINFO_H
