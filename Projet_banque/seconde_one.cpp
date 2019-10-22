#include "seconde_one.h"
#include <ajout.h>
#include <QtGui>
#include <QSqlDatabase>
#include <QObject>
#include <QSqlQuery>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlError>
#include <QSqlDriver>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <efasaj.h>
#include <modification.h>
seconde_one::seconde_one() :QWidget()
{

//Page transaction

    setWindowTitle("Transaction");
    setWindowIcon(QIcon("../icon/bah2.png"));


    //ajout d'une base de donnees
    projet_banque ouvert;
    if (!ouvert.ouverture())
        {
            qWarning()<<"Echec de la connexion avec la base de donnees";
        }
    else
        {
            qWarning()<<"Connexion avec la base de donnees reussie";
        }




    QRegExp re("^[A-Za-z- ]*$");
    QRegExp rev("^[A-Za-z-@-.-_]*$");

     recherche = new QLineEdit;
     recherche->setValidator(new QIntValidator(recherche));
     recherche->setMaxLength(5);
     recherche->setFixedWidth(200);
     brecherche = new QPushButton("Rechercher");
     brecherche->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;text-align:center; background-color: #2e409a; border: 1.9px solid #25326c;border-radius: 5px;padding: 3px 3px;color:white;");
     brecherche->setCursor(Qt::PointingHandCursor);
     qnom = new QLineEdit;
     qnom->setValidator(new QRegExpValidator(re,0));
     qnom->setReadOnly(true);
     qnom->setFixedWidth(200);
     qprenom = new QLineEdit;
     qprenom->setValidator(new QRegExpValidator(re,0));
     qprenom->setReadOnly(true);
     qprenom->setFixedWidth(200);
     qcompte = new QLineEdit;
     qcompte->setReadOnly(true);
     qcompte->setFixedWidth(200);
     qnif = new QLineEdit;
     qnif->setValidator(new QIntValidator(qnif));
     qnif->setReadOnly(true);
     qnif->setFixedWidth(200);
     qmontant = new QLineEdit;
     qmontant->setValidator(new QIntValidator(qmontant));
     qmontant->setReadOnly(true);
     qmontant->setFixedWidth(200);
     choix = new QRadioButton("Depot");
     choix->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:15px;");
     choix1 = new QRadioButton("Retrait");
     choix1->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:15px;");
     qmontant2 = new QLineEdit;
     qmontant2->setValidator(new QIntValidator(qmontant2));
     qmontant2->setFixedWidth(200);
     valider = new QPushButton("Valider");
     valider->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:15px;text-align:center; background-color: #2e409a; border: 1.9px solid #25326c;border-radius: 5px;padding: 3px 3px;color:white;");
     valider->setCursor(Qt::PointingHandCursor);
     valider->setFixedWidth(150);
     exit = new QPushButton("Exit");
     exit->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:15px;text-align:center; background-color: #2e409a; border: 1.9px solid #25326c;border-radius: 5px;padding: 3px 3px;color:white;");
     exit->setCursor(Qt::PointingHandCursor);
     exit->setFixedWidth(150);

     lnom1 = new QLabel("Nom");
     lnom1->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:15px;");
     lprenom1 = new QLabel("Prenom");
     lprenom1->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:15px;");
     lcompte1 = new QLabel("No. Compte");
     lcompte1->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:15px;");
     lnif1 = new QLabel("NIF");
     lnif1->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:15px;");
     lmontant1 = new QLabel("Montant Actif");
     lmontant1->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:15px;");

     QHBoxLayout *radio= new QHBoxLayout;
     radio->addWidget(choix);
     radio->addWidget(choix1);

     QGridLayout *gridfinal= new QGridLayout;
     gridfinal->addWidget(brecherche,0,0);
     gridfinal->addWidget(recherche,0,1);
     gridfinal->addWidget(lnom1,1,0);
     gridfinal->addWidget(qnom,1,1);
     gridfinal->addWidget(lprenom1,2,0);
     gridfinal->addWidget(qprenom,2,1);
     gridfinal->addWidget(lcompte1,3,0);
     gridfinal->addWidget(qcompte,3,1);
     gridfinal->addWidget(lnif1,4,0);
     gridfinal->addWidget(qnif,4,1);
     gridfinal->addWidget(lmontant1,5,0);
     gridfinal->addWidget(qmontant,5,1);
     gridfinal->addLayout(radio,6,0);
     gridfinal->addWidget(qmontant2,6,1);

     //Creation d'un QTableView
     table1 = new QTableView;
     table1->setFixedWidth(700);

     QHBoxLayout *finalite = new QHBoxLayout;
     finalite->addLayout(gridfinal);
     finalite->addWidget(table1);

     //QHBoxLayout pou bouton anba
     QHBoxLayout *bouton001 = new QHBoxLayout;
     bouton001->addWidget(valider);
     bouton001->addWidget(exit);


     QAction *efasaj = new QAction("&Effacer compte",this);
     QAction *modifier = new QAction("&Modifier Info",this);
     efasaj->setShortcut(QKeySequence("Ctrl+D"));
     efasaj->setIcon(QIcon("../icon/remove1.png"));
     modifier->setShortcut(QKeySequence("Ctrl+M"));
     modifier->setIcon(QIcon("../icon/edit1.png"));

     QAction *refresh = new QAction("&Actualiser",this);
     refresh->setShortcut(QKeySequence("Ctrl+R"));
     refresh->setIcon(QIcon("../icon/refresh1.png"));

     QToolBar *toolbar = new QToolBar;
     toolbar->setStyleSheet ("spacing:35px; background-color: white;");
     QAction *tooly = new QAction("&Ajouter Client",this);
     tooly->setIcon(QIcon("../icon/icon4"));
     toolbar->addAction(tooly);
     toolbar->addAction(efasaj);
     toolbar->addAction(modifier);
     toolbar->addAction(refresh);
     tooly->setShortcut(QKeySequence("Ctrl+A"));


     QVBoxLayout *layout02 = new QVBoxLayout;
     layout02->addWidget(toolbar);
     layout02->addLayout(finalite);
     layout02->addLayout(bouton001);
     setLayout(layout02);



     connect(exit,SIGNAL(clicked()),this,SLOT(close()));
     connect(choix,SIGNAL(clicked()),this,SLOT(checking()));
     connect(choix1,SIGNAL(clicked()),this,SLOT(checking()));
     connect(table1,SIGNAL(clicked(const QModelIndex &)),this,SLOT(loading1(const QModelIndex &)));
     connect(valider,SIGNAL(clicked()),this,SLOT(transaction1()));
     connect(brecherche,SIGNAL(clicked()),this,SLOT(search()));
     connect(recherche,SIGNAL(returnPressed()),this,SLOT(search()));
     connect(tooly,SIGNAL(triggered()),this,SLOT(pajajout()));
     connect(efasaj,SIGNAL(triggered()),this,SLOT(pajdelete()));
     connect(modifier,SIGNAL(triggered()),this,SLOT(pajmodifier()));
     connect(refresh,SIGNAL(triggered()),this,SLOT(tableLoad()));
}



