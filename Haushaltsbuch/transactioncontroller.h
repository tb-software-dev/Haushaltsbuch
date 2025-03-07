#pragma once

#include <QList>
#include <QDate>
#include "transactions.h"
#include "database.h"

class TransactionController
{
public:

	// Konstruktor
	TransactionController(Database* database);

	// Transaktionen verwalten
	bool addTransaction(Transaction& transaction);
	bool updateTransaction(const Transaction& transaction);
	bool deleteTransaction(int id);

	// Transaktionen abfragen
	QList<Transaction> getTransactions(const QDate& startDate, const QDate& endDate);

	// Statistik und Berichte
	double getTotalIncome(const QDate& startDate, const QDate& endDate);
	double getTotalExpense(const QDate& startDate, const QDate& endDate);
	double getBalance(const QDate& startDate, const QDate& endDate);
	QMap<QString, double> getExpensesByCategory(const QDate& startDate, const QDate& endDate);

private:

	Database* m_database;

};
