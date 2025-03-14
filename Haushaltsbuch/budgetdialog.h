#pragma once

#include <QDialog>

namespace Ui
{
	class BudgetDialog;
}

class BudgetDialog : public QDialog
{

	Q_OBJECT

public:
	explicit BudgetDialog(QWidget* parent = nullptr);
	~BudgetDialog();

	// Kategorien f�r die Auswahl setzen
	void setCategories(const QStringList& categories);

	// Vorausf�llen der Felder (bei Bearbeitung)
	void setCategory(const QString& category);
	void setAmount(double amount);

	// Werte abrufen
	QString getCategory() const;
	double getAmount() const;


private:
	Ui::BudgetDialog* ui;
};
