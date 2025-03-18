#include "transactionstab.h"
#include "transactiondialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QHeaderView>
#include <QMessageBox>

TransactionsTab::TransactionsTab(TransactionController* transactionController, QWidget* parent)
	: QWidget(parent), m_transactionController(transactionController)
{
	setupUi();
	updateTransactionTable();
}

void TransactionsTab::setupUi()
{
	QVBoxLayout* layout = new QVBoxLayout(this);

	// Datumbereichsauswahl
	QGroupBox* dateRangeGroup = new QGroupBox(tr("Zeitraum"));
	QHBoxLayout* dateRangeLayout = new QHBoxLayout(dateRangeGroup);

	QLabel* startDateLabel = new QLabel(tr("Von:"));
	m_startDateEdit = new QDateEdit();
	m_startDateEdit->setCalendarPopup(true);
	m_startDateEdit->setDate(QDate::currentDate().addMonths(-1));

	QLabel* endDateLabel = new QLabel(tr("Bis:"));
	m_endDateEdit = new QDateEdit();
	m_endDateEdit->setCalendarPopup(true);
	m_endDateEdit->setDate(QDate::currentDate());

	QPushButton* filterButton = new QPushButton(tr("Filtern"));

	dateRangeLayout->addWidget(startDateLabel);
	dateRangeLayout->addWidget(m_startDateEdit);
	dateRangeLayout->addWidget(endDateLabel);
	dateRangeLayout->addWidget(m_endDateEdit);
	dateRangeLayout->addWidget(filterButton);
	dateRangeLayout->addStretch();

	layout->addWidget(dateRangeGroup);

	// Transaktionen- Table
	m_transactionsModel = new QStandardItemModel(this);
	m_transactionsModel->setHorizontalHeaderLabels(
		QStringList() << tr("ID") << tr("Datum") << tr("Typ") << tr("Kategorie")
		<< tr("Beschreibung") << tr("Betrag"));

	m_transactionsTable = new QTableView();
	m_transactionsTable->setModel(m_transactionsModel);
	m_transactionsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_transactionsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_transactionsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_transactionsTable->verticalHeader()->setVisible(false);
	m_transactionsTable->setSortingEnabled(true);

	layout->addWidget(m_transactionsTable);

	// Aktionsbuttons
	QHBoxLayout* buttonsLayout = new QHBoxLayout();
	m_addTransactionButton = new QPushButton(QString::fromUtf8("Neue Transaktion"));
	m_editTransactionButton = new QPushButton(QString::fromUtf8("Bearbeiten"));
	m_deleteTransactionButton = new QPushButton(QString::fromUtf8("Entfernen"));

	buttonsLayout->addWidget(m_addTransactionButton);
	buttonsLayout->addWidget(m_editTransactionButton);
	buttonsLayout->addWidget(m_deleteTransactionButton);
	buttonsLayout->addStretch();

	layout->addLayout(buttonsLayout);

	// Verbindungen herstellen
	connect(filterButton, &QPushButton::clicked, this, &TransactionsTab::onFilterTransactions);
	connect(m_startDateEdit, &QDateTimeEdit::dateChanged, this, &TransactionsTab::onDateRangeChanged);
	connect(m_endDateEdit, &QDateEdit::dateChanged, this, &TransactionsTab::onDateRangeChanged);
	connect(m_addTransactionButton, &QPushButton::clicked, this, &TransactionsTab::onAddTransaction);
	connect(m_editTransactionButton, &QPushButton::clicked, this, &TransactionsTab::onEditTransaction);
	connect(m_deleteTransactionButton, &QPushButton::clicked, this, &TransactionsTab::onDeleteTransaction);
}

void TransactionsTab::updateTransactionTable()
{
	// Tabelle leeren
	m_transactionsModel->removeRows(0, m_transactionsModel->rowCount());

	// Transaktionen für den ausgewählten Zeitraum laden
	QList<Transaction> transactions = m_transactionController->getTransactions(
		m_startDateEdit->date(), m_endDateEdit->date());

	// Transaktionen in die Tabelle einfügen
	for (const Transaction& transaction : transactions)
	{
		QList<QStandardItem*> row;

		// ID
		QStandardItem* idItem = new QStandardItem(QString::number(transaction.id()));
		row.append(idItem);

		// Datum
		QStandardItem* dateItem = new QStandardItem(transaction.date().toString("dd.MM.yyyy"));
		row.append(dateItem);

		// Typ
		QStandardItem* typeItem = new QStandardItem(
			transaction.type() == Transaction::Income ? tr("Einnahme") : tr("Ausgabe"));
		typeItem->setForeground(
			transaction.type() == Transaction::Income ? QColor(0, 128, 0) : QColor(128, 0, 0));
		row.append(typeItem);

		// Kategorie
		QStandardItem* categoryItem = new QStandardItem(transaction.category());
		row.append(categoryItem);

		// Beschreibung
		QStandardItem* descriptionItem = new QStandardItem(transaction.description());
		row.append(descriptionItem);

		// Betrag
		QStandardItem* amountItem = new QStandardItem(
			QString("%1 \u20AC").arg(transaction.amount(), 0, 'f', 2));
		amountItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		row.append(amountItem);

		// Zeile hinzufügen
		m_transactionsModel->appendRow(row);

	}

	// Status-Änderung signalisieren
	emit statusChanged();

}

