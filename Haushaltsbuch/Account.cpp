#include "Account.h"

Account::Account() : m_balance(0.0)
{

}

Account::Account(const QString& name, double initialBalance)
    : m_name(name), m_balance(initialBalance)

{

}