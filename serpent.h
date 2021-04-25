#ifndef SERPENT_H
#define SERPENT_H

#include "serpentpart.h"

#include <QGraphicsRectItem>
#include <QMap>
#include <QObject>




class Serpent : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Serpent(QGraphicsItem* parent=0);
    void keyPressEvent(QKeyEvent * action);
    QMap<int, SerpentPart*> *map;
    SerpentPart *tete;
    SerpentPart *queue;
    void suivre();
private:
    int length;
};

#endif // SERPENT_H
