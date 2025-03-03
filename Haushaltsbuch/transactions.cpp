#include "transactions.h"


Transaction::Transaction() : m_id(-1), m_type(Expense), m_amount(0.0)

{
	m_date = QDate::currentDate();
}

Transaction::Transaction(Type type, const QDate& date, double amount,
	const QString& category, const QString& description)
	: m_id(-1), m_type(type), m_date(date), m_amount(amount),
	m_category(category), m_description(description)
{


}