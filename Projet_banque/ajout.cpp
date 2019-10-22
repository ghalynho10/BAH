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

    //ADD NEW CLIENT CLASS

Ajout::Ajout(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Ajouter Client");
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

    QRegExp re("^[A-Za-z- ]*$");
    QRegExp rev("^[A-Za-z-@-.-_]*$");

    //Creation the entry point of the informations
    nom = new QLineEdit;
    nom->setValidator(new QRegExpValidator(re,0));
    nom->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    prenom = new QLineEdit;
    prenom->setValidator(new QRegExpValidator(re,0));
    prenom->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    dnaissance = new QDateTimeEdit;
    dnaissance->setDisplayFormat("d-MMMM-yyyy");
    dnaissance->setMinimumDate(QDate::currentDate().addYears(-100));
    dnaissance->setMaximumDate(QDate::currentDate().addYears(-18));
    dnaissance->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    sexe = new QComboBox;
    sexe->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    telephone = new QLineEdit;
    telephone->setValidator(new QIntValidator(telephone));
    telephone->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    montant = new QLineEdit;
    montant->setValidator(new QIntValidator(montant));
    montant->setPlaceholderText("Montant >500gdes");
    montant->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    adresse = new QLineEdit;
    adresse->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    nif = new QLineEdit;
    nif->setValidator(new QIntValidator(nif));
    nif->setMaxLength(17);
    nif->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    mail = new QLineEdit;
    mail->setValidator(new QRegExpValidator(rev,0));
    mail->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    enregistrer = new QPushButton("Enregistrer");
    enregistrer->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;text-align:center; background-color: #2e409a; border: 1.9px solid #25326c;border-radius: 5px;padding: 3px 3px;color:white;");
    enregistrer->setCursor(Qt::PointingHandCursor);
    quitter = new QPushButton("Quitter");
    quitter->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;text-align:center; background-color: #2e409a; border: 1.9px solid #25326c;border-radius: 5px;padding: 3px 3px;color:white;");
    quitter->setCursor(Qt::PointingHandCursor);


    //QLAbel
    lnom = new QLabel("Nom");
    lnom->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    lprenom =new QLabel("Prenom");
    lprenom->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    lsexe = new QLabel("Sexe");
    lsexe->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    naissance =new QLabel("Date de Naissance");
    naissance->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    ltelephone =new QLabel("Telephone");
    ltelephone->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    ladresse =new QLabel("Adresse");
    ladresse->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    lnif =new QLabel("NIF");
    lnif->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    lmail =new QLabel("Mail");
    lmail->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    lmontant = new QLabel("Montant");
    lmontant->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");


    //Sexe
    sexe->addItem("M");
    sexe->addItem("F");


    //Creation of a Grid
    QGridLayout *item =new QGridLayout;
    item->addWidget(lnom,0,0);
    item->addWidget(nom,0,1);
    item->addWidget(lprenom,1,0);
    item->addWidget(prenom,1,1);
    item->addWidget(lsexe,2,0);
    item->addWidget(sexe,2,1);
    item->addWidget(naissance,3,0);
    item->addWidget(dnaissance,3,1);
    item->addWidget(ltelephone,4,0);
    item->addWidget(telephone,4,1);
    item->addWidget(ladresse,5,0);
    item->addWidget(adresse,5,1);
    item->addWidget(lnif,6,0);
    item->addWidget(nif,6,1);
    item->addWidget(lmail,7,0);
    item->addWidget(mail,7,1);
    item->addWidget(lmontant,8,0);
    item->addWidget(montant,8,1);



    QHBoxLayout *bsave = new QHBoxLayout;
    bsave->addWidget(enregistrer);
    bsave->addWidget(quitter);

    QVBoxLayout *er = new QVBoxLayout;
    er->addLayout(item);
    er->addLayout(bsave);
    setLayout(er);

    //Setting the action on the buttons for save and quit
    connect(enregistrer,SIGNAL(clicked()),this,SLOT(ajout()));
    connect(quitter,SIGNAL(clicked()),this,SLOT(close()));
}

    //Setting a function to save the datas t the database
void Ajout::ajout()
{
    projet_banque ouvert;
    bool ok;
    QString Nom, Prenom, date1, Sexe, Telephone, Adresse, NIF,Mail;
    int Montant;
    Nom = nom->text();
    Prenom = prenom->text();
    date1 = dnaissance->date().toString("d-MMMM-yyyy");
    Sexe = sexe->currentText();
    Telephone = telephone->text();
    Adresse = adresse->text();
    NIF = nif->text();
    Mail = mail->text();
    Montant = montant->text().toInt(&ok,10);

    //check if the database is functioning
    if (!ouvert.ouverture())
        {
            qDebug()<<"Echec de la connexion";
        }
    ouvert.ouverture();
    if ((Nom.isEmpty()||Prenom.isEmpty()||Sexe.isEmpty()||Telephone.isEmpty()||Adresse.isEmpty()||Mail.isEmpty()||NIF.isEmpty()||QString::number(Montant).isEmpty()))
    {
        QMessageBox::information(this,tr("SAUVEGARDE"),tr("Aucun champ ne doit etre vide"));
    }
    else if(Montant<500)
    {
        QMessageBox::critical(this,tr("Erreur d'enregistrement"),tr("Le montant doit etre superieur a 500"));
    }
    else
    {
        QSqlQuery qry;
        qry.prepare("insert into information (Nom,Prenom, Anniversaire,Sexe,Telephone,Adresse,NIF,Mail,Montant)"
                    "values ('"+Nom+"','"+Prenom+"','"+date1+"','"+Sexe+"','"+Telephone+"',"
                    "'"+Adresse+"','"+NIF+"','"+Mail+"','"+QString::number(Montant)+"')");

        //Cleaning the entry point of the informations
        if (qry.exec())
        {
            QMessageBox::information(this,tr("SAUVEGARDE"),tr("Sauvegarde"));
            nom->clear();
            prenom->clear();
            dnaissance->clear();
            sexe->clear();
            telephone->clear();
            adresse->clear();
            nif->clear();
            mail->clear();
            montant->clear();
            ouvert.fermeture();
        }
        else
        {
            QMessageBox::critical(this,tr("Erreur"),tr("Erreur de sauvegarde"));
        }
     }
}
