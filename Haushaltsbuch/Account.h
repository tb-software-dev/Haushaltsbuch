#pragma once

#include <QString>
#include <QList>
#include "transactions.h"

// Klasse zur Speicherung der Kontoinformationen basierend auf den Transaktionen
class Account
{
public:

	Account();
	Account(const QString& name, double initialBalance = 0.0);

	// Getter und Setter
	QString name() const { return m_name; }
	void setName(const QString& name) { m_name = name; }

	double balance() const { return m_balance; }

	// Kontofunktionen
	void addTransaction(const Transaction& transaction);
	void removeTransaction(int transactionId);

	// Transaktionen abrufen
	QList<Transaction> transactions() const { return m_transactions; }

private:

	QString m_name;							// Kontoname
	double m_balance;						// Aktueller Kontostand
	QList<Transaction> m_transactions;		// Liste aller Transaktionen

	// Aktualisiert den Kontostand basierend auf einer Transaktion
	void updateBalance(const Transaction& transaction, bool adding = true);
};
