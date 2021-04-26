#include "murpart.h"

MurPart::MurPart(QString mur, QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    if(mur != NULL)
        murtype = mur;
    else
        murtype = "mur.png";

    setPixmap(QPixmap(":/images/"+murtype).scaled(40,40));
    setPos(0,0);
    setZValue(5);
}
