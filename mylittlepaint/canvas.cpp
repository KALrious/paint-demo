#include "canvas.h"

Canvas::Canvas(QWidget *parent):QGraphicsScene(parent)
{

    inpress=false;
    drawn=false;
    myPen=QPen();
    myPen.setWidth(2);
    item=0;

}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent  *event)
{
    if(!drawn) drawn=true;

    if(event->buttons()& Qt::LeftButton & !inpress  ){
        firstPoint=event->scenePos();
        inpress=true;
    }

}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent  *event)
{
    inpress=false;
    item=0;
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent  *event)
{
    if(inpress && (event->buttons() & Qt::LeftButton)){
        switch(mymode){
        case line:
            drawLine(event->scenePos());
            break;
         case rect:
            drawMyRect(event->scenePos());
            break;
         case ellipse:
            drawMyEllipse(event->scenePos());
            break;
         case eraser:
            erase(event->scenePos());
            break;
         default:
            freeHand(event->scenePos());
            break;
        }
    }
}



void Canvas::freeHand(QPointF pf)
{
    addLine(QLineF(firstPoint,pf),myPen);
    firstPoint=pf;
}

void Canvas::erase(QPointF pf)
{
    QPen p(myPen);
    p.setColor(Qt::white);
    addLine(QLineF(firstPoint,pf),p);
    firstPoint=pf;
}

void Canvas::drawMyRect(QPointF pf)
{
if(item){
    this->removeItem(item);
   }
double minX=firstPoint.x()<pf.x()?firstPoint.x():pf.x();
double maxX=firstPoint.x()>pf.x()?firstPoint.x():pf.x();
double minY=firstPoint.y()<pf.y()?firstPoint.y():pf.y();
double maxY=firstPoint.y()>pf.y()?firstPoint.y():pf.y();
double width=(maxX - minX)>0?maxX-minX:0;
double height=(maxY-minY)>0?maxY-minY:0;
QRectF newRect(minX, minY,width ,height );
item=this->addRect(newRect,myPen);
}

void Canvas::drawLine(QPointF end)
{
    if(item){
        this->removeItem(item);
       }
    item=this->addLine(QLineF(firstPoint,end),myPen);

}

void Canvas::drawMyEllipse(QPointF end)
{
    if(item)
        this->removeItem(item);

QRectF newRect(firstPoint,end);
item=this->addEllipse(newRect,myPen);
}

void Canvas::setMode(Canvas::Mode m)
{
    this->mymode=m;
}

void Canvas::setDrawn(bool d)
{
    drawn=d;
}

void Canvas::setPenColor(QColor c)
{
    this->myPen.setColor(c);
}

void Canvas::setPenWidth(int width)
{
    this->myPen.setWidth(width+2);
}



