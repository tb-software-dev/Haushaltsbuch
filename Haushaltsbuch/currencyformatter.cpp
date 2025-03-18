#include "currencyformatter.h"

QString CurrencyFormatter::formatCurrency(double amount, int decimals)
{
	QLocale locale(QLocale::German, QLocale::Germany);

	return locale.toString(amount, 'f', decimals) + " " + currencySymbol();


}

QString CurrencyFormatter::currencySymbol()
{
	return QString::fromUtf8("\u20AC");
}

