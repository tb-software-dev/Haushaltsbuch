#include "budgetdialog.h"
#include "ui_budgetdialog.h"

BudgetDialog::BudgetDialog(QWidget* parent) : QDialog(parent), ui(new Ui::BudgetDialog)
{
	ui->setupUi(this);
}

BudgetDialog::~BudgetDialog()
{
	delete ui;
}

void BudgetDialog::setCategories(const QStringList& categories)
{
	ui->categoryComboBox->clear();
	ui->categoryComboBox->addItems(categories);
}

void BudgetDialog::setCategory(const QString& category)
{
	ui->categoryComboBox->setCurrentText(category);
}

void BudgetDialog::setAmount(double amount)
{
	ui->amountSpinBox->setValue(amount);
}

QString BudgetDialog::getCategory() const
{
	return ui->categoryComboBox->currentText();
}

double BudgetDialog::getAmount() const
{
	return ui->amountSpinBox->value();
}