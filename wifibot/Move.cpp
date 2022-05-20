/*
#include "Move.h"
#include "QtCore/qdebug.h"

Move::Move(QWidget *parent) : QWidget{parent}
{
    //. Taille du widget
    this->setFixedSize(200,200);

    // boutons de commande du robot
    bHaut = new QPushButton(this);
    setButton(bHaut, QRect(61,0,41,41),"haut");

    bGauche = new QPushButton(this);
    setButton(bGauche, QRect(20,41,41,41), "gauche");

    bDroit = new QPushButton(this);
    setButton(bDroit, QRect(102,41,41,41), "droite");

    bBas = new QPushButton(this);
    setButton(bBas, QRect(61,82,41,41), "arriere");

    bArret = new QPushButton(this);
    setButton(bArret, QRect(61,41,41,41), "");

    // Création de 2 sliders de gestion de vitesse (Valeur entre 0 et 240, voir la doc)
    sliderGauche = new QSlider(this);
    sliderGauche->setMinimum(0);
    sliderGauche->setMaximum(240);
    sliderGauche->setGeometry(0,0,20,120);

    sliderDroit = new QSlider(this);
    sliderDroit->setMinimum(0);
    sliderDroit->setMaximum(240);
    sliderDroit->setGeometry(143,0,20,120);

    // Definition des connexions entre les signaux des boutons et les slots
    connect(bHaut, SIGNAL(pressed()), this, SLOT(sMoveHaut()));
    connect(bGauche, SIGNAL(pressed()), this, SLOT(sMoveGauche()));
    connect(bDroit, SIGNAL(pressed()), this, SLOT(sMoveDroite()));
    connect(bBas, SIGNAL(pressed()), this, SLOT(sMoveBas()));
    connect(bArret, SIGNAL(pressed()), this, SLOT(sMoveArret()));

    connect(sliderDroit, SIGNAL(valueChanged(int)), this, SLOT(sDroiteSlider(int)));
    connect(sliderGauche, SIGNAL(valueChanged(int)), this, SLOT(sGaucheSlider(int)));
}

// Methode inutile, ajoute un icone au bouton et place celui-ci au sein du widget
void Move::setButton(QPushButton *bouton, QRect Geometry, QString texte){
    //bouton->setIcon(QIcon(chemin));
    bouton->setText(texte);
    bouton->setGeometry(Geometry);
}


void Move::sMoveHaut()  // aller en haut
{
    // Emission d'un signal de modification de direction
    emit updateMove(0, sliderDroit->value(), sliderGauche->value());
}

void Move::sMoveBas()    // aller en bas
{
    // Emission d'un signal de modification de direction
    emit updateMove(3, sliderDroit->value(), sliderGauche->value());
}

void Move::sMoveGauche()
{
    // Emission d'un signal de modification de direction
    emit updateMove(1, sliderDroit->value(), sliderGauche->value());
}

void Move::sMoveDroite()
{
    // Emission d'un signal de modification de direction
    emit updateMove(2, sliderDroit->value(), sliderGauche->value());
}

void Move::sMoveArret()
{
    // Emission d'un signal de modification de direction
    emit updateMove(4, sliderDroit->value(), sliderGauche->value());
}

void Move::sDroiteSlider(const int data)
{
    // Emission d'un signal de modification de la vitesse coté. gauche
    emit updateVitesseDroite((unsigned char)data);
}

void Move::sGaucheSlider(const int data)
{
    // Emission d'un signal de modification de la vitesse coté droit
    emit updateVitesseGauche((unsigned char)data);
}

*/
