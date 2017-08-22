#ifndef MYLITTLEPAINT_H
#define MYLITTLEPAINT_H

#include <QMainWindow>
#include<QColor>

#include"canvas.h"
namespace Ui {
class MyLittlePaint;
}

class MyLittlePaint : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyLittlePaint(QWidget *parent = 0);
    ~MyLittlePaint();
     void setCheckdButtnMode(Canvas::Mode m);

private slots:
    //color button event
    void on_colorbtn_clicked();
    //pencil button event
    void on_hand_clicked();
    //Line button event
    void on_line_clicked();
    //rectangle button event
    void on_rect_clicked();
    //ellipse button event
    void on_ellipse_clicked();
    //Erase button event
    void on_erase_clicked();
    //event for menu items;
    void newPNGImage();
    void openPNGImage();
    void savePNGImage();
    void printPNGImage();
    //quit event
    void quit();
    //about event
    void About();


private:
    Ui::MyLittlePaint *ui;
    //selected color
    QColor c;
    //saved file Name
    QString fileName;

    Canvas *mascene;
};

#endif // MYLITTLEPAINT_H
