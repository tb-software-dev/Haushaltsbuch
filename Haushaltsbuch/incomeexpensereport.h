#pragma once

#include "reportgenerator.h"
#include "transactioncontroller.h"
#include <QLabel>

// Klasse zur Erstellung von Berichten , die einen Überblick über Einnahmen und Ausgaben geben
class IncomeExpenseReport : public ReportGenerator
{
public:
	// Konstruktor
	explicit IncomeExpenseReport(TransactionController* transactionController);

	void generateReport(QWidget* container, const QDate& startDate, const QDate& endDate) override;


private:
	TransactionController* m_transactionController;


};
