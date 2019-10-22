#include "modification.h"
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

    //EDIT CLIENT CLASS

modification::modification(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Modifier Information");
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
    mnom = new QLineEdit;
    mnom->setValidator(new QRegExpValidator(re,0));
    mnom->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    mprenom = new QLineEdit;
    mprenom->setValidator(new QRegExpValidator(re,0));
    mprenom->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    mdnaissance = new QDateTimeEdit;
    mdnaissance->setDisplayFormat("d-MMMM-yyyy");
    mdnaissance->setMinimumDate(QDate::currentDate().addYears(-100));
    mdnaissance->setMaximumDate(QDate::currentDate().addYears(-18));
    mdnaissance->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    msexe = new QComboBox;
    msexe->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    mtelephone = new QLineEdit;
    mtelephone->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    mtelephone->setValidator(new QIntValidator(mtelephone));
    madresse = new QLineEdit;
    madresse->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    mnif = new QLineEdit;
    mnif->setValidator(new QIntValidator(mnif));
    mnif->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    mmail = new QLineEdit;
    mmail->setValidator(new QRegExpValidator(rev,0));
    mmail->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    mcompte = new QLineEdit;
    mcompte->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    mrecherche = new QLineEdit;
    mrecherche->setValidator(new QIntValidator(mrecherche));
    mrecherche->setStyleSheet("border: 1.2px solid #25326c;border-radius: 3px;");
    mrecherche->setFixedSize(180,23);
    mbrecherche = new QPushButton("Recherche");
    mbrecherche->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;text-align:center; background-color: #2e409a; border: 1.9px solid #25326c;border-radius: 5px;padding: 3px 3px;color:white;");
    mbrecherche->setCursor(Qt::PointingHandCursor);
    menregistrer = new QPushButton("Enregistrer");
    menregistrer->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;text-align:center; background-color: #2e409a; border: 1.9px solid #25326c;border-radius: 5px;padding: 3px 3px;color:white;");
    menregistrer->setCursor(Qt::PointingHandCursor);
    mquitter = new QPushButton("Quitter");
    mquitter->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;text-align:center; background-color: #2e409a; border: 1.9px solid #25326c;border-radius: 5px;padding: 3px 3px;color:white;");
    mquitter->setCursor(Qt::PointingHandCursor);

    //QLAbel
    mlnom = new QLabel("Nom");
    mlnom->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    mlprenom =new QLabel("Prenom");
    mlprenom->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    mlsexe = new QLabel("Sexe");
    mlsexe->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    mnaissance =new QLabel("Date de Naissance");
    mnaissance->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    mltelephone =new QLabel("Telephone");
    mltelephone->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    mladresse =new QLabel("Adresse");
    mladresse->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    mlnif =new QLabel("NIF");
    mlnif->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    mlmail =new QLabel("Mail");
    mlmail->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");
    mlcompte = new QLabel("No. Compte");
    mlcompte->setStyleSheet("font-family:'Franklin Gothic Medium';font-size:12px;");

    //Sexe
    msexe->addItem("M");
    msexe->addItem("F");


    //Creation d'un Grid
    QGridLayout *item =new QGridLayout;
    item->addWidget(mbrecherche,0,0);
    item->addWidget(mrecherche,0,1);
    item->addWidget(mlnom,1,0);
    item->addWidget(mnom,1,1);
    item->addWidget(mlprenom,2,0);
    item->addWidget(mprenom,2,1);
    item->addWidget(mlsexe,3,0);
    item->addWidget(msexe,3,1);
    item->addWidget(mlcompte,4,0);
    item->addWidget(mcompte,4,1);
    item->addWidget(mnaissance,5,0);
    item->addWidget(mdnaissance,5,1);
    item->addWidget(mltelephone,6,0);
    item->addWidget(mtelephone,6,1);
    item->addWidget(mladresse,7,0);
    item->addWidget(madresse,7,1);
    item->addWidget(mlnif,8,0);
    item->addWidget(mnif,8,1);
    item->addWidget(mlmail,9,0);
    item->addWidget(mmail,9,1);

    QHBoxLayout *bsave = new QHBoxLayout;
    bsave->addWidget(menregistrer);
    bsave->addWidget(mquitter);

    QVBoxLayout *er = new QVBoxLayout;
    er->addLayout(item);
    er->addLayout(bsave);
    setLayout(er);

    //Setting the action on the buttons for search, save and quit
    connect(mbrecherche,SIGNAL(clicked()),this,SLOT(rech()));
    connect(mrecherche,SIGNAL(returnPressed()),this,SLOT(rech()));
    connect(menregistrer,SIGNAL(clicked()),this,SLOT(modifier()));
    connect(mquitter,SIGNAL(clicked()),this,SLOT(close()));
}
void modification::rech()
{
    bool ok;
    projet_banque ouvert;
    int cheche = mrecherche->text().toInt(&ok,10);
    //QSqlQueryModel *model = new QSqlQueryModel();
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
                mnom->setText(qry->value(1).toString());
                mprenom->setText(qry->value(2).toString());
                mcompte->setText(qry->value(0).toString());
                QString rema= (qry->value(3).toString());
                QDate remake = QDate::fromString(rema,"d-MMMM-yyyy");
                mdnaissance->setDate(remake);
                mtelephone->setText(qry->value(5).toString());
                madresse->setText(qry->value(6).toString());
                mnif->setText(qry->value(7).toString());
                mmail->setText(qry->value(8).toString());
            }

            if (!qry->first())
            {
                QMessageBox::critical(this,tr("Erreur de recherche"),tr("Compte inexistant"));
                mnom->clear();
                mprenom->clear();
                mcompte->clear();
                mdnaissance->clear();
                mtelephone->clear();
                madresse->clear();
                mnif->clear();
                mmail->clear();
            }
        }
        else
        {
            qWarning()<<"Erreur de recherche"<<qry->lastError().text();
        }
        ouvert.fermeture();
    }
}

void modification::modifier()
{
    bool ok;
    int identite = mcompte->text().toInt(&ok,10);
    QString Nom, Prenom, date1, Sexe, Telephone, Adresse, NIF,Mail;
    Nom = mnom->text();
    Prenom = mprenom->text();
    date1 = mdnaissance->date().toString("d-MMMM-yyyy");
    Sexe = msexe->currentText();
    Telephone = mtelephone->text();
    Adresse = madresse->text();
    NIF = mnif->text();
    Mail = mmail->text();

    projet_banque ouvert;
    ouvert.ouverture();

    QSqlQuery *qry = new QSqlQuery;
    qry->prepare("UPDATE information SET Nom='"+Nom+"',Prenom='"+Prenom+"', Anniversaire='"+date1+"', Sexe='"+Sexe+"', Telephone='"+Telephone+"', Adresse='"+Adresse+"', NIF='"+NIF+"', Mail='"+Mail+"' WHERE ID= '"+QString::number(identite)+"'");
    if (qry->exec())
    {
        QMessageBox::information(this,tr("Reussite"),tr("Modification Reussie"));
        mnom->clear();
        mprenom->clear();
        mcompte->clear();
        mdnaissance->clear();
        mtelephone->clear();
        madresse->clear();
        mnif->clear();
        mmail->clear();
    }
    else
    {
        QMessageBox::critical(this,tr("Erreur de modification"),tr("Modification non faite"));
        qWarning()<<"Erreur de modification"<<qry->lastError().text();
    }

    ouvert.fermeture();
}
