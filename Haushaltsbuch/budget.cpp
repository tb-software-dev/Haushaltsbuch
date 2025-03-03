#include "budget.h"

Budget::Budget()
{

}

double Budget::getBudget(const QString& category) const
{
	return m_budgets.value(category, 0.0);
}

void Budget::setBudget(const QString& category, double amount)
{
	m_budgets[category] = amount;
}

bool Budget::isOverBudget(const QString& category, double currentSpent) const
{
	double budget = getBudget(category);
	return currentSpent > budget && budget > 0;
}

double Budget::getRemainingBudget(const QString& category, double currentSpent) const
{
	return getBudget(category) - currentSpent;
}

QStringList Budget::getCategories() const
{
	return m_budgets.keys();
}