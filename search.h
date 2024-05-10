#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>


//добавлено
#include <QSqlDatabase>



namespace Ui {
class Search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr);
    explicit Search(QWidget *parent = nullptr, QString lg = "", QString pass = "", QString host = "", QString prt = "", QString datab = "");
    ~Search();

    QString fuserid = "";

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_userid_2_returnPressed();

    void on_lineEdit_series_returnPressed();

    void on_lineEdit_number_returnPressed();

private:
    Ui::Search *ui;
    QString login = "";
    QString password = "";
    QString host = "";
    QString port = "";
    QString database = "";
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
};

#endif // SEARCH_H
