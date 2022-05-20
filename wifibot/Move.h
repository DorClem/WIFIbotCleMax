/*
#ifndef MOVE_H
#define MOVE_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>

class Move : public QWidget
{
    Q_OBJECT
public:
    explicit Move(QWidget *parent = nullptr);

private:
    QPushButton *bHaut;
    QPushButton *bGauche;
    QPushButton *bDroit;
    QPushButton *bBas;
    QPushButton *bArret;

    QSlider *sliderDroit;
    QSlider *sliderGauche;

    void setButton(QPushButton *bouton, QRect Geometry, QString chemin);

private slots:
    void sMoveHaut();
    void sMoveBas();
    void sMoveDroite();
    void sMoveGauche();
    void sMoveArret();

    void sDroiteSlider(const int data);
    void sGaucheSlider(const int data);

signals:
    void updateMove(const unsigned char data, const unsigned char vitesseDroite, const unsigned char vitesseGauche);
    void updateVitesseDroite(const unsigned char data);
    void updateVitesseGauche(const unsigned char data);

};

#endif // MOVE_H
*/
