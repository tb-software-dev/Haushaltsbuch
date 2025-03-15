#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QDate>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	// Datenbank initialisieren
	m_database = new Database();

	if (!m_database->initialize())
	{
		QMessageBox::critical(this, tr("Fehler"),
			tr("Die Datenbank konnte nicht initialisiert werden."));
	}

	// Controller initialisieren
	m_transactionController = new TransactionController(m_database);
	m_budgetController = new BudgetController(m_database);

	// UI einrichteen
	setupUi();
	setupMenus();
	setupStatusBar();
	setupConnections();

	// Fenstereigenschaften setzen
	setWindowTitle(tr("Haushaltsbuch"));
	resize(800, 600);
}

MainWindow::~MainWindow()
{
	// Resourcen freigeben
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

	// Tabs erstellen und hinzufügen
	m_transactionsTab = new TransactionsTab(m_transactionController, m_tabWidget);
	m_budgetTab = new BudgetTab(m_budgetController, m_tabWidget);
	m_reportsTab = new ReportsTab(m_transactionController, m_budgetController, m_tabWidget);

	m_tabWidget->addTab(m_transactionsTab, tr("Transaktionen"));
	m_tabWidget->addTab(m_budgetTab, tr("Budget"));
	m_tabWidget->addTab(m_reportsTab, tr("Berichte"));

}

void MainWindow::setupMenus()
{
	// Datei-Menü
	QMenu* fileMenu = menuBar()->addMenu(tr("Datei"));

	QAction* exportAction = new QAction(tr("Exportieren"), this);
	connect(exportAction, &QAction::triggered, this, &MainWindow::onExport);
	fileMenu->addAction(exportAction);

	QAction* importAction = new QAction(tr("Importieren"), this);
	connect(importAction, &QAction::triggered, this, &MainWindow::onImport);
	fileMenu->addAction(importAction);

	fileMenu->addSeparator();

	QAction* exitAction = new QAction(tr("Beenden"), this);
	connect(exitAction, &QAction::triggered, this, &MainWindow::close);
	fileMenu->addAction(exitAction);

	// Bearbeiten-Menü
	QMenu* editMenu = menuBar()->addMenu(tr("Bearbeiten"));

	QAction* settingsAction = new QAction(tr("Einstellungen"), this);
	connect(settingsAction, &QAction::triggered, this, &MainWindow::onSettings);
	editMenu->addAction(settingsAction);

	// Hilfe-Menü
	QMenu* helpMenu = menuBar()->addMenu(tr("Hilfe"));

	QAction* aboutAction = new QAction(tr("Über"), this);
	connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
	helpMenu->addAction(aboutAction);

}
