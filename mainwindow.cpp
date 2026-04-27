#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Bank Management Application");
    resize(500, 600);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout();

    QLabel *title = new QLabel("Bank Management System");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #0066cc;");

    accInput = new QLineEdit();
    accInput->setPlaceholderText("Enter Account Number");

    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter Customer Name");

    amountInput = new QLineEdit();
    amountInput->setPlaceholderText("Enter Amount");

    QPushButton *createBtn = new QPushButton("Create Account");
    QPushButton *depositBtn = new QPushButton("Deposit");
    QPushButton *withdrawBtn = new QPushButton("Withdraw");
    QPushButton *balanceBtn = new QPushButton("Check Balance");
    QPushButton *showBtn = new QPushButton("Show All Accounts");

    outputBox = new QTextEdit();
    outputBox->setReadOnly(true);

    layout->addWidget(title);
    layout->addWidget(accInput);
    layout->addWidget(nameInput);
    layout->addWidget(amountInput);
    layout->addWidget(createBtn);
    layout->addWidget(depositBtn);
    layout->addWidget(withdrawBtn);
    layout->addWidget(balanceBtn);
    layout->addWidget(showBtn);
    layout->addWidget(outputBox);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(createBtn, &QPushButton::clicked, this, &MainWindow::createAccount);
    connect(depositBtn, &QPushButton::clicked, this, &MainWindow::depositMoney);
    connect(withdrawBtn, &QPushButton::clicked, this, &MainWindow::withdrawMoney);
    connect(balanceBtn, &QPushButton::clicked, this, &MainWindow::checkBalance);
    connect(showBtn, &QPushButton::clicked, this, &MainWindow::showAllAccounts);

    loadAccounts();
}

void MainWindow::loadAccounts() {
    QFile file("accounts.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        accounts.append(BankAccount::fromFileString(line));
    }

    file.close();
}

void MainWindow::saveAccounts() {
    QFile file("accounts.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    for (BankAccount acc : accounts) {
        out << acc.toFileString() << "\n";
    }

    file.close();
}

int MainWindow::findAccount(int accNo) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].accountNumber == accNo) {
            return i;
        }
    }
    return -1;
}

void MainWindow::createAccount() {
    int accNo = accInput->text().toInt();
    QString name = nameInput->text();
    double balance = amountInput->text().toDouble();

    if (accNo == 0 || name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter valid account details.");
        return;
    }

    if (findAccount(accNo) != -1) {
        QMessageBox::warning(this, "Error", "Account already exists.");
        return;
    }

    accounts.append(BankAccount(accNo, name, balance));
    saveAccounts();

    outputBox->setText("Account created successfully!");
}

void MainWindow::depositMoney() {
    int accNo = accInput->text().toInt();
    double amount = amountInput->text().toDouble();

    int index = findAccount(accNo);

    if (index == -1) {
        QMessageBox::warning(this, "Error", "Account not found.");
        return;
    }

    accounts[index].balance += amount;
    saveAccounts();

    outputBox->setText("Amount deposited successfully!\nNew Balance: " +
                       QString::number(accounts[index].balance));
}

void MainWindow::withdrawMoney() {
    int accNo = accInput->text().toInt();
    double amount = amountInput->text().toDouble();

    int index = findAccount(accNo);

    if (index == -1) {
        QMessageBox::warning(this, "Error", "Account not found.");
        return;
    }

    if (amount > accounts[index].balance) {
        QMessageBox::warning(this, "Error", "Insufficient balance.");
        return;
    }

    accounts[index].balance -= amount;
    saveAccounts();

    outputBox->setText("Amount withdrawn successfully!\nNew Balance: " +
                       QString::number(accounts[index].balance));
}

void MainWindow::checkBalance() {
    int accNo = accInput->text().toInt();

    int index = findAccount(accNo);

    if (index == -1) {
        QMessageBox::warning(this, "Error", "Account not found.");
        return;
    }

    outputBox->setText(
        "Account Number: " + QString::number(accounts[index].accountNumber) +
        "\nName: " + accounts[index].name +
        "\nBalance: " + QString::number(accounts[index].balance)
    );
}

void MainWindow::showAllAccounts() {
    QString result = "All Bank Accounts:\n\n";

    for (BankAccount acc : accounts) {
        result += "Account No: " + QString::number(acc.accountNumber) +
                  "\nName: " + acc.name +
                  "\nBalance: " + QString::number(acc.balance) +
                  "\n----------------------\n";
    }

    outputBox->setText(result);
}