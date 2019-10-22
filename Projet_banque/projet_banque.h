#ifndef PROJET_BANQUE_H
#define PROJET_BANQUE_H

#include <QWidget>
#include <QtGui>
#include<QtSql>
#include<QDebug>
#include<QFileInfo>

class projet_banque : public QWidget
{
    Q_OBJECT
public:
        QSqlDatabase mydb;
        void fermeture()
        {
            mydb.close();
            mydb.removeDatabase(QSqlDatabase::defaultConnection);
        }

        bool ouverture()
        {
            mydb = QSqlDatabase::addDatabase("QSQLITE");
            mydb.setDatabaseName("../dab/database.db");
           if (!mydb.open())
               {
                   qDebug()<<("Echec de la connexion")<<mydb.lastError().text();
                   return false;
               }
           else
           {
               qDebug()<<("Connexion reussie");
               return true;
           }


        }
public:
    explicit projet_banque(QWidget *parent = 0);

private:
    QLineEdit *pass;
    QLabel *welcome;
    QLabel *logo;
    QPushButton *Introb;
    QWidget *Accueil;
    QFormLayout *passy;
    QLabel *warning;
    
signals:
    
public slots:
    bool IdentificationPass();
    
};

#endif // PROJET_BANQUE_H
