#include "graphics.h"
#include <QPainter>
#include <QString>
#include <QRect>
#include <QWidget>
#include <QColor>
#include <QAbstractState>
#include <math.h>
#include <QPixmap>
#include <QPointF>
#include <QDebug>
#include <QUrl>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <windows.h>

graphics::graphics(QWidget *parent) :
    QWidget(parent)
{
      timerId = startTimer(20);
      positionA[0] = 1200;
      positionA[1] = 1300;
      positionA[2] = 1400;
      positionB[0] = 100;
      positionB[1] = 200;
      positionB[2] = 300;
      // vi tri thuyen tren bo A
      positionBoat1 = 900;
      // vi tri thuyen tren bo B
      positionBoat2 = 400;
      // vi tri thuyen hien tai
      positionBoat = positionBoat1;
      // vi tri 1 ngoi tren thuyen
      positionOnBoat1 = positionBoat + 20;
      // vi tri 2 ngoi tren thuyen
      positionOnBoat2 = positionBoat + 100;
      // do doi cua thay tu khi buoc len thuyen
      offsetY[0] = 0;
      offsetY[1] = 0;
      offsetY[2] = 0;
      monksPosition[0] = positionA[0];
      monksPosition[1] = positionA[1];
      monksPosition[2] = positionA[2];
      demonsPosition[0] = positionA[0];
      demonsPosition[1] = positionA[1];
      demonsPosition[2] = positionA[2];
      position = 0;
      edge = 0;
      sound = new QMediaPlayer();
      sound->setMedia(QUrl("E:/AI project/boat_rowing.wav"));
}
void graphics::timerEvent(QTimerEvent *)
{
        position+=1;
        edge +=3;
        repaint();
}

QPointF graphics::move(QPointF p, double kc, int huong){
    QPointF pnew;
    pnew.setX(p.x()+kc*cos(M_PI*huong/180));
    pnew.setY(p.y()+kc*sin(M_PI*huong/180));
    return pnew;
//    int c = v;
}

//hàm xoay (đồ họa con rùa)
QPointF graphics::rotate(QPointF p, QPointF c, int deg){
    QPoint newp;
    double rad = deg*M_PI/180;
    newp.setX(c.x() + (p.x() - c.x())*cos(rad) - (p.y() - c.y())*sin(rad));
    newp.setY(c.y() + (p.x() - c.x())*sin(rad) + (p.y() - c.y())*cos(rad));
    return newp;
}

//hàm vẽ cánh quạt và truyền chuyển động cho cánh quạt
void graphics::drawEgde(QPainter& painter, QPointF center, int r, int n){
   double w = center.x();
   double h = center.y();

   painter.setPen(Qt::black);

   QPointF a(w-20, h);
   QPointF b(w+20, h);

   QPointF c(w+5, h-r);
   QPointF d(w-35, h-r);

   QPointF e(w-35, h-r+50);
   QPointF f(w-5, h-r+50);

   QPointF g(w-5, h);

   painter.setBrush(QColor("#ffff66"));
   for(int i = 0; i < n; i++){
       QPointF a1 = rotate(a, center, i*(360/n)+edge);
       QPointF b1 = rotate(b, center, i*(360/n)+edge);
       QPointF c1 = rotate(c, center, i*(360/n)+edge);
       QPointF d1 = rotate(d, center, i*(360/n)+edge);
       QPointF e1 = rotate(e, center, i*(360/n)+edge);
       QPointF f1 = rotate(f, center, i*(360/n)+edge);
       QPointF g1 = rotate(g, center, i*(360/n)+edge);
       QPainterPath path;
       path.moveTo(a1);
       path.lineTo(b1);
       path.lineTo(c1);
       path.lineTo(d1);
       path.lineTo(e1);
       path.lineTo(f1);
       path.lineTo(g1);
       painter.drawPath(path);
   }
   painter.drawEllipse(center, r/10, r/10);
}
void graphics::body_edge(QPainter &painter){
    QPointF body_edge[4] = {
       QPointF(1290,250),
       QPointF(1280,500),
       QPointF(1320,500),
       QPointF(1310,250),
    };
    painter.setPen(QPen(QBrush("#99ccff"), 5));
    painter.setBrush(QColor("#80b3ff"));
    painter.drawPolygon(body_edge,4);
}

