#include "piewidget.h"
#include "ui_piewidget.h"

PieWidget::PieWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PieWidget)
{
    ui->setupUi(this);
}

PieWidget::~PieWidget()
{
    delete ui;
}

void PieWidget::updatePie(QVector<int> &data)
{
    piedata = data; //更新数据

    update();
}

void PieWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    //饼状图半径和中心坐标
    int radius = 100;
    int centerX = width() / 2;
    int centerY = height() / 2;
    //将笔刷设成透明
    QPen pen;
    pen.setColor(QColor(0, 0, 0, 0));
    painter.setPen(pen);

    //绘制1
    QColor sliceColor = QColor("#F25F5C"); //优秀的红色
    int startAngle = 0;
    int spanAngle = piedata[0];
    painter.setRenderHint(QPainter::Antialiasing); //抗锯齿
    painter.setBrush(sliceColor);
    painter.drawPie(centerX - radius, centerY - radius, 2 * radius, 2 * radius, startAngle * 16, spanAngle * 16);
    // 绘制2
    sliceColor = QColor("#A0E8AF"); //不错的绿色
    startAngle += spanAngle;
    spanAngle = piedata[1];
    painter.setBrush(sliceColor);
    painter.drawPie(centerX - radius, centerY - radius, 2 * radius, 2 * radius, startAngle * 16, spanAngle * 16);
    // 绘制3
    sliceColor = QColor("#FFCA3A"); //一般的黄色
    startAngle += spanAngle;
    spanAngle = piedata[2];
    painter.setBrush(sliceColor);
    painter.drawPie(centerX - radius, centerY - radius, 2 * radius, 2 * radius, startAngle * 16, spanAngle * 16);
    // 绘制4
    sliceColor = QColor("#2E5266"); //不及格的黑色
    startAngle += spanAngle;
    spanAngle = piedata[3];
    painter.setBrush(sliceColor);
    painter.drawPie(centerX - radius, centerY - radius, 2 * radius, 2 * radius, startAngle * 16, spanAngle * 16);

}
