#include "mainwindow.h"


#include <QApplication>


//добавлено
#include <QFile>


//добавленные окна
#include "autorization.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //стиль
    QFile stylesheedfile(":/recources/styleuwu.qss");
    stylesheedfile.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(stylesheedfile.readAll());
    a.setStyleSheet(stylesheet);


    //запускаем окно авторизации
    Autorization autorizationwindow;
    autorizationwindow.setModal(true); //не обязательно, по умолч true
    autorizationwindow.exec();
    //условие для появления окна this
    if (autorizationwindow.loggedin != true)
    {
        return 0;
    }
    MainWindow w(nullptr, autorizationwindow.flogin, autorizationwindow.fpassword, autorizationwindow.fhost, autorizationwindow.fport, autorizationwindow.fdatabase);
    w.show();
    return a.exec();
}
