#pragma once

#include <QMap>
#include <QDate>
#include "budget.h"
#include "database.h"

class BudgetController
{
public:

	// Konstruktor
	BudgetController(Database* database);

	// Budget verwalten
	bool setBudget(const QString& category, double amount);
	double getBudget(const QString& category) const;

	// Budget-Status abfragen
	double getCurrentSpending(const QString& category, const QDate& startDate, const QDate& endDate);
	bool isOverBudget(const QString& category, const QDate& startDate, const QDate& endDate);
	double getRemainingBudget(const QString& category, const QDate& startDate, const QDate& endDate);

	// Kategorien verwalten
	QStringList getCategories() const;
	QMap<QString, double> getAllBudgets() const;

private:

	Database* m_database;
	Budget m_budget;

};