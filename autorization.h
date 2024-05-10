#ifndef AUTORIZATION_H
#define AUTORIZATION_H

#include <QDialog>


//для moveapp
#include <QMouseEvent>
#include <QEvent>

namespace Ui {
class Autorization;
}

class Autorization : public QDialog
{
    Q_OBJECT

public:
    explicit Autorization(QWidget *parent = nullptr);
    ~Autorization();
    bool loggedin = false;
    QString fhost = "";
    QString fport = "";
    QString flogin = "";
    QString fpassword = "";
    QString fdatabase = "";


private slots:
    void on_checkBox_notidiot_stateChanged(int arg1);

    void on_pushButton_go_clicked();

    void on_pushButton_connect_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Autorization *ui;
    //для кнопки moveapp
    bool movepressed = false;
};

#endif // AUTORIZATION_H
