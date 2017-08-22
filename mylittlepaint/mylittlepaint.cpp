#include "mylittlepaint.h"
#include "ui_mylittlepaint.h"

MyLittlePaint::MyLittlePaint(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyLittlePaint)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(),this->height());
    mascene=new Canvas(this);
    mascene->setBackgroundBrush(Qt::white);
    mascene->setSceneRect(QRectF(0,0,ui->canvas->width(),ui->canvas->height()));
    ui->canvas->updateSceneRect(QRectF(0,0,ui->canvas->width(),ui->canvas->height()));
    ui->canvas->setScene(mascene);
    fileName="Sans Nom.png";
    // make draw button as (toggledbutton (on/off)
    ui->linebtn->setCheckable(true);
    ui->handbtn->setCheckable(true);
    ui->rectbtn->setCheckable(true);
    ui->ellipsebtn->setCheckable(true);
    ui->erasebtn->setCheckable(true);
    //set 'on' for pen button as default choice
     ui->handbtn->setChecked(true);
    //binding diffreent signal and slot between widgets
     //connection for menu items
     QObject::connect(ui->openItem,SIGNAL(triggered(bool)),this,SLOT(openPNGImage()));
     QObject::connect(ui->saveItem,SIGNAL(triggered(bool)),this,SLOT(savePNGImage()));
     QObject::connect(ui->printItem,SIGNAL(triggered(bool)),this,SLOT(printPNGImage()));
     QObject::connect(ui->newItem,SIGNAL(triggered(bool)),this,SLOT(newPNGImage()));
     QObject::connect(ui->quitItem,SIGNAL(triggered(bool)),this,SLOT(quit()));
     QObject::connect(ui->aboutItem,SIGNAL(triggered(bool)),this,SLOT(About()));
     //for slider and spinbox
    QObject::connect(ui->sliderEpaisseur,SIGNAL(valueChanged(int)),ui->spinBoxEpesseur,SLOT(setValue(int)));
    QObject::connect(ui->spinBoxEpesseur,SIGNAL(valueChanged(int)),ui->sliderEpaisseur,SLOT(setValue(int)));
    QObject::connect(ui->sliderEpaisseur,SIGNAL(valueChanged(int)),mascene,SLOT(setPenWidth(int)));
    QObject::connect(ui->spinBoxEpesseur,SIGNAL(valueChanged(int)),mascene,SLOT(setPenWidth(int)));
    //for palette button
    QObject::connect(ui->handbtn,SIGNAL(clicked()),this,SLOT(on_hand_clicked()));
    QObject::connect(ui->linebtn,SIGNAL(clicked()),this,SLOT(on_line_clicked()));
    QObject::connect(ui->rectbtn,SIGNAL(clicked()),this,SLOT(on_rect_clicked()));
    QObject::connect(ui->ellipsebtn,SIGNAL(clicked()),this,SLOT(on_ellipse_clicked()));
    QObject::connect(ui->erasebtn,SIGNAL(clicked()),this,SLOT(on_erase_clicked()));


}

MyLittlePaint::~MyLittlePaint()
{
    delete ui;
}

void MyLittlePaint::on_colorbtn_clicked()
{
    QColor c=QColorDialog::getColor();
    ui->colorlbl->setStyleSheet("QLabel { background-color :"+c.name()+"}");
    ui->colorlbl->setText(c.name().toUpper());
    this->c=c;
    emit this->mascene->setPenColor(c);
}

void MyLittlePaint::on_hand_clicked()
{
    if(!this->ui->handbtn->isChecked())
        ui->handbtn->setChecked(true);
    emit this->mascene->setMode(Canvas::hand);
    this->setCheckdButtnMode(Canvas::hand);
}

void MyLittlePaint::on_line_clicked()
{
    if(!this->ui->linebtn->isChecked())
        this->ui->linebtn->setChecked(true);
    emit this->mascene->setMode(Canvas::line);
    setCheckdButtnMode(Canvas::line);
}

void MyLittlePaint::on_rect_clicked()
{
    if(!this->ui->rectbtn->isChecked())
        this->ui->rectbtn->setChecked(true);
    emit this->mascene->setMode(Canvas::rect);
    setCheckdButtnMode(Canvas::rect);

}

