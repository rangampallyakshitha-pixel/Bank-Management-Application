#include "bankaccount.h"
#include <QStringList>

BankAccount::BankAccount() {
    accountNumber = 0;
    name = "";
    balance = 0;
}

BankAccount::BankAccount(int accNo, QString accName, double bal) {
    accountNumber = accNo;
    name = accName;
    balance = bal;
}

QString BankAccount::toFileString() const {
    return QString::number(accountNumber) + "," + name + "," + QString::number(balance);
}

BankAccount BankAccount::fromFileString(QString line) {
    QStringList data = line.split(",");

    if (data.size() == 3) {
        return BankAccount(
            data[0].toInt(),
            data[1],
            data[2].toDouble()
        );
    }

    return BankAccount();
}
