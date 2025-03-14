#include "transactiondialog.h"
#include "ui_transactiondialog.h"

TransactionDialog::TransactionDialog(QWidget* parent) :
	QDialog(parent), ui(new Ui::TransactionDialog),
	m_transactionId(-1)
{
	ui->setupUi(this);

	// Aktuelles Datum vorausfüllen
	ui->dateEdit->setDate(QDate::currentDate());

}

TransactionDialog::~TransactionDialog()
{
	delete ui;
}

void TransactionDialog::setTransaction(const Transaction& transaction)
{
	// Transaktionstyp setzen
	if (transaction.type() == Transaction::Income)
	{
		ui->incomeRadioButton->setChecked(true);
	}
	else
	{
		ui->expenseRadioButton->setChecked(true);
	}

	// Daten setzen
	ui->dateEdit->setDate(transaction.date());
	ui->amountSpinBox->setValue(transaction.amount());
	ui->categoryComboBox->setCurrentText(transaction.category());
	ui->descriptionTextEdit->setText(transaction.description());

	m_transactionId = transaction.id();
}

void TransactionDialog::setCategories(const QStringList& categories)
{
	ui->categoryComboBox->clear();
	ui->categoryComboBox->addItems(categories);
}

Transaction TransactionDialog::getTransaction() const
{
	// Transaktionstyp bestimmen
	Transaction::Type type = ui->incomeRadioButton->isChecked()
		? Transaction::Income : Transaction::Expense;

	// Transaktion erstellen
	Transaction transaction(
		type,
		ui->dateEdit->date(),
		ui->amountSpinBox->value(),
		ui->categoryComboBox->currentText(),
		ui->descriptionTextEdit->toPlainText()
	);

	// ID setzen 
	transaction.setId(m_transactionId);

	return transaction;
}