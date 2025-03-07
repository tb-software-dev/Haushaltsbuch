#include "budgetcontroller.h"

// Konstruktor
BudgetController::BudgetController(Database* database) : m_database(database)
{
	// Die Budgetdaten aus der Datenbank laden
	m_budget = m_database->getBudget();
}

// Festlegen des Budgets einer Kategorie und speichern in der Datenbank
bool BudgetController::setBudget(const QString& category, double amount)
{
	// Festlegen des Budget Betrags
	m_budget.setBudget(category, amount);

	// In der Datenbank speichern
	return m_database->saveBudget(m_budget);
}

double BudgetController::getBudget(const QString& category) const
{
	// Abrufen des Budgets für eine bestimmte Kategorie
	return m_budget.getBudget(category);
}

// Berechnet die aktuellen Ausgaben einer Kategorie in einem bestimmten Zeitraum
double BudgetController::getCurrentSpending(const QString& category, const QDate& startDate, const QDate& endDate)
{
	// Var
	double spending = 0.0;

	//

	// Transaktionen aus der Datenbank für den festgelegten Zeitraum abrufen
	QList<Transaction> transactions = m_database->getTransactions(startDate, endDate);

	// Loop durch alle Transaktionen
	for (const Transaction& transaction : transactions)
	{
		// Nur die relevanten Ausgaben berücksichtigen
		if (transaction.type() == Transaction::Expense &&
			transaction.category() == category)
		{
			spending += transaction.amount(); // Betrag hinzufügen
		}
	}

	return spending;
}

bool BudgetController::isOverBudget(const QString& category, const QDate& startDate, const QDate& endDate)
{
	// Aktuelle Ausgaben berechnen
	double currentSpending = getCurrentSpending(category, startDate, endDate);

	// Prüfen, ob Ausgaben das Budget überschreiten
	return m_budget.isOverBudget(category, currentSpending);
}

double BudgetController::getRemainingBudget(const QString& category, const QDate& startDate, const QDate& endDate)
{
	// Aktuelle Ausgaben berechnen
	double currentSpending = getCurrentSpending(category, startDate, endDate);

	// Verbleibendes Budget berechnen
	return m_budget.getRemainingBudget(category, currentSpending);
}

QStringList BudgetController::getCategories() const
{
	// Abrufen aller Budget-Kategorien
	return m_budget.getCategories();
}

QMap<QString, double> BudgetController::getAllBudgets() const
{
	QMap<QString, double> result;

	// Alle Kategorien abrufen
	QStringList categories = getCategories();

	// Loop durch jede Kategorie und das Budget in der Map speichern
	for (const QString& category : categories)
	{
		result[category] = getBudget(category);
	}

	return result;
}