#ifndef MODIFICATION_H
#define MODIFICATION_H

#include <QWidget>
#include <QWidget>
#include<QtGui>
#include "projet_banque.h"
#include "seconde_one.h"
#include "ajout.h"
#include "projet_banque.h"
#include "efasaj.h"

class modification : public QWidget
{
    Q_OBJECT
public:
    explicit modification(QWidget *parent = 0);

private:
    QLineEdit *mnom;
    QLineEdit *mprenom;
    QDateTimeEdit *mdnaissance;
    QComboBox *msexe;
    QLineEdit *mtelephone;
    QLineEdit *madresse;
    QLineEdit *mnif;
    QLineEdit *mmail;
    QLineEdit *mcompte;
    QLineEdit *mrecherche;
    QPushButton *mbrecherche;
    QPushButton *menregistrer;
    QPushButton *mquitter;

    //ajout des QLabel
    QLabel *mlnom;
    QLabel *mlprenom;
    QLabel *mlsexe;
    QLabel *mnaissance;
    QLabel *mltelephone;
    QLabel *mladresse;
    QLabel *mlnif;
    QLabel *mlmail;
    QLabel *mlcompte;

signals:
    
public slots:
    void rech();
    void modifier();

};

#endif // MODIFICATION_H
