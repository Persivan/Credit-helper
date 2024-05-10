#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



//добавлено
#include <QSqlDatabase>
#include "search.h"
#include <QWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QWidget *parent = nullptr, QString lg = "", QString pass = "", QString host = "", QString prt = "", QString datab = "");
    ~MainWindow();
    void getinfo(QString, QString, QString, QString, QString);

private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_valute_currentTextChanged(const QString &arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_lineEdit_month_editingFinished();

    void on_lineEdit_startvalue_editingFinished();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void work_credit();

    void on_tabWidget_currentChanged(int index);

    void on_lineEdit_penny_editingFinished();

    void on_lineEdit_percent_editingFinished();

    void on_lineEdit_nextpayment_editingFinished();

    void on_comboBox_valute_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_lineEdit_startvalue_textChanged(const QString &arg1);

    void on_lineEdit_penny_textChanged(const QString &arg1);

    void on_lineEdit_percent_textChanged(const QString &arg1);

    void on_lineEdit_month_textChanged(const QString &arg1);

    void on_lineEdit_nextpayment_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QString login = "";
    QString password = "";
    QString host = "";
    QString port = "";
    QString database = "";
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QString new_save_edit = "Add New"; //используется в кнопках search, clear, new
    bool firstcredit = true; //проверка первый ли кредит
    //для work_credit
    bool type;
    double body;
    int timeTerm; //months
    double percent;
    double value;
    double payment;
    double paymentProcents;
    double paymentBody;

};
#endif // MAINWINDOW_H
