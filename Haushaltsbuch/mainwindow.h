#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QDateEdit>
#include <QTableView>
#include <QComboBox>
#include <QPushButton>
#include "budgetcontroller.h"
#include "transactioncontroller.h"
#include "database.h"

class QStandardItemModel;

QT_BEGIN_NAMESPACE

namespace Ui
{
	class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT


public:
	// 
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();


private slots:

	// Aktions-Slots
	void onAddTransaction();
	void onEditTransaction();
	void onDeleteTransaction();
	void onFilterTransactions();
	void onDateRangeTransactions();
	void onAddBudget();
	void onEditBudget();
	void onGenerateReport();






private:

	// UI
	Ui::MainWindow* ui;
	QTabWidget* m_tabWidget;

	// Transaktionen-Tab
	QWidget* m_transactionsTab;
	QDateEdit* m_startDateEdit;
	QDateEdit* m_endDateEdit;
	QTableView* m_transactionsTable;
	QStandardItemModel* m_transactionsModel;
	QPushButton* m_addTransactionButton;
	QPushButton* m_editTransactionButton;
	QPushButton* m_deleteTransactionButton;

	// Budget-Tab
	QWidget* m_budgetTab;
	QTableView* m_budgetTable;
	QStandardItemModel* m_budgetModel;
	QPushButton* m_addBudgetButton;
	QPushButton* m_editBudgetButton;

	// Berichte-Tab
	QWidget* m_reportsTab;
	QComboBox* m_reportTypeComboBox;
	QDateEdit* m_reportStartDateEdit;
	QDateEdit* m_reportEndDateEdit;
	QPushButton* m_generateReportButton;
	QWidget* m_reportContainer;

	// Status-Anzeige
	QLabel* m_statusLabel;

	// Controller
	Database* m_database;
	TransactionController* m_transactionController;
	BudgetController* m_budgetController;


	// Setup-Methoden
	void setupUi();
	void setupTransactionsTab();
	void setupBudgetTab();
	void setupReportsTab();
	void setupStatusBar();

	// Helper-Methoden
	void updateTransactionsTable();
	void updateBudgetTable();
	void updateStatusLabel();
	void showTransactionDialog(const Transaction& transaction = Transaction());
	void showBudgetDialog(const QString& category = QString(), double amount = 0.0);


};