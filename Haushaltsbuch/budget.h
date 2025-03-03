#pragma once

#include <QString>
#include <QMap>

class Budget
{

public:

	Budget();

	// Getter und Setter für Kategorie-Budgets
	double getBudget(const QString& category) const;
	void   setBudget(const QString& category, double amount);

	// Budget-Limit Überprüfung
	bool isOverBudget(const QString& category, double currentSpent) const;
	double getRemainingBudget(const QString& category, double currentSpent) const;

	// Alle Budgetkategorien abrufen
	QStringList getCategories() const;


private:
	QMap<QString, double> m_budgets;	// Speichert das Budget von jeder Kategorie in einer Map



};