void graphics::sky(QPainter &painter){
    QRect rect(0,0,1920,350);
    QLinearGradient gradient(rect.x(), rect.y(), rect.x(), rect.y() + rect.height()); // dùng QRadialGradient để làm cho màu sắc của sự vật có độ dốc
          gradient.setColorAt(0.2, QColor("#cce6ff"));
          gradient.setColorAt(0.8, QColor("#66b5ff"));
          gradient.setSpread(QGradient::ReflectSpread); //Độ dốc được phản ánh bên ngoài khu vực gradient
             painter.setPen(Qt::NoPen);
             painter.setBrush(gradient);
             painter.drawRect(rect);
}

//hàm vẽ mây
void graphics::cloud(QPainter &painter){
    QRadialGradient radialGrad(QPointF(500, 300), 1000); // dùng QRadialGradient để làm cho màu sắc của sự vật có độ dốc
     radialGrad.setColorAt(0.2, QColor("#f2f2f2"));
     radialGrad.setColorAt(0.4, QColor("#ffffff"));
     radialGrad.setColorAt(1, QColor("#f2f2f2"));
    QBrush brush(radialGrad);
    painter.setBrush(brush);
    QPen pen;
    pen.setStyle(Qt::NoPen);
    painter.setPen(pen);
    painter.drawEllipse(780-200,100,150,100);
    painter.drawEllipse(870-200,130,150,100);
    painter.drawEllipse(850-200,70,150,100);
    painter.drawEllipse(950-200,100,150,100);
    painter.drawEllipse(990-200,60,150,100);

    pen.setStyle(Qt::NoPen);
    painter.setPen(pen);
    painter.drawEllipse(1130-200,150,180,100);
    painter.drawEllipse(1220-200,180,180,100);
    painter.drawEllipse(1200-200,120,180,100);
    painter.drawEllipse(1300-200,150,180,100);
    painter.drawEllipse(1340-200,110,180,100);
}
//hàm vẽ mặt troi
void graphics::sun(QPainter &painter){
    QRadialGradient radialGrad(QPointF(250, 100), 300);  // dùng QRadialGradient để làm cho màu sắc của sự vật có độ dốc
        radialGrad.setColorAt(0, QColor("#ffff80"));
        radialGrad.setColorAt(0.2, QColor("#ffff80"));
        radialGrad.setColorAt(0.7, QColor("#ffff80"));
        radialGrad.setColorAt(0.7, QColor("#ffff00"));
        radialGrad.setColorAt(0.5, QColor("#ffff00"));
        QBrush brush(radialGrad);
        painter.setBrush(brush);
        QPen pen;
        pen.setStyle(Qt::NoPen);
        painter.setPen(pen);
        painter.drawEllipse(200, 20, 150, 150);
}
void graphics::river(QPainter &painter){
    QRect rect(0,0,1920,1080);
    QLinearGradient gradient(rect.x(), rect.y(), rect.x(), rect.y() + rect.height()); // dùng QRadialGradient để làm cho màu sắc của sự vật có độ dốc
          gradient.setColorAt(0.2, QColor("#1a8cff"));
          gradient.setColorAt(0.8, QColor("#1a8cff"));
          gradient.setSpread(QGradient::ReflectSpread); //Độ dốc được phản ánh bên ngoài khu vực gradient
             painter.setPen(Qt::NoPen);
             painter.setBrush(gradient);
             painter.drawRect(rect);
              for(int i = 1;i<=1000;i++){ // i càng tăng thì mật độ tuyết càng dày
                 painter.setPen(Qt::NoPen);
                 painter.setBrush(QColor(255,255,255));

              }

}
void graphics::tree(QPainter &painter){
      //gốc cây
    painter.setPen(QColor("#6e4a02"));
    painter.setBrush(QBrush("#5c5b18"));
    painter.drawEllipse(20,500,235,60);
    painter.setPen(QPen(Qt::black, 3 , Qt::SolidLine));
      //thân cây
    painter.setPen(QColor("#6e4a02"));
    painter.setBrush(QBrush("#6e4a02"));
    painter.drawRect(110,320,50,210);
    painter.setPen(QColor("#7d5f05"));
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QColor("#614202"));
      //tán cây
    painter.setPen(QColor("#048004"));
    painter.setBrush(QBrush("#048004"));
    painter.drawEllipse(0,270,150,120);
    painter.drawEllipse(90,200,150,120);
    painter.drawEllipse(100,280,150,120);
    painter.drawEllipse(0,200,150,120);
    painter.drawEllipse(60,280,150,120);
    painter.drawEllipse(120,230,150,120);
}

