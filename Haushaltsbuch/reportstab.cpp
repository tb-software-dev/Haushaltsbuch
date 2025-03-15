#include "reportstab.h"
#include "incomeexpensereport.h"
#include "expensecategoryreport.h"
#include "budgetoverviewreport.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>

ReportsTab::ReportsTab(TransactionController* transactionController,
						BudgetController* budgetController,
						QWidget* parent)
	: QWidget(parent), m_transactionController(transactionController),
	m_budgetController(budgetController)
{
	setupUi();

	// Report-Generatoren erstellen
	m_reportGenerators.append(new IncomeExpenseReport(m_transactionController));
	m_reportGenerators.append(new ExpenseCategoryReport(m_transactionController));
	m_reportGenerators.append(new BudgetOverviewReport(m_transactionController, m_budgetController));


}

// Destruktor
ReportsTab::~ReportsTab()
{
	// Report-Generatoren freigeben
	qDeleteAll(m_reportGenerators);
	m_reportGenerators.clear();
}

void ReportsTab::setupUi()
{
	QVBoxLayout* layout = new QVBoxLayout(this);

	// Report-Konfiguration
	QGroupBox* configGroup = new QGroupBox(tr("Berichtseinstellungen"));
	QHBoxLayout* configLayout = new QHBoxLayout(configGroup);

	QLabel* reportTypeLabel = new QLabel(tr("Berichtstyp:"));
	m_reportTypeComboBox = new QComboBox();
	m_reportTypeComboBox->addItem(tr("Einnahmen/Ausgaben"));
	m_reportTypeComboBox->addItem(tr("Ausgaben nach Kategorie"));
	m_reportTypeComboBox->addItem(tr("Budget-Übersicht"));

	QLabel* startDateLabel = new QLabel(tr("Von:"));
	m_startDateEdit = new QDateEdit();
	m_startDateEdit->setCalendarPopup(true);
	m_startDateEdit->setDate(QDate::currentDate().addMonths(-1));

	QLabel* endDateLabel = new QLabel(tr("Bis:"));
	m_endDateEdit = new QDateEdit();
	m_endDateEdit->setCalendarPopup(true);
	m_endDateEdit->setDate(QDate::currentDate());

	m_generateReportButton = new QPushButton(tr("Bericht erstellen"));

	configLayout->addWidget(reportTypeLabel);
	configLayout->addWidget(m_reportTypeComboBox);
	configLayout->addWidget(startDateLabel);
	configLayout->addWidget(m_startDateEdit);
	configLayout->addWidget(endDateLabel);
	configLayout->addWidget(m_endDateEdit);
	configLayout->addWidget(m_generateReportButton);
	configLayout->addStretch();

	layout->addWidget(configGroup);

	// Report-Anzeige
	m_reportContainer = new QWidget();
	QVBoxLayout* containerLayout = new QVBoxLayout(m_reportContainer);

	// Platzhaltertext
	QLabel* placeholderLabel = new QLabel(tr("Bitte wählen Sie einen Berichtstyp und klicken sie auf 'Bericht erstellen'."));
	placeholderLabel->setAlignment(Qt::AlignCenter);
	containerLayout->addWidget(placeholderLabel);

	// Scrollbereich für den Bericht
	m_scrollArea = new QScrollArea();
	m_scrollArea->setWidgetResizable(true);
	m_scrollArea->setWidget(m_reportContainer);

	layout->addWidget(m_scrollArea);

	// Verbindung herstellen
	connect(m_generateReportButton, &QPushButton::clicked, this, &ReportsTab::onGenerateReport);
}

void ReportsTab::clearReportContainer()
{
	// Bericht-Container leeren
	QLayout* layout = m_reportContainer->layout();
	QLayoutItem* item;

	while ((item = layout->takeAt(0)) != nullptr)
	{
		if (item->widget())
		{
			delete item->widget();
		}
		delete item;
	}
}

void ReportsTab::onGenerateReport()
{
	clearReportContainer();

	// Berichtstyp und Zeitraum ermitteln
	int reportType = m_reportTypeComboBox->currentIndex();
	QDate startDate = m_startDateEdit->date();
	QDate endDate = m_endDateEdit->date();

	// Sicherstellen, dass der Berichtstyp gültig ist
	if (reportType >= 0 && reportType < m_reportGenerators.size())
	{
		// Bericht generieren
		m_reportGenerators[reportType]->generateReport(
			m_reportContainer, startDate, endDate);
	}
}