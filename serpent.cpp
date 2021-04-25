#include "serpent.h"
#include "serpentpart.h"
#include "jeu.h"

#include <QKeyEvent>
#include <QDebug>
extern Jeu * jeu;

Serpent::Serpent(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    length =4;
    map = new QMap<int, SerpentPart*>();
    tete = new SerpentPart(SerpentPart::PartType::tete, nullptr, nullptr);
    tete->setPreced(nullptr);
    tete->setPos(200,200);
    map->insert(0, tete);
    int i=1;
        for(i=1; i< length; ++i){
            SerpentPart *part = new SerpentPart(SerpentPart::PartType::partie, map->value(i-1));
            part->setPreced(map->value(i-1));

            map->insert(i, part);
        }
    queue = new SerpentPart(SerpentPart::PartType::queue, map->value(i-1));
    queue->setPreced(map->value(i-1));
    map->insert(i,queue);
}

void Serpent::keyPressEvent(QKeyEvent *action)
{

    switch(action->key()){
    case Qt::Key_Left :
        suivre();
        tete->move(SerpentPart::Direction::left);
        break;
    case Qt::Key_Right :
        suivre();
        tete->move(SerpentPart::Direction::right);
        break;
    case Qt::Key_Up :
        suivre();
        tete->move(SerpentPart::Direction::up);
        break;
    case Qt::Key_Down :
        suivre();
        tete->move(SerpentPart::Direction::down);
        break;
    default:
        break;
    }

}

void Serpent::suivre()
{
    int i= 0;
    for(i=map->count()-1; i > 0 ; --i){
        map->value(i)->moveto(map->value(i-1));
    }
    qDebug() << map->count();

}
