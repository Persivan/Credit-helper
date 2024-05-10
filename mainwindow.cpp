#include "mainwindow.h"
#include "ui_mainwindow.h"


//добавлено
#include <QMessageBox>
#include <QGraphicsBlurEffect> //для блюра
#include <QPixmap> //для uwu
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <map>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(QWidget *parent, QString lg, QString pass, QString hst, QString prt, QString datab)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

    ui->plainTextEdit->setReadOnly(true);
    db.setHostName(host);
    db.setPort(port.toInt());
    db.setUserName(login);
    db.setPassword(password);
    db.setDatabaseName(database);
    if (!db.open())
    {
        QMessageBox::warning(this, "Error","Error to connect sql in mainwindow");
    }

    //таблица
    ui->tableWidget->setColumnWidth(0, 160);
    ui->tableWidget->setColumnWidth(1, 160);
    ui->tableWidget->setColumnWidth(2, 160);
    ui->tableWidget->setColumnWidth(3, 160);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clear_clicked()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Sure?", "This will delete all info",  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        //очистка полей
        ui->lineEdit_age->clear();
        ui->lineEdit_birthplace->clear();
        ui->lineEdit_dateofbirth->clear();
        ui->lineEdit_email->clear();
        ui->lineEdit_firstname->clear();
        ui->comboBox_gender->setCurrentIndex(0);
        ui->lineEdit_passportcodedepartment->clear();
        ui->lineEdit_passportdate->clear();
        ui->lineEdit_passportgivenby->clear();
        ui->lineEdit_passportnumber->clear();
        ui->lineEdit_patronymic->clear();
        ui->lineEdit_phone->clear();
        ui->lineEdit_rating->clear();
        ui->lineEdit_residencepermit->clear();
        ui->lineEdit_secondname->clear();
        ui->lineEdit_series->clear();
        ui->lineEdit_userid->clear();
        //залочить поля
        ui->lineEdit_age->setEnabled(false);
        ui->lineEdit_birthplace->setEnabled(false);
        ui->lineEdit_dateofbirth->setEnabled(false);
        ui->lineEdit_email->setEnabled(false);
        ui->lineEdit_firstname->setEnabled(false);
        ui->comboBox_gender->setEnabled(false);
        ui->lineEdit_passportcodedepartment->setEnabled(false);
        ui->lineEdit_passportdate->setEnabled(false);
        ui->lineEdit_passportgivenby->setEnabled(false);
        ui->lineEdit_passportnumber->setEnabled(false);
        ui->lineEdit_patronymic->setEnabled(false);
        ui->lineEdit_phone->setEnabled(false);
        ui->lineEdit_residencepermit->setEnabled(false);
        ui->lineEdit_secondname->setEnabled(false);
        ui->lineEdit_series->setEnabled(false);
        new_save_edit = "Add New";
        ui->pushButton_edit->setText(new_save_edit);
    }
}


