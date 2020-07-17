#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include <QMediaPlayer>


class graphics : public QWidget
{
    Q_OBJECT
public:
    explicit graphics(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    QPixmap spritesheet;
    QMediaPlayer *sound;
    double boatPosition;
    int position;
    int edge;
    void drawFruit(QPainter& painter,QPointF diemBD,double BK);
    QPointF move(QPointF p, double kc, int huong);
    QPointF rotate(QPointF p, QPointF c, int deg);
    void river(QPainter &painter);
    void sky(QPainter &painter);
    void body_edge(QPainter &painter);
    void cloud(QPainter &painter);
    void sun(QPainter &painter);
    void tree(QPainter &painter);
    void setPositionFruit(QPainter &painter);
    void riverSide(QPainter &painter);

    void drawEgde(QPainter& painter, QPointF center, int r, int n);

    double timerId ;
    int offsetY[3];
    int positionA[3];
    int positionB[3];
    int positionBoat;
    int positionBoat1;
    int positionBoat2;
    int positionOnBoat1;
    int positionOnBoat2;

    int monksPosition[3];
    int demonsPosition[3];

    void chuyen0nguoi1quy ();
    void chuyen0nguoi2quy ();
    void chuyen1nguoi0quy ();
    void chuyen1nguoi1quy ();
    void chuyen2nguoi0quy ();

    void dichuyenthuyen1(int isMonk, int id);
    void dichuyenthuyen2(int isMonk1, int isMonk2, int id1, int id2);
    void xuongThuyen(int isMonk, int id);
    void lenBo(int isMonk, int id);
signals:

public slots:

};

#endif // GRAPHICS_H
