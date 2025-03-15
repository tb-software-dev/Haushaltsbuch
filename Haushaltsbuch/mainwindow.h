#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QTabWidget>
#include "budgetcontroller.h"
#include "transactioncontroller.h"
#include "database.h"
#include "transactionstab.h"
#include "budgettab.h"
#include "reportstab.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	// Konstruktor
	explicit MainWindow(QWidget* parent = nullptr);

	// Destruktor
	~MainWindow();

private slots:

	// Aktualisiert die Statusleiste mit den aktuellen Finanzdaten
	void updateStatusLabel();

	// Exportiert die Daten in eine Datei
	void onExport();

	// Importiert Daten aus einer Datei
	void onImport();

	// Zeigt den Einstellungsdialog an
	void onSettings();

	// Zeigt den About-Dialog an
	void onAbout();

private:
	// UI-Komponenten
	QTabWidget* m_tabWidget;
	TransactionsTab* m_transactionsTab;
	BudgetTab* m_budgetTab;
	ReportsTab* m_reportsTab;
	QLabel* m_statusLabel;

	// Controller und Datenbank
	Database* m_database;		// Datenbankverbindung
	TransactionController* m_transactionController;
	BudgetController* m_budgetController;


	// Initialisiert die Benutzeroberfläche
	void setupUi();

	// Richtet die Menüs ein
	void setupMenus();

	// Richtet die Statusleiste ein
	void setupStatusBar();

	// Stellt Verbindungen zwischen Signalen und Slots her
	void setupConnections();

};