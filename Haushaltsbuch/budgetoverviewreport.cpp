#include "budgetoverviewreport.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QProgressBar>
#include <QChart>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QFont>


// Konstruktor
BudgetOverviewReport::BudgetOverviewReport(TransactionController* transactionController,
										   BudgetController* budgetController)
					: m_transactionController(transactionController),
						m_budgetController(budgetController)
{

}

void BudgetOverviewReport::generateReport(QWidget* container, const QDate& startDate, const QDate& endDate)
{
	QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(container->layout());

	// Titel hinzufügen
	QLabel* titleLabel = new QLabel(QObject::tr("Budget-Übersicht"), container);
	titleLabel->setAlignment(Qt::AlignCenter);
	QFont titleFont;
	titleFont.setPointSize(14);
	titleFont.setBold(true);
	titleLabel->setFont(titleFont);
	layout->addWidget(titleLabel);

	// Zeitraum-Label
	QLabel* dateRangeLabel = new QLabel(
		QObject::tr("Zeitraum: %1 - %2")
		.arg(startDate.toString("dd.MM.yyyy"))
		.arg(endDate.toString("dd.MM.yyyy")),
		container);
	dateRangeLabel->setAlignment(Qt::AlignCenter);
	layout->addWidget(dateRangeLabel);

	// Budget-Daten laden
	QMap<QString, double> budgets = m_budgetController->getAllBudgets();

	// Prüfen , ob Daten vorhanden sind
	if (budgets.isEmpty())
	{
		QLabel* noDataLabel = new QLabel(QObject::tr("Keine Budgets definiert."), container);
		noDataLabel->setAlignment(Qt::AlignCenter);
		layout->addWidget(noDataLabel);

		return;
	}


	// Tabelle erstellen
	QTableWidget* table = new QTableWidget(container);
	table->setColumnCount(5);
	table->setHorizontalHeaderLabels(
		QStringList() << QObject::tr("Kategorie") << QObject::tr("Budget") << QObject::tr("Ausgegeben")
		<< QObject::tr("Verbleibend") << QObject::tr("Fortschritt"));
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->verticalHeader()->setVisible(false);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setAlternatingRowColors(true);

	// Zeilen hinzufügen
	table->setRowCount(budgets.size());
	int row = 0;

	// Daten für dass Balkendiagramm
	QBarSet* budgetSet = new QBarSet(QObject::tr("Budget"));
	QBarSet* spentSet = new QBarSet(QObject::tr("Ausgegeben"));
	QStringList categories;

	for (auto it = budgets.begin(); it != budgets.end(); it++)
	{
		QString category = it.key();
		double budgetAmount = it.value();

		// Aktuelle Ausgaben für diese Kategorie berechnen
		double currentSpending = m_budgetController->getCurrentSpending(category, startDate, endDate);
		double remainingBudget = budgetAmount - currentSpending;
		double percentage = (currentSpending / budgetAmount) * 100;

		// Kategorie
		QTableWidgetItem* categoryItem = new QTableWidgetItem(category);
		table->setItem(row, 0, categoryItem);

		// Budget
		QTableWidgetItem* budgetItem = new QTableWidgetItem(QString("%1 €").arg(budgetAmount, 0, 'f', 2));
		budgetItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		table->setItem(row, 1, budgetItem);

		// Ausgegeben 
		QTableWidgetItem* spentItem = new QTableWidgetItem(QString("%1 €").arg(currentSpending, 0, 'f', 2));
		spentItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		table->setItem(row, 2, spentItem);

		// Verbleibend
		QTableWidgetItem* remainingItem = new QTableWidgetItem(QString("%1 €").arg(remainingBudget, 0, 'f', 2));
		remainingItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		remainingItem->setForeground(remainingBudget < 0 ? QColor(255, 0, 0) : QColor(0, 128, 0));
		table->setItem(row, 3, remainingItem);

		// Fortschrittsbalken
		QProgressBar* progressBar = new QProgressBar(container);
		progressBar->setRange(0, 100);
		progressBar->setValue(qMin(static_cast<int>(percentage), 100));
		progressBar->setFormat("%p%");
		progressBar->setTextVisible(true);

		// Farbe basierend auf dem  Budget-Status
		if (currentSpending > budgetAmount)
		{
			// Rot bei OverBudget
			progressBar->setStyleSheet("QProgressBar::chunk {background-color: #ff0000; }");
		}
		else if (percentage >= 90)
		{
			// Orange 90 %
			progressBar->setStyleSheet("QProgressBar::chunk { background-color: #ffa500; }");
		}
		else
		{
			// Alles im Grünen Bereich
			progressBar->setStyleSheet("QProgressBar::chunk { background-color: #00b050; }");
		}

		table->setCellWidget(row, 4, progressBar);

		// Daten für das Diagramm
		budgetSet->append(budgetAmount);
		spentSet->append(currentSpending);
		categories << category;

		row++;
	}

	layout->addWidget(table);

	// Balkendiagramm erstellen
	QChart* chart = new QChart();
	chart->setTitle(QObject::tr("Budget vs. Ausgaben pro Kategorie"));
	chart->setAnimationOptions(QChart::SeriesAnimations);

	QBarSeries* series = new QBarSeries();
	series->append(budgetSet);
	series->append(spentSet);

	chart->addSeries(series);

	// Axis
	QBarCategoryAxis* axisX = new QBarCategoryAxis();
	axisX->append(categories);
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	QValueAxis* axisY = new QValueAxis();
	double maxValue = 0;

	for (auto it = budgets.begin(); it != budgets.end(); it++)
	{
		double budgetAmount = it.value();
		double currentSpending = m_budgetController->getCurrentSpending(it.key(), startDate, endDate);
		maxValue = qMax(maxValue, qMax(budgetAmount, currentSpending));
	}

	axisY->setRange(0, maxValue * 1.1);
	axisY->setLabelFormat("%d €");
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	// Legend Config
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	// Chart-View erstellen und hinzufügen
	QChartView* chartView = new QChartView(chart, container);
	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->setMinimumHeight(400);

	layout->addWidget(chartView);

	// Hinweis für die Budgetverwaltung
	QLabel* noteLabel = new QLabel(
		QObject::tr("Tipp: Nutzen Sie den Budget-Tab, um Budget-Limits für Kategorien anzupassen."),
		container);
	noteLabel->setAlignment(Qt::AlignCenter);
	noteLabel->setStyleSheet("color: gray; font-style: italic;");
	layout->addWidget(noteLabel);

	// Abstand am Ende hinzufügen
	layout->addStretch();







}