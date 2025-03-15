#pragma once

#include <QWidget>
#include <QDate>

// Diese abstrakte Klasse ermöglicht die einheitliche Behandlung verschiedener Berichtstypen.

class ReportGenerator
{
public:
	virtual ~ReportGenerator() { }

	// Generiert einen Bericht für den angegebenen Zeitraum und fügt ihn zum Container hinzu
	virtual void generateReport(QWidget* container, const QDate& startDate, const QDate& endDate) = 0;
};
