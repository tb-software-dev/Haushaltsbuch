#pragma once

#include <QWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QScrollArea>
#include "transactioncontroller.h"
#include "budgetcontroller.h"
#include "reportgenerator.h"

class ReportsTab : public QWidget
{
	Q_OBJECT

public:
	// Konstruktor
	explicit ReportsTab(TransactionController* transactionController,
						BudgetController* budgetController,
						QWidget* parent = nullptr);


	// Destruktor
	~ReportsTab();

private slots:
	// Wird aufgerufen wenn der Bericht erstellen- Button geclickt wird
	void onGenerateReport();

private:
	// UI-Komponenten
	QComboBox* m_reportTypeComboBox;				// Auswahl des Typs
	QDateEdit* m_startDateEdit;
	QDateEdit* m_endDateEdit;
	QPushButton* m_generateReportButton;
	QWidget* m_reportContainer;
	QScrollArea* m_scrollArea;

	// Controller
	TransactionController* m_transactionController;
	BudgetController* m_budgetController;

	// Report-Generatoren
	QList<ReportGenerator*> m_reportGenerators;

	// Initialisiert die Benutzeroberfläche
	void setupUi();

	// Leert den Berichtscontainer
	void clearReportContainer();

};
