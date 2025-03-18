#include "budgettab.h"
#include "budgetdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include "currencyformatter.h"

// Konstruktor
BudgetTab::BudgetTab(BudgetController* budgetController, QWidget* parent)
	: QWidget(parent), m_budgetController(budgetController)
{
	setupUi();
	updateBudgetTable();
}

void BudgetTab::setupUi()
{
	QVBoxLayout* layout = new QVBoxLayout(this);

	// BudgetTabelle
	m_budgetModel = new QStandardItemModel(this);
	m_budgetModel->setHorizontalHeaderLabels(
		QStringList() << tr("Kategorie") << tr("Budget") << tr("Ausgegeben")
		<< tr("Verbleibend") << tr("Status"));

	m_budgetTable = new QTableView();
	m_budgetTable->setModel(m_budgetModel);
	m_budgetTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_budgetTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_budgetTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_budgetTable->verticalHeader()->setVisible(false);

	layout->addWidget(m_budgetTable);

	// Aktionsbuttons
	QHBoxLayout* buttonsLayout = new QHBoxLayout();
	m_addBudgetButton = new QPushButton(QString::fromUtf8("Neues Budget"));
	m_editBudgetButton = new QPushButton(QString::fromUtf8("Bearbeiten"));

	buttonsLayout->addWidget(m_addBudgetButton);
	buttonsLayout->addWidget(m_editBudgetButton);
	buttonsLayout->addStretch();

	layout->addLayout(buttonsLayout);

	// Verbindungen herstellen
	connect(m_addBudgetButton, &QPushButton::clicked, this, &BudgetTab::onAddBudget);
	connect(m_editBudgetButton, &QPushButton::clicked, this, &BudgetTab::onEditBudget);
}

void BudgetTab::updateBudgetTable()
{
	// Tabelle leeren
	m_budgetModel->removeRows(0, m_budgetModel->rowCount());

	// Aktuelles Datum für den Monatszeitraum
	QDate startDate = QDate(QDate::currentDate().year(), QDate::currentDate().month(), 1);
	QDate endDate = startDate.addMonths(1).addDays(-1);

	// Budget-Daten laden
	QMap<QString, double> budgets = m_budgetController->getAllBudgets();

	// Budgets in die Tabelle einfügen
	for (auto it = budgets.begin(); it != budgets.end(); it++)
	{
		QString category = it.key();
		double budgetAmount = it.value();

		// Aktuelle Ausgaben für diese Kategorie berechnen
		double currentSpending = m_budgetController->getCurrentSpending(category, startDate, endDate);
		double remainingBudget = budgetAmount - currentSpending;
		bool isOverBudget = remainingBudget < 0;

		QList<QStandardItem*> row;

		// Kategorie
		QStandardItem* categoryItem = new QStandardItem(category);
		row.append(categoryItem);

		// Budget
		QStandardItem* budgetItem = new QStandardItem(
			CurrencyFormatter::formatCurrency(budgetAmount));
		budgetItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		row.append(budgetItem);

		// Ausgegeben
		QStandardItem* spentItem = new QStandardItem(
			CurrencyFormatter::formatCurrency(currentSpending));
		spentItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		row.append(spentItem);

		// Verbleibend
		QStandardItem* remainingItem = new QStandardItem(
			CurrencyFormatter::formatCurrency(remainingBudget));
		remainingItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		remainingItem->setForeground(isOverBudget ? QColor(255, 0, 0) : QColor(0, 128, 0));
		row.append(remainingItem);

		// Status
		QStandardItem* statusItem = new QStandardItem();

		if (isOverBudget)
		{
			statusItem->setText(tr("Überschritten"));
			statusItem->setForeground(QColor(255, 0, 0));
		}
		else
		{
			// Prozentsatz berechnen
			double percentage = (currentSpending / budgetAmount) * 100;

			if (percentage >= 90)
			{
				statusItem->setText(tr("Fast erschöpft"));
				statusItem->setForeground(QColor(255, 165, 0));		// Orange
			}
			else if (percentage >= 75)
			{
				statusItem->setText(tr("Achtung"));
				statusItem->setForeground(QColor(255, 165, 0));		// Orange
			}
			else
			{
				statusItem->setText(tr("OK"));
				statusItem->setForeground(QColor(0, 128, 0));		// Grün
			}
		}
		row.append(statusItem);

		// Zeile hinzufügen
		m_budgetModel->appendRow(row);

	}

	// Budget-Änderung signalisieren 
	emit budgetChanged();

}

void BudgetTab::showBudgetDialog(const QString& category, double amount)
{
	// Dialog erstellen
	BudgetDialog dialog(this);

	// Kategorien aus vorhandenen Kategorien laden
	// Platzhalter
	QStringList allCategories = m_budgetController->getCategories();

	// Budget Daten setzen
	if (!category.isEmpty())
	{
		dialog.setCategory(category);
		dialog.setAmount(amount);
	}

	// Dialog anzeigen
	if (dialog.exec() == QDialog::Accepted)
	{
		QString newCategory = dialog.getCategory();
		double newAmount = dialog.getAmount();

		// Budget speichern
		if (m_budgetController->setBudget(newCategory, newAmount))
		{
			QMessageBox::information(this, tr("Erfolg"),
				tr("Das Budget wurde erfolgreich gespeichert."));

			// Daten aktualisieren
			updateBudgetTable();
		}
		else
		{
			QMessageBox::warning(this, tr("Fehler"),
				tr("Das Budget konnte nicht gespeichert werden."));
		}
	}
}

void BudgetTab::onAddBudget()
{
	showBudgetDialog();
}

void BudgetTab::onEditBudget()
{
	// Ausgewählte Zeile ermitteln
	QModelIndexList selection = m_budgetTable->selectionModel()->selectedRows();

	if (selection.isEmpty())
	{
		QMessageBox::information(this, tr("Hinweis"),
			tr("Bitte wählen Sie ein Budget aus."));

		return;
	}

	// Budget-Daten abrufen
	int row = selection.first().row();
	QString category = m_budgetModel->item(row, 0)->text();
	QString budgetText = m_budgetModel->item(row, 1)->text();
	double amount = budgetText.replace(" €", "").replace(",", ".").toDouble();

	// Budget-Dialog anzeigen
	showBudgetDialog(category, amount);


}