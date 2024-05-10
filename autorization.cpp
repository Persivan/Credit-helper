#include "autorization.h"
#include "ui_autorization.h"


#include <QMessageBox>
//sql тестовое подключение
#include <QSqlDatabase>
#include <QSqlError>

Autorization::Autorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Autorization)
{
    ui->setupUi(this);
    //вкладка заблокирована по умолчанию
    ui->tabWidget->setTabEnabled(1, 0);
    //вкладка заблокирована по умолчанию
    ui->tabWidget->setTabEnabled(2, 0);
    //скрыть кнопки windows
    setWindowFlags(Qt::FramelessWindowHint);
    //uwu
    QPixmap pixmap2(":/uwu/e29.png");
    ui->label_uwu->setPixmap(pixmap2.scaled(128,128, Qt::KeepAspectRatio));
    QPixmap pixmap3(":/uwu/notuwu.png");
    ui->label_notuwu->setPixmap(pixmap3.scaled(128,128, Qt::KeepAspectRatio));
    QPixmap pixmap4(":/uwu/max.jpg");
    ui->label_max->setPixmap(pixmap4.scaled(128,128, Qt::KeepAspectRatio));
    //кнопка close
    QPixmap pixmap(":/recources/img/close3.png");
    QIcon ButtonIcon(pixmap);
    ui->pushButton_3->setIcon(ButtonIcon);
    ui->pushButton_3->setIconSize(QSize(15,15));
    //двигать приложение на кнопку
    ui->pushButton_moveapp->setFlat(true);
    ui->pushButton_moveapp->setStyleSheet("background-color: 39af98");
    //тестовое подключение
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QString host = ui->lineEdit_sqlhost->text();
    QString port = ui->lineEdit_sqlport->text();
    QString login = "test_connection";
    QString password = "";
    QString database = "test_connection";
    db.setHostName(host);
    db.setPort(port.toInt());
    db.setUserName(login);
    db.setPassword(password);
    db.setDatabaseName(database);
    if (db.open())
    {
        ui->label_sqlstatus1->setText("Server/SQL Connected (name: " + login + ")");
    }
    else
    {
        ui->label_sqlstatus1->setText("Server/SQL NOT Connected (name: " + login + ")");
    }
    db.close();  
}

Autorization::~Autorization()
{
    delete ui;
}

void Autorization::on_checkBox_notidiot_stateChanged(int arg1)
{
    ui->tabWidget->setTabEnabled(1, arg1);
    ui->tabWidget->setTabEnabled(2, arg1);
}


void Autorization::on_pushButton_go_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QString host = ui->lineEdit_sqlhost->text();
    QString port = ui->lineEdit_sqlport->text();
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();
    QString database = ui->lineEdit_database->text();
    db.setHostName(host);
    db.setPort(port.toInt());
    db.setUserName(login);
    db.setPassword(password);
    db.setDatabaseName(database);
    if (db.open())
    {
        this->hide();
        loggedin = true;
        fhost = host;
        fport = port;
        flogin = login;
        fpassword = password;
        fdatabase = database;
    }
    else
    {
        if (ui->label_sqlstatus1->text().contains("Server/SQL Connected", Qt::CaseInsensitive))
        {
            ui->label_status->setText("Wrong login or password");
        }
        else
        {
            ui->label_status->setText("Server NOT Connected");
        }
    }
    db.close();
}


void Autorization::on_pushButton_connect_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QString host = ui->lineEdit_sqlhost->text();
    QString port = ui->lineEdit_sqlport->text();
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();
    QString database = ui->lineEdit_database->text();
    db.setHostName(host);
    db.setPort(port.toInt());
    db.setUserName(login);
    db.setPassword(password);
    db.setDatabaseName(database);
    if (db.open())
    {
        ui->label_sqlstatus1->setText("Server/SQL Connected (name: " + login + ")");
    }
    else
    {
        ui->label_sqlstatus1->setText("Server/SQL NOT Connected (name: " + login + ")");
    }
    db.close();
}


void Autorization::on_pushButton_3_clicked()
{
    close();
}
