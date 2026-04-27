#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <QString>

class BankAccount {
public:
    int accountNumber;
    QString name;
    double balance;

    BankAccount();
    BankAccount(int accNo, QString accName, double bal);

    QString toFileString() const;
    static BankAccount fromFileString(QString line);
};

#endif