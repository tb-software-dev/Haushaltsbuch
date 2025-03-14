#pragma once

#include <QWidget>
#include <QTableView>
#include <QDateEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include "transactioncontroller.h"

class TransactionsTab : public QWidget
{
	Q_OBJECT

public:
	//
	explicit TransactionsTab(TransactionController* transactionController, QWidget* parent = nullptr);

	// Öffentliche Methode zum Aktualisieren der Ansicht
	void updateTransactionTable();


signals:
		// Signale für Statusaktualisierungen
	void statusChanged();

private slots:
	//
	void onAddTransaction();
	void onEditTransaction();
	void onDeleteTransaction();
	void onFilterTransactions();
	void onDateRangeChanged();

private:
	// UI-Komponenten
	QDateEdit* m_startDateEdit;
	QDateEdit* m_endDateEdit;
	QTableView* m_transactionsTable;
	QStandardItemModel* m_transactionsModel;
	QPushButton* m_addTransactionButton;
	QPushButton* m_editTransactionButton;
	QPushButton* m_deleteTransactionButton;

	// Controller
	TransactionController* m_transactionController;

	// Helper-Methoden
	void setupUi();
	void showTransactionDialog(const Transaction& transaction = Transaction());



};
