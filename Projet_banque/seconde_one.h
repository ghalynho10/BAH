#ifndef SECONDE_ONE_H
#define SECONDE_ONE_H

#include <QWidget>
#include<QtGui>
#include "projet_banque.h"

class seconde_one : public QWidget
{
    Q_OBJECT
public:
    explicit seconde_one();

private:

    //Page Transaction
    QLineEdit *recherche;
    QPushButton *brecherche;
    QLineEdit *qnom;
    QLineEdit *qprenom;
    QLineEdit *qcompte;
    QLineEdit *qnif;
    QLineEdit *qmontant;
    QRadioButton *choix;
    QRadioButton *choix1;
    QLineEdit *qmontant2;
    QPushButton *valider;
    QPushButton *exit;

    //QLAbel
    QLabel *lnom1;
    QLabel *lprenom1;
    QLabel *lcompte1;
    QLabel *lnif1;
    QLabel *lmontant1;

    //AJout d'un QTableView
    QTableView *table1;




signals:

public slots:
    void tableLoad();
    void loading1(const QModelIndex &index);
    void transaction1();
    void checking();
    void search();
    bool pajajout();
    bool pajdelete();
    bool pajmodifier();


};

#endif // SECONDE_ONE_H
