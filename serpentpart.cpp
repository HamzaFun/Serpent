#include "serpentpart.h"

#include <QBrush>
#include <QPen>

SerpentPart::SerpentPart(PartType type, SerpentPart *preced, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    QLinearGradient gradient(0, 30, 50,30);
    gradient.setColorAt(1,   QColor("#1CB5E0"));
    gradient.setColorAt(0, QColor("#000046"));
    setRect(QRectF(-12, -12, 24, 24));
    setDirection(SerpentPart::Direction::left);
    this->type = type;
    switch (type ) {
    case PartType::tete :
        setBrush(QBrush(QGradient(gradient)));
//        setPen(QPen(Qt::NoPen));
        return;
        break;
    case PartType::queue :
        gradient.setColorAt(0, QColor(Qt::red));
        setBrush(QBrush(QGradient(gradient)));
//        setPen(QPen(Qt::NoPen));
        this->setPos(preced->pos().x()+preced->boundingRect().width(), preced->pos().y());
        return;
        break;
    case PartType::partie :
        this->setPos(preced->pos().x()+preced->boundingRect().width(), preced->pos().y());
    default:
        break;
    }

}

void SerpentPart::setPreced(SerpentPart *part)
{
    preced = part;
}

SerpentPart *SerpentPart::Preced()
{
    return preced;
}

void SerpentPart::setDirection(enum SerpentPart::Direction  dir)
{
    switch(direction){
    case SerpentPart::Direction::left :
        switch(dir){
        case SerpentPart::Direction::right :
            setRotation(-180);
            break;
        case SerpentPart::Direction::up :
            setRotation(90);
            break;
        case SerpentPart::Direction::down :
            setRotation(-90);
            break;
        default:
            break;
        }
        break;
    case SerpentPart::Direction::right :
        switch(dir){
        case SerpentPart::Direction::left :
            setRotation(0);
            break;
        case SerpentPart::Direction::up :
            setRotation(90);
            break;
        case SerpentPart::Direction::down :
            setRotation(-90);
            break;
        default:
            break;
        }

        break;
    case SerpentPart::Direction::up :
        switch(dir){
        case SerpentPart::Direction::right :
            setRotation(-180);
            break;
        case SerpentPart::Direction::left :
            setRotation(0);
            break;
        case SerpentPart::Direction::down :
            setRotation(-90);
            break;
        default:
            break;
        }

        break;
    case SerpentPart::Direction::down :
        switch(dir){
        case SerpentPart::Direction::right :
            setRotation(-180);
            break;
        case SerpentPart::Direction::up :
            setRotation(90);
            break;
        case SerpentPart::Direction::left :
            setRotation(0);
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }

    direction = dir;
}

void SerpentPart::move(enum SerpentPart::Direction dir)
{
    switch(dir){
    case SerpentPart::Direction::right :
        setDirection(SerpentPart::Direction::right);
        if(pos().x()+24 >= 550) setPos( -12,pos().y());
        setPos(pos().x()+25,pos().y());
        break;
    case SerpentPart::Direction::left :
        if(pos().x()+24 <= 48) setPos( 562,pos().y());
        setDirection(SerpentPart::Direction::left);
        setPos(pos().x()-25,pos().y());
        break;
    case SerpentPart::Direction::down :
        if(pos().y() >= 524) setPos( pos().x(), 0);
        setDirection(SerpentPart::Direction::down);
        setPos(pos().x(),pos().y()+25);
        break;
    case SerpentPart::Direction::up :
        if(pos().y() <= 25) setPos( pos().x(), 550);
        setDirection(SerpentPart::Direction::up);
        setPos(pos().x(),pos().y()-25);
        break;
    default:
        break;
    }
}

void SerpentPart::moveto(SerpentPart *dest)
{
    setPos(dest->pos().x(), dest->pos().y());
    setDirection(dest->Direction());
}

enum SerpentPart::Direction SerpentPart::Direction()
{
    return direction;
}


