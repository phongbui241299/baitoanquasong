#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSound>
#include <QPointF>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FILE *fp = fopen("E:/AI project/File Demo.txt", "r");
    currentAction = 0;
    maxAction = 0;
    int i = 0;
    while(!feof(fp)) {
        int t;
        fscanf(fp, "%d", &t);
        actions[i++] = t;
        maxAction++;
    }

    fclose(fp);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//    {"First State", "Chuyen 0 nguoi 1 quy","Chuyen 1 nguoi 0 quy",
//                        "Chuyen 1 nguoi 1 quy","Chuyen 0 nguoi 2 quy",
//                        "Chuyen 2 nguoi 0 quy"};
    printf("MAX: %d", maxAction);
    if(currentAction < maxAction){
            switch (actions[currentAction]) {
                case 1:
                    ui->GraphicsPresenter->graphics::chuyen0nguoi1quy();
                    break;
                case 2:
                    ui->GraphicsPresenter->graphics::chuyen1nguoi0quy();
                    break;
                case 3:
                    ui->GraphicsPresenter->graphics::chuyen1nguoi1quy();
                    break;
                case 4:
                    ui->GraphicsPresenter->graphics::chuyen0nguoi2quy();
                    break;
                case 5:
                    ui->GraphicsPresenter->graphics::chuyen2nguoi0quy();
                    break;
                default: break;
            }
            char* tenAction[7] = {
                "First State", "Chuyen 0 nguoi 1 quy","Chuyen 1 nguoi 0 quy",
                                        "Chuyen 1 nguoi 1 quy","Chuyen 0 nguoi 2 quy",
                                        "Chuyen 2 nguoi 0 quy"};
            if (currentAction+1 <= maxAction) {
                // action
                QString str = tenAction[actions[currentAction+1]];
                ui->label_2->setText(str);
            }
            repaint();
//            ui->label_2->setText(str);
        } else {
            /*ui->label_2->setText("No more moves!!");*/
            ui->pushButton->setText("Done");
            ui->label_2->setText("FINISH!");
            ui->pushButton->setEnabled(false);
        }
        currentAction++;
}
