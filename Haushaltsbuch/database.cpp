#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>

// Konstruktor : Initialisieren der Datenbankverbindung
Database::Database()
{
	// SQLite als Datenbanktyp festlegen
	m_db = QSqlDatabase::addDatabase("QSQLITE");

	// Datenbank-Datei im aktuellen Verzeichnis speichern
	QString dbPath = QDir::currentPath() + "/haushaltsbuch.db";

	// Datenbankpfad setzen
	m_db.setDatabaseName(dbPath);
}

// Destruktor: Schlieﬂen der Datenbank-Verbindung falls sie bereits offen ist
Database::~Database()
{
	if (m_db.isOpen())
	{
		m_db.close();
	}
}

// Initialisieren der Datenbank
bool Database::initialize()
{
	if (!m_db.open())
	{
		qDebug() << "Fehler beim ÷ffnen der Datenbank:" << m_db.lastError().text();
		return false;
	}

	// Erstellt alle erforderlichen Tabellen
	bool success =		createTransactionsTable() &&
						createBudgetsTable() &&
						createAccountsTable();

	if (!success)
	{
		qDebug() << "Fehler beim Initialisieren der Datenbank Tabellen";
		return false;
	}

	return true;
}

// Erstellt die Transaktions Tabelle
bool Database::createTransactionsTable()
{
	//
	QSqlQuery query;

	return query.exec(
		"CREATE TABLE IF NOT EXISTS transactions ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"type INTEGER NOT NULL, "					// Art der Transaktion (Einnahme oder Ausgabe
		"date DATE NOT NULL, "						// Datum der Transaktion
		"amount REAL NOT NULL, "					// Betrag
		"category TEXT, "							// Kategorie
		"description TEXT, "						// Beschreibung
		"account_id INTEGER, "						// Verkn¸pfung zur Account-Tabelle
		"FOREIGN KEY (account_id) REFERENCES accounts(id))");
}

// Erstellt die Tabelle f¸r die Budgets
bool Database::createBudgetsTable()
{
	//
	QSqlQuery query;

	return query.exec(
		"CREATE TABLE IF NOT EXISTS budgets ("
		"category TEXT PRIMARY KEY, "			// Kategorie als Key erstellen
		"amount REAL NOT NULL)"					// Budgetbetrag
	);	
}

// Erstellt die Tabelle f¸r die Konten
bool Database::createAccountsTable()
{
	//
	QSqlQuery query;

	return query.exec(
		"CREATE TABLE IF NOT EXISTS accounts ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "		// Konto-ID
		"name TEXT NOT NULL, "							// Kontoname
		"balance REAL NOT NULL)"						// Kontostand
	);
}

// Speichert eine neue Transaktion in der Datenbank
bool Database::saveTransaction(Transaction& transaction)
{
	//
	QSqlQuery query;

	query.prepare(
		"INSERT INTO transactions (type, date, amount, category, description, account_id) "
		"VALUES (:type, :date, :amount, :category, :description, :account_id)"
	);

	// Platzhalter mit den Werten von der Transaktion f¸llen
	query.bindValue(":type", transaction.type());
	query.bindValue(":date", transaction.date());
	query.bindValue(":amount", transaction.amount());
	query.bindValue(":category", transaction.category());
	query.bindValue(":description", transaction.description());
	
	if (query.exec())
	{
		// ID der neu eingef¸gten Transaktion setzen
		transaction.setId(query.lastInsertId().toInt());
		return true;
	}

	qDebug() << "Fehler beim Speichern der Transaktion: " << query.lastError().text();
	return false;
}

// Aktualisiert eine vorhandene Transaktion
bool Database::updateTransaction(const Transaction& transaction)
{
	QSqlQuery query;

	query.prepare(
		"UPDATE transactions SET type = :type, date = :date, amount = :amount, "
		"category = :category, description = :description "
		"WHERE id = :id");

	query.bindValue(":type", transaction.type());
	query.bindValue(":date", transaction.date());
	query.bindValue(":amount", transaction.amount());
	query.bindValue(":category", transaction.category());
	query.bindValue(":description", transaction.description());
	query.bindValue(":id", transaction.id());

	if (query.exec())
	{
		return true;
	}

	qDebug() << "Fehler beim Aktualisieren der Transaktion:" << query.lastError().text();
	return false;
}

// Lˆscht eine Transaktion anhand der ID
bool Database::deleteTransaction(int id)
{
	QSqlQuery query;

	query.prepare("DELETE FROM transactions WHERE id = :id");
	query.bindValue(":id", id);

	if (query.exec())
	{
		return true;
	}

	qDebug() << "Fehler beim Lˆschen der Transaktion:" << query.lastError().text();
	return false;
}

