#ifndef PIEWIDGET_H
#define PIEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QVector>

namespace Ui {
class PieWidget;
}

class PieWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PieWidget(QWidget *parent = nullptr);
    ~PieWidget();

    //更新饼图
    void updatePie(QVector<int> &data);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::PieWidget *ui;
    QVector<int> piedata = {90,90,90,90};
};

#endif // PIEWIDGET_H
