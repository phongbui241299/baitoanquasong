#include "boat.h"
#include <QPixmap>
#include <graphics.h>
boat::boat(QWidget *parent) :
    QWidget(parent)
{
}
void graphics::boat(QPainter& painter, int isToRight){
    /*
     * Bo A (ben phair):
     *  monks = 1200 - 400, 1300 - 400, 1400 - 400
     *  demons = 1200 - 550, 1300 - 550, 1400 - 500
     *
     * Bo B (ben trai):
     *  monks = 200 - 400, 300- 400, 400 - 400
     *  demons = 200 - 550, 300 - 550, 400 - 500
     *
     *
     **/

//    int r = 100;
    int w = width();
    int h = height();
    int tmp = 0;
//        QPixmap a = painter.drawPixmap(1200,490,w_monk,h_monk,QPixmap(monkImages1));
//        QPixmap b = painter.drawPixmap(1300,490,w_monk,h_monk,QPixmap(monkImages2));
////        QPixmap c = painter.drawPixmap(1400,490,w_monk,h_monk,QPixmap(monkImages3));
//        painter.drawPixmap(1200,490,w_monk,h_monk,QPixmap(monkImages1));
//        painter.drawPixmap(1300,490,w_monk,h_monk,QPixmap(monkImages2));
//         painter.drawPixmap(1400,490,w_monk,h_monk,QPixmap(monkImages3));

    /*******************************/
//    if (isToRight == 1) {
//        if (boatPosition + 400 < 900) {
//            tmp += 3;
//            boatPosition = boatPosition + tmp;
//            painter.drawPixmap(boatPosition + 400,550,w_boat,h_boat,QPixmap(boatImage));
//            //delete this
//            painter.drawPixmap(boatPosition + 400,500,w_monk,h_monk,QPixmap(monkImages1));
//            painter.drawPixmap(boatPosition + 400,500,w_monk,h_monk,QPixmap(monkImages2));

//        } else {
//            boatPosition = 900 - 400;
//            painter.drawPixmap(boatPosition + 400,550,w_boat,h_boat,QPixmap(boatImage));
//            painter.drawPixmap(1100,500,w_monk,h_monk,QPixmap(monkImages1));
//            painter.drawPixmap(1200,500,w_monk,h_monk,QPixmap(monkImages2));

//        }
//    }
//    if (isToRight == 0) {
//        if (boatPosition > 0) {
//            tmp -= 3;
//            boatPosition = boatPosition + tmp;
//            painter.drawPixmap(boatPosition + 400,550,w_boat,h_boat,QPixmap(boatImage));
//            painter.drawPixmap(boatPosition + 400,500,w_monk,h_monk,QPixmap(monkImages1));
//            painter.drawPixmap(boatPosition + 400,500,w_monk,h_monk,QPixmap(monkImages2));

//        } else {
//            boatPosition = 0;
//            painter.drawPixmap(boatPosition + 400,550,w_boat,h_boat,QPixmap(boatImage));
//            painter.drawPixmap(100,400,w_monk,h_monk,QPixmap(monkImages1));
//            painter.drawPixmap(200,400,w_monk,h_monk,QPixmap(monkImages2));

//        }
//    }
}
