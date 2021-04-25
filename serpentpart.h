#ifndef SERPENTPART_H
#define SERPENTPART_H

#include <QGraphicsRectItem>

class SerpentPart : public QGraphicsRectItem
{

public:
    enum class PartType{
        Invalid, tete, partie, queue
    };
    enum class Direction{
        Invalid, up, down, left, right
    };

    SerpentPart(PartType type, SerpentPart *preced, QGraphicsItem *parent=0);
    void setPreced(SerpentPart *part);
    SerpentPart *Preced();
    Direction Direction();
    PartType type;
    void setDirection(enum Direction dir);
    void move(enum Direction dir);
    void moveto(SerpentPart* dest );
private:
    SerpentPart *preced;
    enum Direction direction;

};

#endif // SERPENTPART_H
