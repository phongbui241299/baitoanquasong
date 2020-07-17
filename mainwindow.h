#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int actions[100];
    int maxAction;
    int currentAction;
    
private slots:
    void on_pushButton_clicked();

    void on_btn_start_clicked();

    void on_btn_left_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
