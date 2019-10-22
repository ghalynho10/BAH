#ifndef EFASAJ_H
#define EFASAJ_H

#include <QWidget>
#include<QtGui>
#include "projet_banque.h"
#include "seconde_one.h"
#include "ajout.h"
#include "projet_banque.h"

class efasaj : public QWidget
{
    Q_OBJECT
public:
    explicit efasaj(QWidget *parent = 0);
    
private:
    QLineEdit *enom;
    QLineEdit *eprenom;
    QLineEdit *ednaissance;
    QLineEdit *esexe;
    QLineEdit *etelephone;
    QLineEdit *eadresse;
    QLineEdit *enif;
    QLineEdit *email;
    QLineEdit *erecherche;
    QPushButton *ebrecherche;
    QPushButton *eeffacer;
    QPushButton *eannuler;

    //ajout des QLabel
    QLabel *elnom;
    QLabel *elprenom;
    QLabel *elsexe;
    QLabel *enaissance;
    QLabel *eltelephone;
    QLabel *eladresse;
    QLabel *elnif;
    QLabel *elmail;
signals:
    
public slots:
    void recherche();
    void kill();
    
};

#endif // EFASAJ_H