void graphics::riverSide(QPainter &painter){
    QRadialGradient radialGrad2(QPointF(350, 1150), 800); // dùng QRadialGradient để làm cho màu sắc của sự vật có độ dốc
        radialGrad2.setColorAt(0.5, QColor("#b37700"));
        radialGrad2.setColorAt(1, QColor("#b37700"));
        QBrush brush2(radialGrad2);
        painter.setBrush(brush2);
        QPen pen2;
        pen2.setStyle(Qt::NoPen);
        painter.setPen(pen2);
        painter.drawEllipse(-500,340,950,600);
        painter.drawEllipse(1100,350,1500,600);

        }
//vẽ ngôi sao
void graphics::drawFruit(QPainter&  painter,QPointF diemBD,double BK){
    QPointF Goc=diemBD;
    //Tìm đa giác
    QPolygonF DaGiac;
    for(int i=0;i<5;i++)
        DaGiac<<move(Goc,BK,-90+i*360/5);
    for(int k=0;k<3;k++){
         painter.drawLine(DaGiac.value(k),DaGiac.value(k+2));
        if(k<2)  painter.drawLine(DaGiac.value(k),DaGiac.value(k+3));
    }
}
void graphics::setPositionFruit(QPainter& painter){
    painter.setPen(QPen(QBrush("#ff5050"), 10));
    painter.setBrush(QColor("#ff5050"));
    int step=30;
     QPointF Goc_2(width()/2-750,height()/2-180);
     drawFruit(painter,move(Goc_2,step*4,360/20+20*36),step/3);

     QPointF Goc_3(width()/2-800,height()/2-150);
     drawFruit(painter,move(Goc_3,step*4,360/20+20*36),step/3);

     QPointF Goc_4(width()/2-690,height()/2-150);
     drawFruit(painter,move(Goc_4,step*4,360/20+20*36),step/3);

     QPointF Goc_5(width()/2-700,height()/2-100);
     drawFruit(painter,move(Goc_5,step*4,360/20+20*36),step/3);

     QPointF Goc_6(width()/2-750,height()/2-130);
     drawFruit(painter,move(Goc_6,step*4,360/20+20*36),step/3);

     QPointF Goc_7(width()/2-760,height()/2-80);
     drawFruit(painter,move(Goc_7,step*4,360/20+20*36),step/3);

     QPointF Goc_8(width()/2-800,height()/2-100);
     drawFruit(painter,move(Goc_8,step*4,360/20+20*36),step/3);
}

void graphics::paintEvent(QPaintEvent *){

    QPainter painter (this);
    painter.setRenderHint(QPainter::Antialiasing);

    river(painter);
    sky(painter);
    cloud(painter);
    riverSide(painter);
    body_edge(painter);
    QPointF a(1300, 270);
    drawEgde(painter,a,170,4);
    tree(painter);
    setPositionFruit(painter);
    sun(painter);
    QString monkImageFile = "E:/AI project/images/monk.png";
    QString demonImageFile = "E:/AI project/images/demon.png";
    QString boatImageFile = "E:/AI project/images/boat.png";
    painter.drawPixmap(positionBoat, 640, 250, 150, QPixmap(boatImageFile));
    painter.drawPixmap(monksPosition[0], 490 + offsetY[0], 150, 150, QPixmap(monkImageFile));
    painter.drawPixmap(monksPosition[1], 490 + offsetY[1], 150, 150, QPixmap(monkImageFile));
    painter.drawPixmap(monksPosition[2], 490 + offsetY[2], 150, 150, QPixmap(monkImageFile));
    painter.drawPixmap(demonsPosition[0], 570, 130, 150, QPixmap(demonImageFile));
    painter.drawPixmap(demonsPosition[1], 570, 130, 150, QPixmap(demonImageFile));
    painter.drawPixmap(demonsPosition[2], 570, 130, 150, QPixmap(demonImageFile));
}

