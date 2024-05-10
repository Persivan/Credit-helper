#include "search.h"
#include "ui_search.h"


//sql
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVariant>


Search::Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);

}

Search::Search(QWidget *parent, QString lg, QString pass, QString hst, QString prt, QString datab)
    : QDialog(parent)
    , ui(new Ui::Search)
    , login(lg)
    , password(pass)
    , host(hst)
    , port(prt)
    , database(datab)
{
    ui->setupUi(this);
    //скрыть кнопки windows
    setWindowFlags(Qt::FramelessWindowHint);
    //кнопка close
    QPixmap pixmap(":/recources/img/close3.png");
    QIcon ButtonIcon(pixmap);
    ui->pushButton_3->setIcon(ButtonIcon);
    ui->pushButton_3->setIconSize(QSize(15,15));

    ui->pushButton_search->setFocus();
    db.setHostName(host);
    db.setPort(port.toInt());
    db.setUserName(login);
    db.setPassword(password);
    db.setDatabaseName(database);
    if (!db.open())
    {
        QMessageBox::warning(this, "Error", "Error to connect sql in searchwindow");
    }
}

Search::~Search()
{
    delete ui;
}

void Search::on_pushButton_search_clicked()
{
    fuserid.clear();
    QSqlQuery query = QSqlQuery(db);
    if (!(ui->lineEdit_userid_2->text().isEmpty()))
    {
        query.exec("SELECT userID FROM bank.personal_data WHERE userID = " + ui->lineEdit_userid_2->text() + " LIMIT 1;");
        //результат поиска
        if (query.first())
        {
            fuserid = query.value(0).toString();
            hide();
        }
        else
        {
            ui->label_status->setText("User not found");
        }
    }
    else if (!(ui->lineEdit_series->text().isEmpty()) && !(ui->lineEdit_number->text().isEmpty()))
    {
        //Ищем пользователя в базе данных по паспорту
        query.exec("SELECT userID FROM bank.personal_data WHERE passSeries = " + ui->lineEdit_series->text() + " and passNumber = " + ui->lineEdit_number->text() + " LIMIT 1;");
        ui->lineEdit_userid_2->setText(query.value(0).toString());
        //результат поиска
        if (query.first())
        {
            fuserid = query.value(0).toString();
            hide();
        }
        else
        {
            ui->label_status->setText("User not found");
        }
    }
    else
    {
        ui->label_status->setText("Please enter more information about user");
    }
}


void Search::on_pushButton_3_clicked()
{
    close();
}


void Search::on_lineEdit_userid_2_returnPressed()
{
    on_pushButton_search_clicked();
}


void Search::on_lineEdit_series_returnPressed()
{
    on_pushButton_search_clicked();
}


void Search::on_lineEdit_number_returnPressed()
{
    on_pushButton_search_clicked();
}

