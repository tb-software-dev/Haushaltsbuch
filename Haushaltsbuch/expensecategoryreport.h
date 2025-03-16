#pragma once

#include "reportgenerator.h"
#include "transactioncontroller.h"

class ExpenseCategoryReport : public ReportGenerator
{

public:
	//
	explicit ExpenseCategoryReport(TransactionController* transactionController);

	void generateReport(QWidget* container, const QDate& startDate, const QDate& endDate) override;

private:
	TransactionController* m_transactionController;


};