// Gibt alle Transaktionen in einem bestimmten Zeitraum zur¸ck
QList<Transaction> Database::getTransactions(const QDate& startDate, const QDate& endDate)
{
	QList<Transaction> transactions;
	QSqlQuery query;

	query.prepare(
		"SELECT id, type, date, amount, category, description "
		"FROM transactions "
		"WHERE date BETWEEN :startDate AND :endDate "
		"ORDER BY date DESC"
	);

	query.bindValue(":startDate", startDate);
	query.bindValue(":endDate", endDate);

	if (query.exec())
	{
		while (query.next())
		{
			Transaction transaction;

			transaction.setId(query.value("id").toInt());
			transaction.setType(static_cast<Transaction::Type>(query.value("type").toInt()));
			transaction.setDate(query.value("date").toDate());
			transaction.setAmount(query.value("amount").toDouble());
			transaction.setCategory(query.value("category").toString());
			transaction.setDescription(query.value("description").toString());

			transactions.append(transaction);
		}
	}
	else
	{
		qDebug() << "Fehler beim Abrufen der Transaktionen:" << query.lastError().text();
	}


	return transactions;

}

bool Database::saveBudget(const Budget& budget)
{
	// Alle alten Eintr‰ge lˆschen
	QSqlQuery clearQuery;
	clearQuery.prepare("DELETE FROM budgets");

	if (!clearQuery.exec())
	{
		qDebug() << "Fehler beim Lˆschen der alten Budgets:" << clearQuery.lastError().text();
		return false;
	}

	// Die neuen Budget-Eintr‰ge hinzuf¸gen
	QStringList categories = budget.getCategories();
	bool success = true;

	for (const QString& category : categories) {
		double amount = budget.getBudget(category);

		QSqlQuery insertQuery;
		insertQuery.prepare(
			"INSERT INTO budgets (category, amount) "
			"VALUES (:category, :amount)");
		insertQuery.bindValue(":category", category);
		insertQuery.bindValue(":amount", amount);

		if (!insertQuery.exec())
		{
			qDebug() << "Fehler beim Speichern des Budgets f¸r" << category << ":" << insertQuery.lastError().text();
			success = false;
		}
	}

	return success;
}

Budget Database::getBudget()
{
	Budget budget;

	QSqlQuery query;
	query.prepare("SELECT category, amount FROM budgets");

	if (query.exec()) {
		while (query.next()) {
			QString category = query.value("category").toString();
			double amount = query.value("amount").toDouble();
			budget.setBudget(category, amount);
		}
	}
	else {
		qDebug() << "Fehler beim Abrufen der Budgets:" << query.lastError().text();
	}

	return budget;
}

// F¸ge auch diese Implementierungen hinzu, falls sie fehlen:

bool Database::saveAccount(Account& account)
{
	QSqlQuery query;

	if (account.name().isEmpty()) {
		qDebug() << "Fehler: Kontoname darf nicht leer sein";
		return false;
	}

	// Pr¸fen, ob das Konto bereits existiert
	int accountId = -1;
	QSqlQuery checkQuery;
	checkQuery.prepare("SELECT id FROM accounts WHERE name = :name");
	checkQuery.bindValue(":name", account.name());

	if (checkQuery.exec() && checkQuery.next()) {
		accountId = checkQuery.value("id").toInt();

		// Konto aktualisieren
		QSqlQuery updateQuery;
		updateQuery.prepare("UPDATE accounts SET balance = :balance WHERE id = :id");
		updateQuery.bindValue(":balance", account.balance());
		updateQuery.bindValue(":id", accountId);

		if (!updateQuery.exec()) {
			qDebug() << "Fehler beim Aktualisieren des Kontos:" << updateQuery.lastError().text();
			return false;
		}
	}
	else {
		// Neues Konto einf¸gen
		QSqlQuery insertQuery;
		insertQuery.prepare("INSERT INTO accounts (name, balance) VALUES (:name, :balance)");
		insertQuery.bindValue(":name", account.name());
		insertQuery.bindValue(":balance", account.balance());

		if (!insertQuery.exec()) {
			qDebug() << "Fehler beim Speichern des Kontos:" << insertQuery.lastError().text();
			return false;
		}

		accountId = insertQuery.lastInsertId().toInt();
	}

	// Konto-ID f¸r nachfolgende Transaktionsbehandlung aktualisieren
	// (In diesem vereinfachten Beispiel machen wir nichts damit)

	return true;
}

QList<Account> Database::getAccounts() {
	QList<Account> accounts;

	QSqlQuery query;
	query.prepare("SELECT id, name, balance FROM accounts");

	if (query.exec()) {
		while (query.next()) {
			QString name = query.value("name").toString();
			double balance = query.value("balance").toDouble();

			Account account(name, balance);
			// account.setId(query.value("id").toInt());  // Falls Account eine ID hat

			accounts.append(account);
		}
	}
	else {
		qDebug() << "Fehler beim Abrufen der Konten:" << query.lastError().text();
	}

	return accounts;
}