void MainWindow::on_pushButton_edit_clicked()
{
    if (new_save_edit == "Edit")
    {
        ui->lineEdit_age->setEnabled(true);
        ui->lineEdit_birthplace->setEnabled(true);
        ui->lineEdit_dateofbirth->setEnabled(true);
        ui->lineEdit_email->setEnabled(true);
        ui->lineEdit_firstname->setEnabled(true);
        ui->comboBox_gender->setEnabled(true);
        ui->lineEdit_passportcodedepartment->setEnabled(true);
        ui->lineEdit_passportdate->setEnabled(true);
        ui->lineEdit_passportgivenby->setEnabled(true);
        ui->lineEdit_passportnumber->setEnabled(true);
        ui->lineEdit_patronymic->setEnabled(true);
        ui->lineEdit_phone->setEnabled(true);
        ui->lineEdit_residencepermit->setEnabled(true);
        ui->lineEdit_secondname->setEnabled(true);
        ui->lineEdit_series->setEnabled(true);
        //Запомнить какая следующая
        new_save_edit = "Save";
    }
    else if(new_save_edit == "Save")
    {
        //Залочить поля
        ui->lineEdit_age->setEnabled(false);
        ui->lineEdit_birthplace->setEnabled(false);
        ui->lineEdit_dateofbirth->setEnabled(false);
        ui->lineEdit_email->setEnabled(false);
        ui->lineEdit_firstname->setEnabled(false);
        ui->comboBox_gender->setEnabled(false);
        ui->lineEdit_passportcodedepartment->setEnabled(false);
        ui->lineEdit_passportdate->setEnabled(false);
        ui->lineEdit_passportgivenby->setEnabled(false);
        ui->lineEdit_passportnumber->setEnabled(false);
        ui->lineEdit_patronymic->setEnabled(false);
        ui->lineEdit_phone->setEnabled(false);
        ui->lineEdit_residencepermit->setEnabled(false);
        ui->lineEdit_secondname->setEnabled(false);
        ui->lineEdit_series->setEnabled(false);
        //Запомнить какая следующая
        new_save_edit = "Edit";
        //проверка изменение текущего или добавление нового
        QSqlQuery query = QSqlQuery(db);
        query.exec("select count(*) + 1 from personal_data;");
        query.first();
        if (ui->lineEdit_userid->text() == query.value(0).toString())
        {
            //создаем sql
            ui->lineEdit_userid->setText(query.value(0).toString());
            qDebug() << query.exec("INSERT INTO `bank`.`personal_data` (`firstName`, `secondName`, `patronymic`, `age`, `email`, `phoneNumber`, `passCodeDepartment`, `passSeries`, `passNumber`, `passGivenBy`, `passDate`, `genderIsFemale`, `dateOfBirth`, `birthplace`, `residencePermit`) VALUES ('"
    + ui->lineEdit_firstname->text() + "', '"
    + ui->lineEdit_secondname->text() + "', '"
    + ui->lineEdit_patronymic->text() + "', '"
    + ui->lineEdit_age->text() + "', '"
    + ui->lineEdit_email->text() + "', '"
    + ui->lineEdit_phone->text() + "', '"
    + ui->lineEdit_passportcodedepartment->text() + "', '"
    + ui->lineEdit_series->text() + "', '"
    + ui->lineEdit_passportnumber->text() + "', '"
    + ui->lineEdit_passportgivenby->text() + "', '"
    + ui->lineEdit_passportdate->text() + "', '"
    + QString::number(ui->comboBox_gender->currentIndex()) + "', '"
    + ui->lineEdit_dateofbirth->text() + "', '"
    + ui->lineEdit_birthplace->text() + "', '"
    + ui->lineEdit_residencepermit->text() +
                       "');");
            qDebug() << query.lastError();
        }
        else
        {
            QSqlQuery query2 = QSqlQuery(db);
            qDebug() << query2.exec("UPDATE `bank`.`personal_data` SET `firstName` = '" + ui->lineEdit_firstname->text()
                       + "', `secondName` = '" + ui->lineEdit_secondname->text()
                       + "', `patronymic` = '" + ui->lineEdit_patronymic->text()
                       + "', `age` = '" +ui->lineEdit_age->text()
                       + "', `email` = '" + ui->lineEdit_email->text()
                       + "', `phoneNumber` = '" + ui->lineEdit_phone->text()
                       + "', `passCodeDepartment` = '" + ui->lineEdit_passportcodedepartment->text()
                       + "', `passSeries` = '" + ui->lineEdit_series->text()
                       + "', `passNumber` = '" + ui->lineEdit_passportnumber->text()
                       + "', `passGivenBy` = '" + ui->lineEdit_passportgivenby->text()
                       + "', `passDate` = '" + ui->lineEdit_passportdate->text()
                       + "', `genderIsFemale` = '" + QString::number(ui->comboBox_gender->currentIndex())
                       + "', `dateOfBirth` = '" + ui->lineEdit_dateofbirth->text()
                       + "', `birthplace` = '" + ui->lineEdit_birthplace->text()
                       + "', `residencePermit` = '" + ui->lineEdit_residencepermit->text()
                       + "' WHERE (`userID` = '" + ui->lineEdit_userid->text() + "');");
            qDebug() << query2.lastError();
        }


    }
    else if(new_save_edit == "Add New")
    {
        ui->lineEdit_age->setEnabled(true);
        ui->lineEdit_birthplace->setEnabled(true);
        ui->lineEdit_dateofbirth->setEnabled(true);
        ui->lineEdit_email->setEnabled(true);
        ui->lineEdit_firstname->setEnabled(true);
        ui->comboBox_gender->setEnabled(true);
        ui->lineEdit_passportcodedepartment->setEnabled(true);
        ui->lineEdit_passportdate->setEnabled(true);
        ui->lineEdit_passportgivenby->setEnabled(true);
        ui->lineEdit_passportnumber->setEnabled(true);
        ui->lineEdit_patronymic->setEnabled(true);
        ui->lineEdit_phone->setEnabled(true);
        ui->lineEdit_residencepermit->setEnabled(true);
        ui->lineEdit_secondname->setEnabled(true);
        ui->lineEdit_series->setEnabled(true);
        //Значения для автозаполнения
        ui->lineEdit_rating->setText("100");
        ui->lineEdit_rating->setStyleSheet("color: #00ff00");
        //создаем запрос для получения нового userid
        QSqlQuery query = QSqlQuery(db);
        query.exec("select count(*) + 1 from personal_data;");
        query.first();
        ui->lineEdit_userid->setText(query.value(0).toString());
        query.clear();
        //Запомнить какая следующая
        new_save_edit = "Save";

    }
    else
    {
        qDebug() << "4";
    }
    ui->pushButton_edit->setText(new_save_edit);
}


