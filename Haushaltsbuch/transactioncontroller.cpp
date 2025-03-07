#include "transactioncontroller.h"

// Konstruktor
TransactionController::TransactionController(Database* database) :
	m_database(database)
{

}

// Transaktion hinzufügen & und in der Datenbank speichern
bool TransactionController::addTransaction(Transaction& transaction)
{
	return m_database->saveTransaction(transaction);
}

// Transaktion in der DB aktualisieren
bool TransactionController::updateTransaction(const Transaction& transaction)
{
	return m_database->updateTransaction(transaction);
}

// Löschen einer Transaktion anhand der ID
bool TransactionController::deleteTransaction(int id)
{
	return m_database->deleteTransaction(id);
}

// Abrufen der Transaktionen in einen bestimmten Zeitfenster
QList<Transaction> TransactionController::getTransactions(const QDate& startDate, const QDate& endDate)
{
	return m_database->getTransactions(startDate, endDate);
}

// Berechnen der Gesamteinnahmen im angegebenen Zeitraum
double TransactionController::getTotalIncome(const QDate& startDate, const QDate& endDate)
{
	// var
	double total = 0.0;

	//

	QList<Transaction> transactions = getTransactions(startDate, endDate);

	// Loop durch alle Transaktionen und berücksichtigt nur die Einnahmen
	for (const Transaction& transaction : transactions)
	{
		if (transaction.type() == Transaction::Income)
		{
			total += transaction.amount();
		}
	}

	return total;
}

// Berechnen der Gesamtausgaben im angegebenen Zeitraum
double TransactionController::getTotalExpense(const QDate& startDate, const QDate& endDate)
{
	//
	double total = 0.0;
	//

	QList<Transaction> transactions = getTransactions(startDate, endDate);
	

	
	for (const Transaction& transaction : transactions)
	{
		if (transaction.type() == Transaction::Expense)
		{
			total += transaction.amount();
		}
	}
	return total;
}

// Berechnet die Bilanz (Saldo) = Einnahmen - Ausgaben
double TransactionController::getBalance(const QDate& startDate, const QDate& endDate)
{
	return getTotalIncome(startDate, endDate) - getTotalExpense(startDate, endDate);
}

// Listet die Gesamtausgaben nach Kategorien auf
QMap<QString, double> TransactionController::getExpensesByCategory(const QDate& startDate, const QDate& endDate)
{
	QList<Transaction> transactions = getTransactions(startDate, endDate);
	QMap<QString, double> result;

	// Iteriert über alle Transaktionen und summiert die Ausgaben pro Kategorie
	for (const Transaction& transaction : transactions)
	{
		if (transaction.type() == Transaction::Expense)
		{
			QString category = transaction.category();
			result[category] = result.value(category, 0.0) + transaction.amount();
		}
	}
	return result;
}