//lenbo xuong bo A - B, qua trai, qua phai
void graphics::dichuyenthuyen1(int isMonk, int id){
//    int tmp = 0;
    int i = 0;
    sound->play();

    // thuyen ben bo A
    if (positionBoat == positionBoat1) {
        if (isMonk == 1) {
            // dat tu si len thuyen
            monksPosition[id] = positionOnBoat1;
            offsetY[id] = 80;
            sound->stop();
        } else {
            // put demon on boat
            demonsPosition[id] = positionOnBoat1;
        }

        while (positionBoat > positionBoat2){
            sound->play();
            if (isMonk == 1) {
                monksPosition[id] -= 5;
                sound->stop();
            }
            else {
                demonsPosition[id] -= 5;
            }
            positionBoat -= 5;
            repaint();
        }

        sound->stop();
        if (isMonk == 1) {
            // dat tu si len bo;
            monksPosition[id] = positionB[id];
        }
        else {
            // dat con quy len bo;
            demonsPosition[id] = positionB[id];
        }
        positionBoat = positionBoat2;
    }
    else {
        if (isMonk == 1) {
            // dat tu si len thuyen
            monksPosition[id] = positionOnBoat1;
            offsetY[id] = 80;
            sound->stop();
        }
        else {
            // dat con quy len thuyen
            demonsPosition[id] = positionOnBoat1;
        }
        sound->play();

        while (positionBoat < positionBoat1){
            if (isMonk == 1) {
                monksPosition[id] += 5;
            }
            else {
                demonsPosition[id] += 5;
            }
            positionBoat += 5;
            repaint();
        }
        sound->stop();

        if (isMonk == 1) {
            // dat tu si len bo;
            monksPosition[id] = positionA[id];
        }
        else {
            // dat con quy len bo
            demonsPosition[id] = positionA[id];
        }
        positionBoat = positionBoat1;
    }
    // Reset lai 2 vi tri ngoi tren thuyen
    positionOnBoat1 = positionBoat + 20;
    positionOnBoat2 = positionBoat + 100;

    // reset do doi Y
    offsetY[id] = 0;
}


void graphics::dichuyenthuyen2(int isMonk1, int isMonk2, int id1, int id2){
//    int tmp = 0;
    int i = 0;
    sound->play();
    if (positionBoat == positionBoat1) {
        // if obj1 is monk
        if (isMonk1 == 1) {
            // but monk 1 on boat
            monksPosition[id1] = positionOnBoat1;
            offsetY[id1] = 80;
        }
        else {
            // but demon 1 on boat
            demonsPosition[id1] = positionOnBoat1;
        }
        // if obj2 is monk
        if (isMonk2 == 1) {
            // but monk 2 on boat
            monksPosition[id2] = positionOnBoat2;
            offsetY[id2] = 80;
        }
        else {
            // but demon 2 on boat
            demonsPosition[id2] = positionOnBoat2;
        }

        while (positionBoat > positionBoat2){

            if (isMonk1 == 1) {

                // move monk 1
                monksPosition[id1] -=5;
            }
            else {

                // move demon 1
                demonsPosition[id1] -=5;
            }

            if (isMonk2 == 1) {

                // move monk 2
                monksPosition[id2] -=5;
            }
            else {
                // move demon 2
                demonsPosition[id2] -=5;
            }

            positionBoat-=5;
            repaint();
        }
        sound->stop();

        if (isMonk1 == 1) {
            // put monk 1 on B
            monksPosition[id1] = positionB[id1];
        }
        else {
            // put demon 1 on B
            demonsPosition[id1] = positionB[id1];
        }

        if (isMonk2 == 1) {
            // put monk 2 on B
            monksPosition[id2] = positionB[id2];
        }
        else {
            // put demon 2 on B
            demonsPosition[id2] = positionB[id2];
        }
        positionBoat = positionBoat2;
    }
    else {
        // if obj1 is monk
        if (isMonk1 == 1) {
            // put monk 1 on boat
            monksPosition[id1] = positionOnBoat1;
            offsetY[id1] = 80;
        }
        else {
            // put demon 1 on boat
            demonsPosition[id1] = positionOnBoat1;
        }
        // if obj2 is monk
        if (isMonk2 == 1) {
            // put monk 2 on boat
            monksPosition[id2] = positionOnBoat2;
            offsetY[id2] = 80;
        }
        else {
            // put demon 2 on boat
            demonsPosition[id2] = positionOnBoat2;
        }
        sound->play();

        while (positionBoat < positionBoat1){

            if (isMonk1 == 1) {
                // move monk 1
                monksPosition[id1] +=5;
            }
            else {

                // move demon 1
                demonsPosition[id1] +=5;

            }

            if (isMonk2 == 1) {

                // move monk 2
                monksPosition[id2] +=5;
            }
            else {
                sound->play();
                // move demon 2
                demonsPosition[id2] +=5;
            }

            positionBoat += 5;
            repaint();
        }
        sound->stop();

        if (isMonk1 == 1) {
            monksPosition[id1] = positionA[id1];
        }
        else {
            // move demon 1
            demonsPosition[id1] = positionA[id1];
        }

        if (isMonk2 == 1) {
            // move monk 2
            monksPosition[id2] = positionA[id2];
        }
        else {
            // move demon 2
            demonsPosition[id2] = positionA[id2];
        }
        positionBoat = positionBoat1;
    }
    // Reset lai 2 vi tri ngoi tren thuyen
    positionOnBoat1 = positionBoat + 20;
    positionOnBoat2 = positionBoat + 100;
    offsetY[id1] = 0;
    offsetY[id2] = 0;
}