void MainWindow::on_pushButton_search_clicked()
{
    //блюр
    QGraphicsBlurEffect *effect = new QGraphicsBlurEffect(this);
    this->setGraphicsEffect(effect);
    //Добавить реализацию поиска
    Search searchwindow(nullptr, login, password, host, port, database);
    searchwindow.exec();
    this->setGraphicsEffect(nullptr);
    //вышли из окна получили fuserid
    //поиск по userid из окна
    if (searchwindow.fuserid != "")
    {
        QSqlQuery query = QSqlQuery(db);
        query.exec("SELECT * FROM bank.personal_data WHERE userID = " + searchwindow.fuserid + " LIMIT 1;");
        query.first();
        ui->lineEdit_age->setText(query.value(5).toString());
        ui->lineEdit_birthplace->setText(query.value(15).toString());
        ui->lineEdit_dateofbirth->setText(query.value(14).toString());
        ui->lineEdit_email->setText(query.value(6).toString());
        ui->lineEdit_firstname->setText(query.value(2).toString());
        if (query.value(13).toBool())
        {
            ui->comboBox_gender->setCurrentIndex(1);
        }
        else
        {
            ui->comboBox_gender->setCurrentIndex(0);
        }
        ui->lineEdit_passportcodedepartment->setText(query.value(8).toString());
        ui->lineEdit_passportdate->setText(query.value(12).toString());
        ui->lineEdit_passportgivenby->setText(query.value(11).toString());
        ui->lineEdit_passportnumber->setText(query.value(10).toString());
        ui->lineEdit_patronymic->setText(query.value(4).toString());
        ui->lineEdit_phone->setText(query.value(7).toString());
        ui->lineEdit_rating->setText(query.value(1).toString());
        //Изменить цвет рейтинга на соответств
        int rating = ui->lineEdit_rating->text().toInt() / 10;
        std::map <int, QString> colormap = {
            {0, "color: #ff0000"},
            {1, "color: #ff0000"},
            {2, "color: #ff3200"},
            {3, "color: #ff6400"},
            {4, "color: #ff9600"},
            {5, "color: #ffC800"},
            {6, "color: #C8ff00"},
            {7, "color: #96ff00"},
            {8, "color: #64ff00"},
            {9, "color: #32ff00"},
            {10, "color: #00ff00"},
        };
        ui->lineEdit_rating->setStyleSheet(colormap[rating]);
        ui->lineEdit_residencepermit->setText(query.value(16).toString());
        ui->lineEdit_secondname->setText(query.value(3).toString());
        ui->lineEdit_series->setText(query.value(9).toString());
        ui->lineEdit_userid->setText(searchwindow.fuserid);
        new_save_edit = "Edit";
        ui->pushButton_edit->setText(new_save_edit);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    //clear tab 2
    ui->tableWidget->setRowCount(0);
    ui->lineEdit_closecredit->clear();
    ui->comboBox->setCurrentText("Differentiated");
    ui->lineEdit_month->clear();
    ui->lineEdit_opencredit->clear();
    ui->lineEdit_percent->clear();
    ui->lineEdit_startvalue->clear();
    ui->comboBox_valute->setCurrentText("RUB");
    ui->lineEdit_closecredit->clear();
    ui->lineEdit_nextpayment->clear();
    ui->lineEdit_penny->clear();
    ui->comboBox_valute->setCurrentText("Fixed summ");
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_pushButton_3_clicked()
{
    close();
}


void MainWindow::on_comboBox_valute_currentTextChanged(const QString &arg1)
{
    if (ui->comboBox_2->currentText() == "Fixed summ")
    {
        ui->label_penny->setText(arg1);
    }
    //меняем названия столбцов в таблице
    QStringList tableheadersname = { "Payment | " + arg1, "Payment % | " + arg1, "Payment body | " + arg1, "Left to pay | " + arg1};
    ui->tableWidget->setHorizontalHeaderLabels(tableheadersname);
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Fixed summ")
    {
        ui->label_penny->setText(ui->comboBox_valute->currentText());
    }
    else
    {
        ui->label_penny->setText("  %   ");
    }
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_lineEdit_month_editingFinished()
{
    QDate data;
    //вывести текущую дату (не привязана к data)
    ui->lineEdit_opencredit->setText(data.currentDate().toString("dd MMM yyyy"));
    //установить текущуую дату
    data.setDate(data.currentDate().year(), data.currentDate().month(), data.currentDate().day());
    //добавить месяц и вывести в лейбл
    data = data.addMonths(1);
    ui->label_6->setText(data.toString("MMM yyyy"));
    //добавить месяца - 1
    data = data.addMonths(ui->lineEdit_month->text().toInt() - 1);
    //вывести
    ui->lineEdit_closecredit->setText(data.toString("dd MMM yyyy"));
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_lineEdit_startvalue_editingFinished()
{
    QDate data;
    //вывести текущую дату (не привязана к data)
    ui->lineEdit_opencredit->setText(data.currentDate().toString("dd MMM yyyy"));
    //установить текущуую дату
    data.setDate(data.currentDate().year(), data.currentDate().month(), data.currentDate().day());
    //добавить месяц и вывести в лейбл
    data = data.addMonths(1);
    ui->label_6->setText(data.toString("MMM yyyy"));
    //добавить месяца - 1
    data = data.addMonths(ui->lineEdit_month->text().toInt() - 1);
    //вывести
    ui->lineEdit_closecredit->setText(data.toString("dd MMM yyyy"));
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_pushButton_clicked()
{
    if (ui->lineEdit_percent->text().isEmpty()
        || ui->lineEdit_month->text().isEmpty()
        || ui->lineEdit_penny->text().isEmpty()
        || ui->lineEdit_closecredit->text().isEmpty()
        || ui->lineEdit_nextpayment->text().isEmpty()
        || ui->lineEdit_opencredit->text().isEmpty()
        || ui->lineEdit_startvalue->text().isEmpty())
    {
        ui->label_16->setText("Enter correct information");
    }
    else
    {
        if (!firstcredit)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Another credit", "It is another credit, are you sure?",  QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                std::map<QString, QString> diff = {{"Differentiated", "1"}, {"Annuity", "0"}};
                std::map<QString, QString> pennytype = {{"Fixed summ", "fix"}, {"Сredit increase", "upp"}, {"Percentage of the total outstanding debt", "per"}};
                QDate data = QDate::currentDate();
                QDate datetosql;
                datetosql.setDate(data.currentDate().year(), data.currentDate().month(), ui->lineEdit_nextpayment->text().toInt());
                datetosql = datetosql.addMonths(1);
                QSqlQuery query = QSqlQuery(db);
                qDebug() << query.exec("INSERT INTO `bank`.`credits` (`userID`, `creditIsDiff`, `startValue`, `bodyValue`, `currency`, `paymentPercents`, `paymentBody`, `percent`, `penny`, `pennyType`, `month`, `nextPayment`, `openCredit`) VALUES ('"
        + ui->lineEdit_userid_tab2->text() + "', '"
        + diff[ui->comboBox->currentText()] + "', '"
        + ui->lineEdit_startvalue->text() + "', '"
        + ui->lineEdit_startvalue->text() + "', '"
        + ui->comboBox_valute->currentText() + "', '"
        + ui->tableWidget->item(0,1)->text() + "', '"
        + ui->tableWidget->item(0,2)->text() + "', '"
        + ui->lineEdit_percent->text() + "', '"
        + ui->lineEdit_penny->text() + "', '"
        + pennytype[ui->comboBox_2->currentText()] + "', '"
        + ui->lineEdit_month->text() + "', '"
        + datetosql.toString("yyyy-MM-dd") + "', '"
        + data.toString("yyyy-MM-dd")
        + "');");
                qDebug() << query.lastQuery();
                if (query.lastError().isValid())
                {
                    ui->label_16->setText("Error to add credit");
                }
                else
                {
                    ui->label_16->setText("Saved");
                }
                qDebug() << query.lastError();
            }
        }
        else
        {
            firstcredit = false;
            std::map<QString, QString> diff = {{"Differentiated", "1"}, {"Annuity", "0"}};
            std::map<QString, QString> pennytype = {{"Fixed summ", "fix"}, {"Сredit increase", "upp"}, {"Percentage of the total outstanding debt", "per"}};
            QDate data = QDate::currentDate();
            QDate datetosql;
            datetosql.setDate(data.currentDate().year(), data.currentDate().month(), ui->lineEdit_nextpayment->text().toInt());
            datetosql = datetosql.addMonths(1);
            QSqlQuery query = QSqlQuery(db);
            qDebug() << query.exec("INSERT INTO `bank`.`credits` (`userID`, `creditIsDiff`, `startValue`, `bodyValue`, `currency`, `paymentPercents`, `paymentBody`, `percent`, `penny`, `pennyType`, `month`, `nextPayment`, `openCredit`) VALUES ('"
    + ui->lineEdit_userid_tab2->text() + "', '"
    + diff[ui->comboBox->currentText()] + "', '"
    + ui->lineEdit_startvalue->text() + "', '"
    + ui->lineEdit_startvalue->text() + "', '"
    + ui->comboBox_valute->currentText() + "', '"
    + ui->tableWidget->item(0,1)->text() + "', '"
    + ui->tableWidget->item(0,2)->text() + "', '"
    + ui->lineEdit_percent->text() + "', '"
    + ui->lineEdit_penny->text() + "', '"
    + pennytype[ui->comboBox_2->currentText()] + "', '"
    + ui->lineEdit_month->text() + "', '"
    + datetosql.toString("yyyy-MM-dd") + "', '"
    + data.toString("yyyy-MM-dd")
    + "');");
            qDebug() << query.lastQuery();
            if (query.lastError().isValid())
            {
                ui->label_16->setText("Error to add credit");
            }
            else
            {
                ui->label_16->setText("Saved");
            }
            qDebug() << query.lastError();
        }


    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QDate data;
    ui->tableWidget->setRowCount(0);
    if (ui->lineEdit_startvalue->text().isEmpty() || ui->lineEdit_startvalue->text().startsWith("0")
            || ui->lineEdit_percent->text().isEmpty()
            || ui->lineEdit_month->text().isEmpty() || ui->lineEdit_month->text().startsWith("0")
            || ui->lineEdit_nextpayment->text().isEmpty()
            || ui->lineEdit_opencredit->text().isEmpty()
            || !data.isValid(data.currentDate().year(), data.currentDate().month() + 1, ui->lineEdit_nextpayment->text().toInt())
        )
    {
        ui->label_16->setText("Enter correct info");
    }
    else
    {
        //установить текущуую дату
        data.setDate(data.currentDate().year(), data.currentDate().month(), ui->lineEdit_nextpayment->text().toInt());
        //меняем названия столбцов в таблице
        QStringList tableheadersname = { "Payment | " + ui->comboBox_valute->currentText(), "Payment % | " + ui->comboBox_valute->currentText(), "Payment body | " + ui->comboBox_valute->currentText(), "Left to pay | " + ui->comboBox_valute->currentText() };
        ui->tableWidget->setHorizontalHeaderLabels(tableheadersname);
        //заполнять созданную
        if (ui->comboBox->currentText() == "Differentiated")
        {
            type = 1;
        }
        else
        {
            type = 0;
        }
        body = ui->lineEdit_startvalue->text().toDouble();
        timeTerm = ui->lineEdit_month->text().toInt();
        percent = ui->lineEdit_percent->text().toDouble() / 100;
        value = body;
        //создаем нужное количество строк
        ui->tableWidget->setRowCount(ui->lineEdit_month->text().toInt());
        for (int i = 0; i < ui->lineEdit_month->text().toInt(); i++)
        {
            //Заполняем строки по i
            data = data.addMonths(1);
            ui->tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(data.toString("MMM yy")));
            work_credit();
            QString strtemp = QString::number(payment);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(strtemp));
            strtemp = QString::number(paymentProcents);
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(strtemp));
            strtemp = QString::number(paymentBody);
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(strtemp));
            strtemp = QString::number(value);
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(strtemp));
        }
        if (ui->lineEdit_userid_tab2->text() != "")
        {
            ui->pushButton->setEnabled(true);
        }
        else
        {
            ui->pushButton->setEnabled(false);
        }
    }

}

