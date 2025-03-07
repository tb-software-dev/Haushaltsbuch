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
	//
	Ui::MainWindow* ui;

	QTabWidget* m_tabWidget;

	QWidget* m_transactionsTab;
	QDateEdit* m_startDateEdit;




};