void seconde_one::tableLoad()
{
    projet_banque ouvert;
    QSqlQueryModel *model = new QSqlQueryModel();
    ouvert.ouverture();
    QSqlQuery *qry = new QSqlQuery(ouvert.mydb);
    qry->prepare("select * from information");
    qry->exec();
    model->setQuery(*qry);
    table1->setModel(model);

    ouvert.fermeture();
    qDebug()<<(model->rowCount());
}

void seconde_one::checking()
{
    qmontant2->setPlaceholderText("Montant>500gdes");
}

void seconde_one::loading1(const QModelIndex &index)
{
    projet_banque ouvert;
    QString valeurpam = table1->model()->data(index).toString();
    if (!ouvert.ouverture())
    {
        qDebug()<<"Echec de la connexion d'ouverture";
    }
    ouvert.ouverture();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM information WHERE  Nom='"+valeurpam+"' ");
    if (qry.exec())
    {
        while(qry.next())
        {
            qnom->setText(qry.value(1).toString());
            qprenom->setText(qry.value(2).toString());
            qcompte->setText(qry.value(0).toString());
            qnif->setText(qry.value(7).toString());
            qmontant->setText(qry.value(9).toString());
        }
    }
    else
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Erreur"));
    }
    ouvert.fermeture();
}