void MyLittlePaint::on_ellipse_clicked()
{
    if(!this->ui->ellipsebtn->isChecked())
        this->ui->ellipsebtn->setChecked(true);
    emit this->mascene->setMode(Canvas::ellipse);
    setCheckdButtnMode(Canvas::ellipse);

}

void MyLittlePaint::on_erase_clicked()
{
    if(!this->ui->erasebtn->isChecked())
        this->ui->erasebtn->setChecked(true);
    emit this->mascene->setMode(Canvas::eraser);
    setCheckdButtnMode(Canvas::eraser);
}

void MyLittlePaint::newPNGImage()
{
    if(mascene->isDrawn()){
        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "mylittlePaint", "Vous voulez enregistrer la modification apporté à "+fileName,QMessageBox::Yes|QMessageBox::No|QMessageBox::Abort);
          if(reply==QMessageBox::Yes){
              emit savePNGImage();
              if(!fileName.isNull()){
                mascene->setDrawn(false);
                mascene->clear();
              }else
                  fileName="Sans Nom.png";
          }else{
              if(reply==QMessageBox::No){
                  mascene->setDrawn(false);
                  mascene->clear();
              }
          }
    }
}

void MyLittlePaint::openPNGImage()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir une image"),QDir::currentPath(),
                                            tr("Portable Network Graphics  (*.png)"));
  if(!fileName.isNull()){
      QImage im(fileName);
      if(!im.isNull()){
          QGraphicsPixmapItem* imageItem=new QGraphicsPixmapItem(QPixmap::fromImage(im));
          imageItem->setPos(ui->canvas->mapToScene(0,0));
         mascene->addItem(imageItem);
      }else{
          QMessageBox::critical(0,"Erreur d'image","le format d'image n'est pas supporté");
      }
  }else{
      QMessageBox::critical(0,"Erreur d'ouverture du fichier","pas de fichier sélectionné");
  }
}

void MyLittlePaint::savePNGImage()
{
     fileName = QFileDialog::getSaveFileName( this,
           tr("Save workshop"),
           QDir::currentPath(),
           tr("Portable Network Graphics (*.png)") );
    if(!fileName.isNull()){
        QImage pixmap(ui->canvas->width(),ui->canvas->height(), QImage::Format_RGB32);
        QPainter p;
        p.begin(&pixmap);
        p.setRenderHint(QPainter::Antialiasing, true);
        mascene->render(&p);
        p.end();
        pixmap.save(fileName, "PNG");
    }else{
        QMessageBox::critical(0,"Erreur de selection du fichier","pas de fichier selectionné");

    }

}

void MyLittlePaint::printPNGImage()
{
    QString  fileName = QFileDialog::getSaveFileName(this, tr("chemin d'exportation pdf"),QDir::currentPath(), tr("Portable Document Format(.pdf)"));
    if(!fileName.isNull()){
    QPrinter pdfPrinter;
    pdfPrinter.setOutputFormat( QPrinter::PdfFormat );
    pdfPrinter.setPaperSize( QSize(mascene->width(), mascene->height()), QPrinter::Point );
    pdfPrinter.setFullPage(true);
    pdfPrinter.setOutputFileName( fileName );

    QPainter pdfPainter;
    pdfPainter.begin( &pdfPrinter);
    mascene->render( &pdfPainter );
    pdfPainter.end();
    }else{
        QMessageBox::critical(0,"Erreur de selection du fichier","pas de fichier selectionné");
    }
}

void MyLittlePaint::quit()
{
    QApplication::quit();
}

void MyLittlePaint::About()
{
    QMessageBox::information(this,"A propos","My Little Paint est un Projet QT dans le cadre de la Formation:\n\n\t"
                                             "Interface Homme Machine (IHM)\n\n"
                                             "Developpé par: \n\tCHABRI Oussama & GIUILI Sacha\n"
                                             "Encadré par: \n\t Mr. HERRY");
}

void MyLittlePaint::setCheckdButtnMode(Canvas::Mode m)
{
    ui->handbtn->setChecked(m==Canvas::hand);
    ui->linebtn->setChecked(m==Canvas::line);
    ui->rectbtn->setChecked(m==Canvas::rect);
    ui->ellipsebtn->setChecked(m==Canvas::ellipse);
    ui->erasebtn->setChecked(m==Canvas::eraser);
}





