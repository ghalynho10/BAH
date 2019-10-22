#ifndef AJOUT_H
#define AJOUT_H

#include <QWidget>
#include<QtGui>
#include "projet_banque.h"
#include "seconde_one.h"

class Ajout : public QWidget
{
    Q_OBJECT
public:
    explicit Ajout(QWidget *parent = 0);

private:
    QLineEdit *nom;
    QLineEdit *prenom;
    QDateTimeEdit *dnaissance;
    QComboBox *sexe;
    QLineEdit *telephone;
    QLineEdit *adresse;
    QLineEdit *nif;
    QLineEdit *mail;
    QLineEdit *montant;
    QPushButton *enregistrer;
    QPushButton *quitter;

    //ajout des QLabel
    QLabel *lnom;
    QLabel *lprenom;
    QLabel *lsexe;
    QLabel *naissance;
    QLabel *ltelephone;
    QLabel *ladresse;
    QLabel *lmontant;
    QLabel *lnif;
    QLabel *lmail;
    
signals:
    
public slots:
    void ajout();
    
};

#endif // AJOUT_H
