#pragma once

#include "reportgenerator.h"
#include "transactioncontroller.h"
#include "budgetcontroller.h"

class BudgetOverviewReport : public ReportGenerator
{

public:
	//
	explicit BudgetOverviewReport(TransactionController* transactionController, BudgetController* budgetController);

	void generateReport(QWidget* container, const QDate& startDate, const QDate& endDate) override;

private:

	TransactionController* m_transactionController;
	BudgetController* m_budgetController;


};