void seconde_one::search()
{
    bool ok;
    projet_banque ouvert;
    int cheche = recherche->text().toInt(&ok,10);
    QSqlQueryModel *model = new QSqlQueryModel();
    ouvert.ouverture();
    QSqlQuery *qry = new QSqlQuery(ouvert.mydb);
    qry->prepare("SELECT * from information WHERE ID='"+QString::number(cheche)+"'");
    if(qry->exec())
    {
        if (!qry->first())
        {
            QMessageBox::critical(this,tr("Erreur de recherche"),tr("Compte inexistant"));
        }
        else
        {
            model->setQuery(*qry);
            table1->setModel(model);
        }
    }
    else
    {
        qWarning()<<"Erreur de recherche"<<qry->lastError().text();
    }
    ouvert.fermeture();

}


void seconde_one::transaction1()
{
    bool ok;
    int amontant = qmontant2->text().toInt(&ok,10);
    int valeur = qmontant->text().toInt(&ok,10);
    int valorisation = qcompte->text().toInt(&ok,10);
    int valeur2 = valeur - amontant;
    if (choix1->isChecked())
    {
        projet_banque ouvert;
        ouvert.ouverture();
        qmontant2->setPlaceholderText("Montant superieur a 500gdes");

        if (valeur<amontant)
        {
            QMessageBox::critical(this,tr("Erreur de transaction"),tr("Le montant doit etre inferieur a la balance"));
        }
        else if(valeur<500)
        {
            QMessageBox::critical(this,tr("Erreur de transaction"),tr("Le montant doit etre superieur a 500"));
        }
        else
        {
            QSqlQuery *qry = new QSqlQuery(ouvert.mydb);
            qry->prepare("UPDATE information SET Montant= :Montant WHERE ID=:ID");
            qry->bindValue(":Montant", valeur2);
            qry->bindValue(":ID", valorisation);

            if(qry->exec())
            {
                QMessageBox::information(this,tr("Reussite"),tr("Transaction Reussie"));
                qnom->clear();
                qprenom->clear();
                qcompte->clear();
                qnif->clear();
                qmontant->clear();
                qmontant2->clear();
                qWarning()<<"Transaction reussie";
            }
            else
            {
              QMessageBox::critical(this,tr("Erreur"),tr("Erreur de transaction"));
              qWarning()<<"Echec de la merde"<<qry->lastError().text();
            }
        }

        ouvert.fermeture();
    }

    if (choix->isChecked())
    {
        projet_banque ouvert;
        ouvert.ouverture();

        if (amontant<500)
        {
            QMessageBox::critical(this,tr("Erreur de transaction"),tr("Le montant doit etre superieur a 500gdes"));
        }
        else
        {
            QSqlQuery *qry = new QSqlQuery(ouvert.mydb);

            int valeur3 = amontant + valeur;
            qry->prepare("update information set Montant= :Montant WHERE ID=:ID");
            qry->bindValue(":Montant", valeur3);
            qry->bindValue(":ID",valorisation);

            if(qry->exec())
            {
                QMessageBox::information(this,tr("Reussite"),tr("Transaction Reussie"));
                qnom->clear();
                qprenom->clear();
                qcompte->clear();
                qnif->clear();
                qmontant->clear();
                qmontant2->clear();
                qWarning()<<"Transaction reussie";
            }
            else
            {
              QMessageBox::critical(this,tr("Erreur"),tr("Erreur de transaction"));
              qWarning()<<"Echec de la merde"<<qry->lastError().text();
            }
        }

        ouvert.fermeture();
    }
}

bool seconde_one::pajajout()
{
    Ajout *fenetre = new Ajout;
    fenetre->setFixedSize(300,300);
    fenetre->show();
    return 1;
}

bool seconde_one::pajdelete()
{
    efasaj *fenetre = new efasaj;
    fenetre->setFixedSize(300,300);
    fenetre->show();
    return 1;
}
bool seconde_one::pajmodifier()
{
    modification *fenetre = new modification;
    fenetre->setFixedSize(300,300);
    fenetre->show();
    return 1;
}