void TransactionsTab::showTransactionDialog(const Transaction& transaction)
{
	// Dialog erstellen
	TransactionDialog dialog(this);

	// Kategorien laden
	QStringList categories;
	dialog.setCategories(categories);

	// Bei Bearbeitung die Transaktionsdaten setzen
	if (transaction.id() != -1)
	{
		dialog.setTransaction(transaction);
	}

	// Dialog anzeigen
	if (dialog.exec() == QDialog::Accepted)
	{
		Transaction newTransaction = dialog.getTransaction();

		// Transaktion speichern oder aktualisieren
		if (newTransaction.id() == -1)
		{
			// Neue Transaktion
			if (m_transactionController->addTransaction(newTransaction))
			{
				QMessageBox::information(this, tr("Erfolg"),
					tr("Die Transaktion wurde erfolgreich hinzugefügt."));
			}
			else
			{
				QMessageBox::warning(this, tr("Fehler"),
					tr("Die Transaktion konnte nicht gespeichert werden."));
			}
		}

		else
		{
			// Vorhandene Transaktion aktualisieren
			if (m_transactionController->updateTransaction(newTransaction))
			{
				QMessageBox::information(this, tr("Erfolg"),
					tr("Die Transaktion wurde erfolgreich aktualisiert."));
			}
			else
			{
				QMessageBox::warning(this, tr("Fehler"),
					tr("Die Transaktion konnte nicht aktualisiert werden."));
			}
		}

		// Daten aktualisieren
		updateTransactionTable();
	}
}

void TransactionsTab::onAddTransaction()
{
	showTransactionDialog();
}

void TransactionsTab::onEditTransaction()
{
	// Ausgewählte Zeile ermitteln
	QModelIndexList selection = m_transactionsTable->selectionModel()->selectedRows();

	if (selection.isEmpty())
	{
		QMessageBox::information(this, tr("Hinweis"),
			tr("Bitte wählen sie eine Transaktion aus."));

		return;
	}

	// Transaktion aus der Tabelle abrufen
	int row = selection.first().row();
	int id = m_transactionsModel->item(row, 0)->text().toInt();

	// Alle Transaktionen abrufen und die gesuchte finden
	QList<Transaction> transactions = m_transactionController->getTransactions(
		m_startDateEdit->date(), m_endDateEdit->date());

	for (const Transaction& transaction : transactions)
	{
		if (transaction.id() == id)
		{
			// Transaktion gefunden, Dialog öffnen
			showTransactionDialog(transaction);
			break;
		}
	}
}

void TransactionsTab::onDeleteTransaction()
{
	// Ausgewählte Zeile ermitteln
	QModelIndexList selection = m_transactionsTable->selectionModel()->selectedRows();

	if (selection.isEmpty())
	{
		QMessageBox::information(this, tr("Hinweis"),
			tr("Bitte wählen sie eine Transaktion aus."));

		return;
	}

	// Bestätigung anfordern
	if (QMessageBox::question(this, tr("Löschen bestätigen"),
		tr("Möchten sie die ausgewählte Transaktion wirklich löschen?"),
		QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
	{
		return;
	}

	// Transaktion löschen
	int row = selection.first().row();
	int id = m_transactionsModel->item(row, 0)->text().toInt();

	if (m_transactionController->deleteTransaction(id))
	{
		QMessageBox::information(this, tr("Erfolg"),
			tr("Die Transaktion wurde erfolgreich gelöscht."));

		// Daten aktualisieren
		updateTransactionTable();
	}
	else
	{
		QMessageBox::warning(this, tr("Fehler"),
			tr("Die Transaktion konnte nicht gelöscht werden."));
	}
}

void TransactionsTab::onFilterTransactions()
{
	updateTransactionTable();
}

void TransactionsTab::onDateRangeChanged()
{
	// Sicherstellen, dass das EndDatum nicht vor dem Startdatum liegt
	if (m_endDateEdit->date() < m_startDateEdit->date())
	{
		m_endDateEdit->setDate(m_startDateEdit->date());
	}
}