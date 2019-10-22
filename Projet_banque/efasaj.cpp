#include "efasaj.h"
#include "ajout.h"
#include <QtGui>
#include <QSqlDatabase>
#include <QObject>
#include <QSqlQuery>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlError>
#include <QSqlDriver>
#include <QDebug>

    //DELETE Class

efasaj::efasaj(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Effacer Client");
    setWindowIcon(QIcon("../icon/bah2.png"));

    //Database connection
    projet_banque ouvert;
    if (!ouvert.ouverture())
        {
            qWarning()<<"Echec de la connexion avec la base de donnees";
        }
    else
        {
            qWarning()<<"Connexion avec la base de donnees reussie";
        }

    //Creation the entry point of the informations
    enom = new QLineEdit;
    enom->setReadOnly(true);
    enom->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    eprenom = new QLineEdit;
    eprenom->setReadOnly(true);
    eprenom->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    ednaissance = new QLineEdit;
    ednaissance->setReadOnly(true);
    ednaissance->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    esexe = new QLineEdit;
    esexe->setReadOnly(true);
    esexe->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    etelephone = new QLineEdit;
    etelephone->setReadOnly(true);
    etelephone->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    eadresse = new QLineEdit;
    eadresse->setReadOnly(true);
    eadresse->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    enif = new QLineEdit;
    enif->setReadOnly(true);
    enif->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    email = new QLineEdit;
    email->setReadOnly(true);
    email->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    erecherche = new QLineEdit;
    erecherche->setValidator(new QIntValidator(erecherche));
    erecherche->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    erecherche->setFixedSize(180,23);
    ebrecherche = new QPushButton("Recherche");
    ebrecherche->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;text-align:center; background-color: #2e409a; border: 1.9px solid #25326c;border-radius: 5px;padding: 3px 3px;color:white;");
    ebrecherche->setCursor(Qt::PointingHandCursor);
    eeffacer = new QPushButton("Effacer Compte");
    eeffacer->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;text-align:center; background-color: #2e409a; border: 1.9px solid #25326c;border-radius: 5px;padding: 3px 3px;color:white;");
    eeffacer->setCursor(Qt::PointingHandCursor);
    eannuler = new QPushButton("Fermer");
    eannuler->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;text-align:center; background-color: #2e409a; border: 1.9px solid #25326c;border-radius: 5px;padding: 3px 3px;color:white;");
    eannuler->setCursor(Qt::PointingHandCursor);

    //QLAbel
    elnom = new QLabel("Nom");
    elnom->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    elprenom =new QLabel("Prenom");
    elprenom->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    elsexe = new QLabel("Sexe");
    elsexe->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    enaissance =new QLabel("Date de Naissance");
    enaissance->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    eltelephone =new QLabel("Telephone");
    etelephone->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    eladresse =new QLabel("Adresse");
    eladresse->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    elnif =new QLabel("NIF");
    elnif->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    elmail =new QLabel("Mail");
    elmail->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");

    QGridLayout *item =new QGridLayout;
    item->addWidget(ebrecherche,0,0);
    item->addWidget(erecherche,0,1);
    item->addWidget(elnom,1,0);
    item->addWidget(enom,1,1);
    item->addWidget(elprenom,2,0);
    item->addWidget(eprenom,2,1);
    item->addWidget(elsexe,3,0);
    item->addWidget(esexe,3,1);
    item->addWidget(enaissance,4,0);
    item->addWidget(ednaissance,4,1);
    item->addWidget(eltelephone,5,0);
    item->addWidget(etelephone,5,1);
    item->addWidget(eladresse,6,0);
    item->addWidget(eadresse,6,1);
    item->addWidget(elnif,7,0);
    item->addWidget(enif,7,1);
    item->addWidget(elmail,8,0);
    item->addWidget(email,8,1);

    QHBoxLayout *bsave = new QHBoxLayout;
    bsave->addWidget(eeffacer);
    bsave->addWidget(eannuler);

    QVBoxLayout *er = new QVBoxLayout;
    er->addLayout(item);
    er->addLayout(bsave);
    setLayout(er);

    //Setting the action on the buttons for search, save, delete and quit
    connect(ebrecherche,SIGNAL(clicked()),this,SLOT(recherche()));
    connect(erecherche,SIGNAL(returnPressed()),this,SLOT(recherche()));
    connect(eeffacer,SIGNAL(clicked()),this,SLOT(kill()));
    connect(eannuler,SIGNAL(clicked()),this,SLOT(close()));
}

    //Creation of a search function by ID
void efasaj::recherche()
{
    bool ok;
    projet_banque ouvert;
    int cheche = erecherche->text().toInt(&ok,10);
    if ((QString::number(cheche)).isEmpty())
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Veuillez entrer le code"));
    }
    else
    {
        ouvert.ouverture();
        QSqlQuery *qry = new QSqlQuery(ouvert.mydb);
        qry->prepare("SELECT * from information WHERE ID='"+QString::number(cheche)+"'");
        if(qry->exec())
        {
            while(qry->next())
            {
                enom->setText(qry->value(1).toString());
                eprenom->setText(qry->value(2).toString());
                ednaissance->setText(qry->value(3).toString());
                esexe->setText(qry->value(4).toString());
                etelephone->setText(qry->value(5).toString());
                eadresse->setText(qry->value(6).toString());
                enif->setText(qry->value(7).toString());
                email->setText(qry->value(8).toString());
            }
            if (!qry->first())
            {
                QMessageBox::critical(this,tr("Erreur de recherche"),tr("Compte inexistant"));
                enom->clear();
                eprenom->clear();
                ednaissance->clear();
                esexe->clear();
                etelephone->clear();
                eadresse->clear();
                enif->clear();
                email->clear();
            }

        }
        else
        {
            qWarning()<<"Erreur de recherche"<<qry->lastError().text();
        }
        ouvert.fermeture();
    }

}

//Creation of a delete function
void efasaj::kill()
{
    bool ok;
    int identite = erecherche->text().toInt(&ok,10);
    projet_banque ouvert;
    ouvert.ouverture();

    QSqlQuery *qry = new QSqlQuery;
    qry->prepare("DELETE from information WHERE ID='"+QString::number(identite)+"'");
    if(qry->exec())
    {
        QMessageBox::information(this,tr("Information"),tr("Compte Supprimee"));
        enom->clear();
        eprenom->clear();
        ednaissance->clear();
        esexe->clear();
        etelephone->clear();
        eadresse->clear();
        enif->clear();
        email->clear();

    }
    else
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Compte non supprimee"));
        qWarning()<<"Erreur de suppression"<<qry->lastError().text();

    }
}
