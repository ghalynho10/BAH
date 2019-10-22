#include <QtGui>
#include <QApplication>
#include <projet_banque.h>

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    projet_banque w;
    w.setFixedSize(350,350);
    w.setStyleSheet("background-color:white;");
    w.show();
    return a.exec();

}
