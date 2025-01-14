#include "button.h"
#include "jeu.h"
#include "murpart.h"
#include "obstacles.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QPushButton>
#include <QStyle>
#include <QTimer>

Jeu::Jeu(QWidget *parent):QGraphicsView(parent)
{
    // charger la vue :
    setFixedSize(1200,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // charger la scene de jeu
    background = new QGraphicsPixmapItem();
    sceneDeJeu = new QGraphicsScene(this);
    sceneDeJeu->setSceneRect(0,0,1200,600);
    setScene(sceneDeJeu);

    score =new Score();
    sceneDeJeu->addItem(score);
    serp2 =NULL;
    serp = NULL;
    setWindowIcon(QIcon(":/images/snake.ico"));

    StageCourant = 1;
}

void Jeu::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape :

        break;
    default:
        break;
    }
    if(serp){
        serp->keyPressEvent(event);
    }else
        QGraphicsView::keyPressEvent(event);

}
void Jeu::afficherFin(QString titre, QString jouer)
{
    titreText = new QGraphicsTextItem(titre);
    QFont titreFont("roboto", 50 );
    titreText->setFont(titreFont);
    int xPos = width()/2 - titreText->boundingRect().width()/2;
    int yPos = 100;
    titreText->setPos(xPos, yPos);
    titreText->setDefaultTextColor(Qt::white);
    sceneDeJeu->addItem(titreText);

    Button* menu = new Button("STAGES", 150,40, titreText);
    int mxPos = 100 ;
    int myPos = 120;
    menu->setPos(mxPos,myPos);

    connect(menu, SIGNAL(clicked()), this, SLOT(afficherStages()));

    Button* joue = creerStg(jouer, 150, 40, 100, 170, 0, true, titreText);
    Button* quit = new Button("<< RETOUR", 150, 40, titreText);
    int rx = 100;
    int ry = 220;
    quit->setPos(rx,ry);
    connect(quit, SIGNAL(clicked()), this, SLOT(retourAffich()));
    Q_UNUSED(joue);
    Q_UNUSED(quit);

}
void Jeu::afficherMenu(QString titre, QString jouer)
{

    background->setPixmap(QPixmap(":/bg/bg/menu.jpg").scaled(1200,600));
    background->setZValue(0);
    sceneDeJeu->addItem(background);
    titreText = new QGraphicsTextItem(titre);
    QFont titreFont("roboto", 50 );
    titreText->setFont(titreFont);
    titreText->setDefaultTextColor(Qt::white);
    int xPos = width()/2 - titreText->boundingRect().width()/2;
    int yPos = 150;
    titreText->setPos(xPos, yPos);
    sceneDeJeu->addItem(titreText);

    Button* menu = new Button("STAGES", 150,40, titreText);
    int mxPos = 100 ;
    int myPos = 140;
    menu->setPos(mxPos,myPos);

    connect(menu, SIGNAL(clicked()), this, SLOT(afficherStages()));

    Button* joue = creerStg(jouer, 150, 40, 100, 190, 0, true, titreText);
    Button* quit = creerStg("QUITTER", 150, 40, 100,240, 0, false, titreText);

    Q_UNUSED(joue);
    Q_UNUSED(quit);

}

void Jeu::finJeu()
{
    afficherFin("Fin De Jeu", "ReJouer");
    sceneDeJeu->removeItem(serp);
    serp = NULL;
}

Button* Jeu::creerStg(QString text, int w, int h, int xpos, int ypos, int stg, bool debut, QGraphicsTextItem *pere)
{
    Button* button;
    if(stg != 0) {
        button = new Button(text, w, h, stg, pere);
        if(stg <= StageCourant){
            button->deletelock();
        }
        button->setHoverd();
        connect(button, SIGNAL(clicked(int)),this,SLOT(creerObs(int)));
    }
    else if(debut)
    {
        button = new Button(text, w, h, pere);
        connect(button, SIGNAL(clicked(int)),this,SLOT(debut()));
    }
    else {
        button = new Button(text, w, h, pere);
        connect(button, SIGNAL(clicked(int)),this,SLOT(close()));
    }

    button->setPos( xpos, ypos);
    return button;
}



void Jeu::debut()
{
    if(obs == NULL){
        background->setPixmap(QPixmap(":/bg/bg/bg4.png").scaled(1200,600));
        background->setZValue(0);
        sceneDeJeu->addItem(background);
    }
    serp = new AnimerSerpent();
    serp->setFlag(QGraphicsItem::ItemIsFocusable);
    serp->setFocus();
    sceneDeJeu->addItem(serp);
    score->setVisible(true);
    score->setScore(0);
    if(pauseText != NULL){
        sceneDeJeu->removeItem(pauseText);
        delete pauseText;
        pauseText = NULL;
    }
    if(titreText != NULL){
        sceneDeJeu->removeItem(titreText);
        delete titreText;
        titreText = NULL;
    }
    if(stagesText != NULL){
        sceneDeJeu->removeItem(stagesText);
        delete stagesText;
        stagesText = NULL;
    }
    if(serp2) serp2->deleteLater();
    serp2 = serp;
}


void Jeu::creerObs(int NumObs)
{
    if(obs != NULL){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
    }
    if(NumObs != 0 && obs == NULL){
    obs = new Obstacles(NumObs);
    sceneDeJeu->addItem(obs);
    background->setPixmap(QPixmap(obs->bg).scaled(1200,600));
    background->setZValue(0);
    sceneDeJeu->addItem(background);
    }
    debut();
}

