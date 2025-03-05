#pragma once

#include <QSqlDatabase>
#include <QList>
#include "transactions.h"
#include "budget.h"
#include "Account.h"

class Database
{
public:

	Database();
	~Database();

	// Datenbank-Initialisierung
	bool initialize();

	// Transaktionsfunktionen
	bool saveTransaction(Transaction& transaction);
	bool updateTransaction(const Transaction& transaction);
	bool deleteTransaction(int id);
	QList<Transaction> getTransactions(const QDate& startDate, const QDate& endDate);

	// Budget-Funktionen
	bool saveBudget(const Budget& budget);
	Budget getBudget();

	// Konto-Funktionen
	bool saveAccount(Account& account);
	QList<Account> getAccounts();


private:

	QSqlDatabase m_db;

	// Hilfsfunktionen zur Erstellung der Datenbanktabellen
	bool createTransactionsTable();
	bool createBudgetsTable();
	bool createAccountsTable();



};
