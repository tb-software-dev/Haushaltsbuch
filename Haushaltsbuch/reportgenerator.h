#pragma once

#include <QWidget>
#include <QDate>

// Diese abstrakte Klasse erm�glicht die einheitliche Behandlung verschiedener Berichtstypen.

class ReportGenerator
{
public:
	virtual ~ReportGenerator() { }

	// Generiert einen Bericht f�r den angegebenen Zeitraum und f�gt ihn zum Container hinzu
	virtual void generateReport(QWidget* container, const QDate& startDate, const QDate& endDate) = 0;
};
