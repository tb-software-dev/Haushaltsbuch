#pragma once

#include <QDate>
#include <QString>



class Transaction
{







public:

	enum class Type
	{
		Income,
		Expense
	};

	Transaction();
	Transaction(Type type, const QDate& date, double amount,
		const QString& category, const QString& description);

	// Getter und Setter
	Transaction::Type type() const { return m_type; }
	void setType(Transaction::Type type) { m_type = type; }

	QDate date() const { return m_date; }
	void setDate(const QDate& date) { m_date = date; }

	double amount() const { return m_amount;  }
	void setAmount(double amount) { m_amount = amount; }
	
	QString category() const { return m_category; }
	void setCategory(const QString& category) { m_category = category; }

	QString description() const { return m_description; }
	void setDescription(const QString& description) { m_description = description; }

	// ID für Datenbankoperationen
	int id() const { return m_id; }
	void setId(int id) { m_id = id; }


private:

	int m_id;              // Eindeutige ID
	Type m_type;           // Art der Transaktion (Einnahme/Ausgabe)
	QDate m_date;          // Datum der Transaktion
	double m_amount;       // Betrag
	QString m_category;    // Kategorie (z.B. "Lebensmittel", "Gehalt")
	QString m_description; // Beschreibung  / Notiz zur Transaktion
};
