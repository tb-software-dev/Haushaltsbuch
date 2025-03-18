#pragma once

#include <QString>
#include <QLocale>

class CurrencyFormatter
{

public:

	static QString formatCurrency(double amount, int decimals = 2);


	static QString currencySymbol();

	QString euroSymbol = QChar(0x20AC);



};