void Jeu::afficherStages()
{
    if(titreText != NULL){
        sceneDeJeu->removeItem(titreText);
        delete titreText;
        titreText =NULL;
    }

    stagesText = new QGraphicsTextItem("Stages");
    QFont titreFont("roboto", 50 );
    stagesText->setFont(titreFont);
    int xPos = width()/2 - stagesText->boundingRect().width()/2;
    int yPos = 100;
    stagesText->setPos(xPos, yPos);
    stagesText->setDefaultTextColor(Qt::white);
    sceneDeJeu->addItem(stagesText);

    Button* stage = creerStg("1", 50, 50, -50,100, 1, true, stagesText);


    Button* stage2 = creerStg("2", 50, 50, 25,100, 2, true, stagesText);
    Button* stage3 = creerStg("3", 50, 50, 100,100, 3, true, stagesText);
    Button* stage4 = creerStg("4", 50, 50, 175,100, 4, true, stagesText);
    Button* stage5 = creerStg("5", 50, 50, 250,100, 5, true, stagesText);

    Button* retour = new Button("<< RETOUR", 100, 50, stagesText);
    int rx = 50;
    int ry = 400;
    retour->setPos(rx,ry);
    connect(retour, SIGNAL(clicked()), this, SLOT(retourAffich()));


    Q_UNUSED(stage);
    Q_UNUSED(stage2);
    Q_UNUSED(stage3);
    Q_UNUSED(stage4);
    Q_UNUSED(stage5);
}

void Jeu::afficherPause()
{
    if(choixText != NULL)
    {
        sceneDeJeu->removeItem(choixText);
        delete choixText;
        choixText = NULL;
    }
    pauseText = new QGraphicsTextItem("PAUSE");
    QFont titreFont("arial", 50 );
    pauseText->setFont(titreFont);
    int xPos = width()/2 - pauseText->boundingRect().width()/2;
    int yPos = 100;
    pauseText->setPos(xPos, yPos);
    sceneDeJeu->addItem(pauseText);
    pauseText->setDefaultTextColor(Qt::white);

    Button* commancer = new Button("COMMANCER", 150, 40, pauseText);
    commancer->setPos(50,140);
    connect(commancer, SIGNAL(clicked()), this, SLOT(commancer()) );

    Button* recommancer = creerStg("Recommancer", 150, 40, 50, 200, 0, true, pauseText);

    Button* retour = new Button("<< RETOUR", 100, 50, pauseText);
    int rx = 80;
    int ry = 400;
    retour->setPos(rx,ry);
    connect(retour, SIGNAL(clicked()), this, SLOT(choix()) );

    Q_UNUSED(recommancer);
    Q_UNUSED(retour);
}

void Jeu::choix()
{
    if(pauseText != NULL)
    {
        sceneDeJeu->removeItem(pauseText);
        delete pauseText;
        pauseText = NULL;
    }
    choixText = new QGraphicsTextItem("WARNING");
    QFont titreFont("arial", 50 );
    choixText->setFont(titreFont);
    int xPos = width()/2 - choixText->boundingRect().width()/2;
    int yPos = 100;
    choixText->setPos(xPos, yPos);
    choixText->setDefaultTextColor(Qt::white);
    sceneDeJeu->addItem(choixText);

    Button* oui = new Button("OUI", 50, 50, choixText);
    int rx = 110;
    int ry = 100;
    oui->setPos(rx,ry);
    connect(oui, SIGNAL(clicked()), this, SLOT(routeurMenu()) );

    Button* non = new Button("NON", 50, 50, choixText);
    int nx = 180;
    int ny = 100;
    non->setPos(nx,ny);
    connect(non, SIGNAL(clicked()), this, SLOT(afficherPause()) );
}

void Jeu::retourAffich()
{
    if(obs != NULL){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
    }
    if(stagesText != NULL){
        sceneDeJeu->removeItem(stagesText);
        delete stagesText;
        stagesText = NULL;
    }
    if(titreText != NULL){
        sceneDeJeu->removeItem(titreText);
        delete titreText;
        titreText = NULL;
    }
    afficherMenu("Jeu Serpent ", "Jouer");

}

void Jeu::commancer()
{
    if(!serp->t->isActive()){
        serp->t->start(90);
        if(titreText != NULL)
        {
            sceneDeJeu->removeItem(titreText);
            delete titreText;
            titreText = NULL;
        }
        if(pauseText != NULL)
        {
            sceneDeJeu->removeItem(pauseText);
            delete pauseText;
            pauseText = NULL;
        }
    }

}

void Jeu::routeurMenu()
{
    sceneDeJeu->removeItem(serp);
    serp =NULL;
    if(choixText != NULL)
    {
        sceneDeJeu->removeItem(choixText);
        delete choixText;
        choixText = NULL;
    }
    if(obs != NULL){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
    }
    if(pauseText != NULL){
        sceneDeJeu->removeItem(pauseText);
        delete pauseText;
        pauseText = NULL;
    }
    afficherMenu("Jeu Serpent ", "Jouer");
}

void Jeu::stageSuiv()
{
    if(obs != NULL){
        sceneDeJeu->removeItem(obs);
        delete obs;
        obs = NULL;
    }
    creerObs(StageCourant);
}
