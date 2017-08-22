#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QPainterPath>
#include<QMouseEvent>
#include<QGraphicsSceneMouseEvent>
#include <QGraphicsPathItem>
#include <QColorDialog>
#include<QColor>
#include<QMessageBox>
#include<QFileDialog>
#include <QtPrintSupport/QPrinter>

class Canvas : public QGraphicsScene
{
    Q_OBJECT
public:
    //different Drawing modes
    enum Mode{hand,line,rect,ellipse,eraser};
    //constructor
    explicit Canvas(QWidget *parent=0);
    //mouse Events
    void mousePressEvent(QGraphicsSceneMouseEvent  *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent  *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent  *);
    //different drawing functions
    void freeHand(QPointF pf);
    void erase(QPointF pf);
    void drawMyRect(QPointF pf);
    void drawLine(QPointF end);
    void drawMyEllipse(QPointF end);




public slots:
    //set color for pen
    void setPenColor(QColor c);
    void setPenWidth(int width);
    bool isDrawn()const{return drawn;}
    void setDrawn(bool d);
    void setMode(Mode m);
private:
    //Item for draw
    QGraphicsItem *item;
    //start Point
    QPointF firstPoint;
    //pen for draw
    QPen myPen;
    //test if in mouse press mode for drawing
    bool inpress;
    //flag if user've drawn before
    bool drawn;
    //selected Mode
    Mode mymode;

};

#endif // CANVAS_H
