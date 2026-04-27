#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVector>
#include "bankaccount.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QLineEdit *accInput;
    QLineEdit *nameInput;
    QLineEdit *amountInput;
    QTextEdit *outputBox;

    QVector<BankAccount> accounts;

    void loadAccounts();
    void saveAccounts();
    int findAccount(int accNo);

private slots:
    void createAccount();
    void depositMoney();
    void withdrawMoney();
    void checkBalance();
    void showAllAccounts();

public:
    MainWindow(QWidget *parent = nullptr);
};

#endif