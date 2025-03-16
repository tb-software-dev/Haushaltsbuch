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

void MainWindow::setupStatusBar()
{
	// Status-Label erstellen
	m_statusLabel = new QLabel();
	statusBar()->addWidget(m_statusLabel);

	// Status aktualisieren
	updateStatusLabel();
}

void MainWindow::setupConnections()
{
	// Verbindungen zu den Tabs herstellen
	connect(m_transactionsTab, &TransactionsTab::statusChanged,
		this, &MainWindow::updateStatusLabel);

	connect(m_budgetTab, &BudgetTab::budgetChanged,
		this, &MainWindow::updateStatusLabel);
}

void MainWindow::updateStatusLabel()
{
	// Aktuelles Datum für den Monatszeitraum
	QDate startDate = QDate(QDate::currentDate().year(), QDate::currentDate().month(), 1);
	QDate endDate = startDate.addMonths(1).addDays(-1);

	// Einnahmen und Ausgaben für den aktuellen Monat berechnen
	double income = m_transactionController->getTotalIncome(startDate, endDate);
	double expense = m_transactionController->getTotalExpense(startDate, endDate);
	double balance = income - expense;

	// Status-Text erstellen
	QString statusText = tr("Aktueller Monat: Einnahmen: %1 € | Ausgaben: %2 € | Saldo: %3 €")
		.arg(income, 0, 'f', 2)
		.arg(expense, 0, 'f', 2)
		.arg(balance, 0, 'f', 2);

	// Status-Label aktualisieren
	m_statusLabel->setText(statusText);
}

void MainWindow::onExport()
{
	// Dateinamen über Dialog abrufen
	QString fileName = QFileDialog::getSaveFileName(
		this, tr("Daten exportieren"),
		QDir::homePath(), tr("CSV-Dateien (*.csv);;Alle Dateien (*.*)"));

	if (fileName.isEmpty())
	{
		return;
	}

	// Platzhalter Export-Funktion
	QMessageBox::information(this, tr("Exportieren"),
		tr("Export nach %1 noch nicht implementiert.").arg(fileName));
}

void MainWindow::onImport()
{
	// Dateinamen über Dialog abrufen
	QString fileName = QFileDialog::getOpenFileName(
		this, tr("Daten importieren"),
		QDir::homePath(), tr("CSV-Dateien (*.csv);;Alle Dateien (*.*)"));

	if (fileName.isEmpty())
	{
		return;
	}

	// Platzhalter Import-Funktion
	QMessageBox::information(this, tr("Importieren"),
		tr("Import von %1 noch nicht implementiert.").arg(fileName));
}

void MainWindow::onSettings()
{
	// Platzhalter Einstellungs Dialog
	QMessageBox::information(this, tr("Einstellungen"),
		tr("Einstellungsdialog noch nicht implementiert."));
}

void MainWindow::onAbout()
{

	QMessageBox::about(this, tr("Über Haushaltsbuch"),
		tr("<h3>Haushaltsbuch</h3>"
			"<p>Version 1.0</p>"
			"<p>Eine Anwendung zur Verwaltung persönlicher Finanzen.</p>"
			"<p>Entwickelt mit Qt und C++.</p>"));
}