void graphics::chuyen0nguoi1quy () {
    // thuyen ben bo A
    if (positionBoat == positionBoat1) {
        int i;

        for (i = 0; i < 3; i++) {
            if (demonsPosition[i] == positionA[i]){
                demonsPosition[i] = positionB[i];
                // goi lien tiep 3 hanh dong:
                // 1 xuong thuyen
                // 2 di chuyen sang bo ben kia (bo B)
                // 3 buoc len bo B
                break;
            }
        }
        this->dichuyenthuyen1(0, i);
    } else {
        int i;
        for (i = 0; i < 3; i++) {
            if (demonsPosition[i] == positionB[i]){
                demonsPosition[i] = positionA[i];
                break;
            }
        }
        this->dichuyenthuyen1(0, i);
    }
}

void graphics::chuyen1nguoi0quy () {
    // thuyen ben bo A
    if (positionBoat == positionBoat1) {
        int i;

        for (i = 0; i < 3; i++) {
            if (monksPosition[i] == positionA[i]){
                monksPosition[i] = positionB[i];
                break;
            }
        }
        this->dichuyenthuyen1(1, i);
    } else {
        int i;
        for (i = 0; i < 3; i++) {
            if (monksPosition[i] == positionB[i]){
                monksPosition[i] = positionA[i];
                break;
            }
        }
        this->dichuyenthuyen1(1, i);

    }
}

void graphics::chuyen1nguoi1quy () {
    // thuyen ben bo A

    if (positionBoat == positionBoat1) {
        int i;

        for (i = 0; i < 3; i++) {
            if (monksPosition[i] == positionA[i]){
                monksPosition[i] = positionB[i];
                break;
            }
        }
        int j;
        for (j = 0; j < 3; j++) {
            if (demonsPosition[j] == positionA[j]){
                demonsPosition[j] = positionB[j];
                break;
            }
        }
        this->dichuyenthuyen2(1, 0, i, j);
    } else {
        int i;
        for (i = 0; i < 3; i++) {
            if (monksPosition[i] == positionB[i]){
                monksPosition[i] = positionA[i];
                break;
            }
        }
        int j;
        for (j = 0; j < 3; j++) {
            if (demonsPosition[j] == positionB[j]){
                demonsPosition[j] = positionA[j];
                break;
            }
        }
        this->dichuyenthuyen2(1, 0, i, j);
    }

}

void graphics::chuyen0nguoi2quy () {
    // thuyen ben bo A
    int counter = 2;
    if (positionBoat == positionBoat1) {
        int i;
        int c = -1, k;
        for (i = 0; i < 3; i++) {
            if (demonsPosition[i] == positionA[i] && counter > 0){
                if (c == -1) {
                    c = i;
                } else k = i;
                counter--;
            }
        }
//        positionBoat = positionBoat2;
        this->dichuyenthuyen2(0, 0, c, k);
    } else {
        int i;
        int c = -1, k;
        for (i = 0; i < 3; i++) {
            if (demonsPosition[i] == positionB[i] && counter > 0){
                if (c == -1) {
                    c = i;
                } else k = i;
                counter--;
            }
        }
        this->dichuyenthuyen2(0, 0, c, k);
    }
//    this->dichuyenthuyen();
}

void graphics::chuyen2nguoi0quy () {
    // thuyen ben bo A
    int counter = 2;
    if (positionBoat == positionBoat1) {
        int i;
        int c = -1, k;
        for (i = 0; i < 3; i++) {
            if (monksPosition[i] == positionA[i] && counter > 0){
                if (c == -1) {
                    c = i;
                } else k = i;
                counter--;
            }
        }
//        positionBoat = positionBoat2;
        this->dichuyenthuyen2(1, 1, c, k);
    } else {
        int i;
        int c = -1, k;
        for (i = 0; i < 3; i++) {
            if (monksPosition[i] == positionB[i] && counter > 0){
                if (c == -1) {
                    c = i;
                } else k = i;
                counter--;
            }
        }
        this->dichuyenthuyen2(1, 1, c, k);
//        this->dichuyenthuyen();
    }
//    this->dichuyenthuyen();
}

void graphics::xuongThuyen(int isMonk, int id) {
    if (isMonk == 1) {
        if (monksPosition[id] == positionA[id]) {
            monksPosition[id] = monksPosition[id] - 100;
        } else {
            monksPosition[id] = monksPosition[id] - 100;
        }
    }
}
