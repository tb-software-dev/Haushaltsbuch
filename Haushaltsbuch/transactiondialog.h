#pragma once

#include <QDialog>
#include "transactions.h"

namespace Ui
{
	class TransactionDialog;
}

class TransactionDialog : public QDialog
{
	Q_OBJECT

public:

	explicit TransactionDialog(QWidget* parent = nullptr);
	~TransactionDialog();

	// Transaktion setzen
	void setTransaction(const Transaction& transaction);

	// Kategorien für die Auswahl setzen
	void setCategories(const QStringList& categories);

	Transaction getTransaction() const;

private:

	Ui::TransactionDialog* ui;
	int m_transactionId;
};
