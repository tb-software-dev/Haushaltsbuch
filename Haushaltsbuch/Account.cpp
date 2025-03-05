#include "Account.h"

Account::Account() : m_balance(0.0)
{

}

Account::Account(const QString& name, double initialBalance)
    : m_name(name), m_balance(initialBalance)

{

}

void Account::addTransaction(const Transaction& transaction)
{
    m_transactions.append(transaction);
    updateBalance(transaction);
}

void Account::removeTransaction(int transactionId)
{
    for (int i = 0; i < m_transactions.size(); i++)
    {
        if (m_transactions[i].id() == transactionId)
        {
            // Balance neu berechnen (inversiv Operation)
            updateBalance(m_transactions[i], false);
            m_transactions.removeAt(i);
            break;
        }
    }
}

void Account::updateBalance(const Transaction& transaction, bool adding)
{
    if (transaction.type() == Transaction::Income)
    {
        m_balance += adding ? transaction.amount() : -transaction.amount();
    }
    else
    {
        m_balance -= adding ? transaction.amount() : -transaction.amount();
    }
}