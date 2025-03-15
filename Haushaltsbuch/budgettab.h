#pragma once

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QStandardItemModel>
#include "budgetcontroller.h"

class BudgetTab : public QWidget
{
	Q_OBJECT

public:
    explicit BudgetTab(BudgetController* budgetController, QWidget* parent = nullptr);

    // Öffentliche Methoden zum Aktualisieren der Ansicht
    void updateBudgetTable();

signals:
    // Signale für Statusaktualisierungen
    void budgetChanged();

private slots:
    void onAddBudget();
    void onEditBudget();

private:
    // UI-Komponenten
    QTableView* m_budgetTable;
    QStandardItemModel* m_budgetModel;
    QPushButton* m_addBudgetButton;
    QPushButton* m_editBudgetButton;

    // Controller
    BudgetController* m_budgetController;

    // Helper-Methoden
    void setupUi();
    void showBudgetDialog(const QString& category = QString(), double amount = 0.0);

};