//служебная для calculate
void MainWindow::work_credit() {
        if (this -> type) {
            long double sT = this -> body / this -> timeTerm; //сумма, которая идет на погашения тела кредита
            long double iN = value * percent; //сумма, уплачиваемых процентов
            this -> payment = sT + iN;
        }
        else {
            this -> payment = this -> body * (this -> percent + this -> percent / (pow(1 + this -> percent, this -> timeTerm) - 1));
            qDebug() << "payment1 = " << payment;
        }
        this -> paymentProcents = this -> value * this -> percent;
        this -> paymentBody = this -> payment - this -> paymentProcents;

        this -> value += this -> value * this -> percent;
        this -> value -= payment;
        if (this -> value < 0.1)
            this -> value = 0;
        qDebug() << "value = " << value;
        qDebug() << "body = " << body;
        qDebug() << "payment = " << payment;
        qDebug() << "payment percents = " << paymentProcents;
        qDebug() << "payment body = " << paymentBody;
        qDebug() << "sd";
}



void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 1)
    {
        ui->lineEdit_userid_tab2->setText(ui->lineEdit_userid->text());
    }
    if (index == 2)
    {
        ui->tableWidget_2->setRowCount(0);
        ui->lineEdit_userid_tab3->setText(ui->lineEdit_userid->text());
        if (ui->lineEdit_userid_tab3->text() != "" )
        {
            //получили из sql количество кредитов у пользователя
            QSqlQuery query = QSqlQuery(db);
            //qDebug() << query.exec("SELECT count(userID) FROM bank.credits where userID = " + ui->lineEdit_userid_tab3->text() + ";");
            query.exec("select * from bank.credits where userID = " +  ui->lineEdit_userid_tab3->text() + ";");
            query.first();
            int i = 0;
            do
            {
                qDebug() << i;
                //добавили строку если количество не равно 0
                QSqlQuery query2 = QSqlQuery(db);
                query2.exec("SELECT count(userID) FROM bank.credits where userID = " + ui->lineEdit_userid_tab3->text() + ";");
                query2.first();
                if (query2.value(0) != 0)
                {
                    ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
                }
                //заполнили элементами
                //тип кредита
                if (query.value(2).toBool())
                {
                    ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem("Differentiated"));
                }
                else
                {
                    ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem("Annuity"));
                }
                ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(query.value(3).toString()));
                ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(query.value(4).toString()));
                ui->tableWidget_2->setItem(i, 3, new QTableWidgetItem(query.value(5).toString()));
                ui->tableWidget_2->setItem(i, 4, new QTableWidgetItem(query.value(6).toString()));
                ui->tableWidget_2->setItem(i, 5, new QTableWidgetItem(query.value(7).toString()));
                ui->tableWidget_2->setItem(i, 6, new QTableWidgetItem(query.value(8).toString()));
                ui->tableWidget_2->setItem(i, 7, new QTableWidgetItem(query.value(9).toString()));
                ui->tableWidget_2->setItem(i, 8, new QTableWidgetItem(query.value(10).toString()));
                ui->tableWidget_2->setItem(i, 9, new QTableWidgetItem(query.value(11).toString()));
                if (query.value(12).toString() == "fix")
                {
                    ui->tableWidget_2->setItem(i, 10, new QTableWidgetItem("Fixed summ"));
                }
                else if (query.value(12).toString() == "upp")
                {
                    ui->tableWidget_2->setItem(i, 10, new QTableWidgetItem("Сredit increase"));
                }
                else
                {
                    ui->tableWidget_2->setItem(i, 10, new QTableWidgetItem("Percentage of debt"));
                }

                ui->tableWidget_2->setItem(i, 11, new QTableWidgetItem(query.value(13).toString()));
                ui->tableWidget_2->setItem(i, 12, new QTableWidgetItem(query.value(14).toString()));
                ui->tableWidget_2->setItem(i, 13, new QTableWidgetItem(query.value(15).toString()));
                ui->tableWidget_2->setItem(i, 14, new QTableWidgetItem(query.value(16).toString()));
                i++;
            }
            while (query.next());
        }


        //int creditcount = query.value(0).toInt();
        //заполнить таблицу TODO
        //для перевода в string QString strtemp = QString::number(payment);
        //результат поиска количества в sql
        /*for (int i = 0; i < creditcount; i++)
        {
            //добавили строку
            ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
            //заполнили элементами
            query.exec("select * from bank.credits where userID = " +  ui->lineEdit_userid_tab3->text() + ";");
            query.first();
            //тип кредита
            if (query.value(2).toBool())
            {
                ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem("Differentiated"));
            }
            else
            {
                ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem("Annuity"));
            }
            ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidget_2->setItem(i, 3, new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidget_2->setItem(i, 4, new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidget_2->setItem(i, 5, new QTableWidgetItem(query.value(7).toString()));
            ui->tableWidget_2->setItem(i, 6, new QTableWidgetItem(query.value(8).toString()));
            ui->tableWidget_2->setItem(i, 7, new QTableWidgetItem(query.value(9).toString()));
            ui->tableWidget_2->setItem(i, 8, new QTableWidgetItem(query.value(10).toString()));
            ui->tableWidget_2->setItem(i, 9, new QTableWidgetItem(query.value(11).toString()));
            if (query.value(12).toString() == "fix")
            {
                ui->tableWidget_2->setItem(i, 10, new QTableWidgetItem("Fixed summ"));
            }
            else if (query.value(12).toString() == "upp")
            {
                ui->tableWidget_2->setItem(i, 10, new QTableWidgetItem("Сredit increase"));
            }
            else
            {
                ui->tableWidget_2->setItem(i, 10, new QTableWidgetItem("Percentage of debt"));
            }

            ui->tableWidget_2->setItem(i, 11, new QTableWidgetItem(query.value(13).toString()));
            ui->tableWidget_2->setItem(i, 12, new QTableWidgetItem(query.value(14).toString()));
            ui->tableWidget_2->setItem(i, 13, new QTableWidgetItem(query.value(15).toString()));
            ui->tableWidget_2->setItem(i, 14, new QTableWidgetItem(query.value(16).toString()));
            query.next();
        }*/



    }
}


void MainWindow::on_lineEdit_penny_editingFinished()
{
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_lineEdit_percent_editingFinished()
{
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_lineEdit_nextpayment_editingFinished()
{
    //установить текущуую дату
    QDate data;
    data.setDate(data.currentDate().year(), data.currentDate().month(), ui->lineEdit_nextpayment->text().toInt());
    data = data.addMonths(ui->lineEdit_month->text().toInt());
    ui->lineEdit_closecredit->setText(data.toString("dd MMM yyyy"));
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_comboBox_valute_currentIndexChanged(const QString &arg1)
{
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_lineEdit_startvalue_textChanged(const QString &arg1)
{
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_lineEdit_penny_textChanged(const QString &arg1)
{
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_lineEdit_percent_textChanged(const QString &arg1)
{
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_lineEdit_month_textChanged(const QString &arg1)
{
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}


void MainWindow::on_lineEdit_nextpayment_textChanged(const QString &arg1)
{
    //лочить кнопку save
    ui->pushButton->setEnabled(false);
}

