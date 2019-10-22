#include "projet_banque.h"
#include "seconde_one.h"
#include <QtGui>
#include <QSqlDatabase>
#include <QObject>
#include <QSqlQuery>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlError>
#include <QSqlDriver>
#include <QDebug>
#include <QShortcut>

    //MAIN INTERFACE CLASS

projet_banque::projet_banque(QWidget *parent) :
    QWidget(parent)
{
    //Ajout de l'entete
    setWindowTitle("BAH App");
    setWindowIcon(QIcon("../icon/bah2.png"));


    //ajout d'une base de donnees
    if (!ouverture())
        {
            qWarning()<<"Echec de la connexion"<<mydb.lastError().text();
        }
    else
        {
            qWarning()<<"Connexion reussie";
        }

    welcome = new QLabel("Bienvenue sur BAH App");
    welcome->setStyleSheet("font-family: Arial Black, cursive; font-size: 20px; color:gray;");
    welcome->setAlignment(Qt::AlignCenter);

     //Buttons
    Introb = new QPushButton("Login");
    Introb->setStyleSheet("font-family: Britannic Bold;text-align:center; background-color: #2e409a; border: 1.9px solid #25326c;border-radius: 5px;padding: 3px 3px;color: white;font-size: 10px;");
    Introb->setFixedSize(150,35);
    Introb->setCursor(Qt::PointingHandCursor);

    logo = new QLabel;
    QImage img("../icon/bah2.png");
    QImage img2 = img.scaled(200,200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    logo->setPixmap(QPixmap::fromImage(img2));
    logo->setAlignment(Qt::AlignCenter);

    //Ajout d'un QLineEdit
    pass =new QLineEdit;
    pass->setEchoMode(QLineEdit::Password);
    pass->setAlignment(Qt::AlignCenter);
    pass->setFixedSize(200,25);
    pass->setStyleSheet("border: 1.9px solid #25326c;border-radius: 5px;");


    //Ajout d'un QHBoxLayout
    QHBoxLayout *layout0= new QHBoxLayout;
    layout0->addWidget(Introb);

    warning= new QLabel("Entrez le mot de passe de l'Administrateur");
    warning->setStyleSheet("font-family:Adobe Gothic Std B");

    QHBoxLayout *lalala =new QHBoxLayout;
    lalala->addWidget(pass);

    QHBoxLayout *pasi =new QHBoxLayout;
    pasi->addWidget(warning);
    pasi->setAlignment(Qt::AlignCenter);

    //definition de la Page d'introduction
    QVBoxLayout *l1 = new QVBoxLayout;
    l1->addWidget(logo);
    l1->addWidget(welcome);
    l1->addLayout(pasi);
    l1->addLayout(lalala);
    l1->addLayout(layout0);
    setLayout(l1);

    //Setting actions on the button for connect
    connect(Introb, SIGNAL(clicked()), this, SLOT(IdentificationPass()));
    connect(pass, SIGNAL(returnPressed()),this,SLOT(IdentificationPass()));
}

bool projet_banque::IdentificationPass()
{
    QString passwa = "administration";
    QString passrenvoi = pass->text();

    if (passrenvoi == passwa)
        {
            seconde_one *fene = new seconde_one;
            fene->setFixedSize(1080,500);
            fene->show();
            setVisible(false);
                return 1;
        }
    else if(passrenvoi.isEmpty())
        {
            QMessageBox::information(this, "Test", QString("Veuillez rentrer une mot de passe").arg(passrenvoi));
        }
    else
        {
            QMessageBox::information(this, "Test", QString("Mot de passe incorrect").arg(passrenvoi));
            pass->clear();
            return 0;
        }
}




