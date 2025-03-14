#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "ui_transactiondialog.h"
#include "ui_budgetdialog.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	m_database = new Database();

	if (!m_database->initialize())
	{
		QMessageBox::critical(this, tr("Fehler"),
			tr("Die Datenbank konnte nicht initialisiert werden."));
	}

	// Controller initialisieren
	m_transactionController = new TransactionController(m_database);
	m_budgetController = new BudgetController(m_database);

	// Daten laden
	updateTransactionsTable();
	updateBudgetTable();
	updateStatusLabel();

	// Fenstereigenschaften setzen
	setWindowTitle(tr("Haushaltsbuch"));
	resize(800, 600);


}

MainWindow::~MainWindow()
{
	delete ui;
	delete m_transactionController;
	delete m_budgetController;
	delete m_database;
}

void MainWindow::setupUi()
{
	// Zentrales Widget erstellen
	QWidget* centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);

	// Hauptlayout
	QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

	// Tab-Widget erstellen
	m_tabWidget = new QTabWidget(centralWidget);
	mainLayout->addWidget(m_tabWidget);

	// Tabs einrichten
	setupTransactionsTab();
	setupBudgetTab();
	setupReportsTab();

	// Statusleiste einrichten
	setupStatusBar();
}

void MainWindow::setupTransactionsTab()
{
	m_transactionsTab = new QWidget();
	QVBoxLayout* layout = new QVBoxLayout(m_transactionsTab);

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

	QPushButton* filterButton = new QPushButton(tr("Filter"));

	dateRangeLayout->addWidget(startDateLabel);
	dateRangeLayout->addWidget(m_startDateEdit);
	dateRangeLayout->addWidget(endDateLabel);
	dateRangeLayout->addWidget(m_endDateEdit);
	dateRangeLayout->addWidget(filterButton);
	dateRangeLayout->addStretch();

	layout->addWidget(dateRangeGroup);

	m_transactionsModel = new QStandardItemModel(this);
	m_transactionsModel->setHorizontalHeaderLabels(
		QStringList() << tr("ID") << tr("Datum") << tr("Kategorie") << tr("Beschreibung") << tr("Betrag"));

	m_transactionsTable = new QTableView();
	m_transactionsTable->setModel(m_transactionsModel);
	m_transactionsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_transactionsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_transactionsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_transactionsTable->verticalHeader()->setVisible(false);
	m_transactionsTable->setSortingEnabled(true);

	layout->addWidget(m_transactionsTable);




}